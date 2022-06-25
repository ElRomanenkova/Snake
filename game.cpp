#include "game.h"
#include "ui.h"

#include <ctime>
#include <random>

using namespace std::placeholders;

GameWithAi::GameWithAi(): Game() {
    View * v = View::getInst();

    auto human_snake = std::make_shared<Human>();
    auto ai_snake = std::make_shared<AI>();

    v->setOnKey(human_snake.get());
    v->setOnAI(ai_snake.get());

    auto snake1 = std::static_pointer_cast<Snake>(human_snake);
    auto snake2 = std::static_pointer_cast<Snake>(ai_snake);

    addNewSnake(snake1);
    addNewSnake(snake2);

//    v->setModel(this);
}

SingleGame::SingleGame(): Game() {
    View * v = View::getInst();

    auto human_snake = std::make_shared<Human>();

    v->setOnKey(human_snake.get());

    auto snake = std::static_pointer_cast<Snake>(human_snake);

    addNewSnake(snake);

//    v->setModel(this);
}

Game::Game(): snake_number_(0) {

    View * v = View::getInst();

    Fruit::fruitType arr[4] = {Fruit::fruitType::APPLE, Fruit::fruitType::LEMON,
                               Fruit::fruitType::GRAPE, Fruit::fruitType::CHERRY};

    for (const auto& ft : arr) {
        for (int i = 0; i < nFRUITS; i++) {
            fruitsGenerate(ft);
            View::getInst()->ontime_deligater.pop_back();
        }
    }

    struct timespec t = {0, SNAKE_TIME};
    v->setOnTimer(t, [this]() { snakeMovement(); });

    //полследующая генерация фруктиков
    long interval = 0;
    for (const auto& ft : arr) {
        t = {FRUIT_TIME + interval, 0};
        interval -= 4;
        v->setOnTimer(t, [this, ft]() { fruitsGenerate(ft); });
    }

    t = {SUPER_FRUIT_TIME, 0};
    v->setOnTimer(t, [this]() { fruitsGenerate(Fruit::fruitType::SUPER_FRUIT); });

//    v->setModel(this);
}

void Game::clearAll() {
    snake_number_ = 0;
    snakes_.clear();
    fruits_.clear();
}

void Game::addNewSnake(std::shared_ptr<Snake>& s) {
    snakes_.push_back(s);
    snake_number_++;
    s->number = snake_number_;
}

void Game::snakeMovement() {

    bool isAllDie = true;

    for(const auto& s: snakes_)
        if(s->alive) {
            isAllDie = false;
            break;
        }

    if(isAllDie) {
//        View::get()->Run();
    }

    if (!View::getInst()->control_deligater.empty())
        for (const auto& ai : View::getInst()->control_deligater)
            ai->onControl_v2();

    for (const auto& s: snakes_)
        if (s->alive)
            s->move();

    struct timespec t = {0, SNAKE_TIME};
    View::getInst()->setOnTimer(t, [this]() { snakeMovement(); });
}

void Game::fruitsGenerate(Fruit::fruitType type) {

    if (type == Fruit::fruitType::APPLE || type == Fruit::fruitType::LEMON ||
        type == Fruit::fruitType::CHERRY || type == Fruit::fruitType::GRAPE) {
        struct timespec t = {FRUIT_TIME, 0};
        View::getInst()->setOnTimer(t, [this, type]() { fruitsGenerate(type); });
    }

    if (type == Fruit::fruitType::SUPER_FRUIT) {
        struct timespec t = {SUPER_FRUIT_TIME, 0};
        View::getInst()->setOnTimer(t, [this]() { fruitsGenerate(Fruit::fruitType::SUPER_FRUIT); });
    }

    fruits_.emplace_back(getFreeCoord(), type);
}

Coord Game::getFreeCoord() {
    Coord c;

    std::random_device rd;
    std::mt19937 gen(rd());

    while (true) {
        std::uniform_int_distribution<int> dist_x(2,View::getInst()->x - 2);
        c.first = dist_x(gen);

        std::uniform_int_distribution<int> dist_y(2,View::getInst()->y - 2);
        c.second = dist_y(gen);

        if (isPlaceFree(c))    return c;
    }
}

void Game::paintObjects(const SnakePainter& ps, const FruitPainter& pr, const ScorePainter& psc) {

    for (const auto& s : snakes_) {
        bool isHead = true;

        for (const auto& c : s->body) {
            ps(c, isHead ? s->dir : Snake::Dir::BODY, s->color);
            isHead = false;
        }

        psc(s->snake_score, s->brand, s->number);
    }

    for (const auto& f : fruits_) {
        pr(f.getPosition(), f.getBrand());
    }
}

Coord Game::nearestFruit(const Coord& c) {
//Coord GameWithAi::nearestFruit(const Coord& c) {

    if (fruits_.empty()) return {0, 0};

    Coord near;
    int min = fruits_.front().getPosition().distance(c);
    near = fruits_.front().getPosition();

    for (auto f : fruits_) {
        if (min > f.getPosition().distance(c)) {
            min = f.getPosition().distance(c);
            near = f.getPosition();
        }
    }
    return near;
}

void Game::biteOffTail(Coord c) {
    for (auto& s : snakes_) {
        auto temp = s->body.begin();
        for (auto& sb : s->body) {
            if (c == sb) {
                s->color = Snake::snakeColor::VIOLET; //проблема ниже
                s->body.pop_back();
//                s->body.pop_back();
//                s->body.erase(temp, s->body.end());
//                s->body.resize(temp);
//                s->body.erase(sb);
            }
            temp++;
        }
    }

//        for(auto i = s->body.begin(); i != s->body.end(); i++) {
//            if (*i == c)
//                s->body.erase(i, s->body.end());
//        }
}

char Game::checkPlaceStatus(Coord c) {
    for (const auto& s : snakes_)
        for (const auto& sb : s->body)
            if (c == sb)  return 's';

    for (const auto& f : fruits_)
        if (c == f.getPosition()) {
            return 'f';
        }

    if (c.first == 0) return 'r';
    if (c.second == 0) return 'g';
    if (c.first == View::getInst()->x) return 'v';
    if (c.second == View::getInst()->y) return 'y';

    return ' ';
}

bool Game::isPlaceFree(Coord c) {

    for (const auto& f : fruits_)
        if (c == f.getPosition()) return false;

    for (const auto& s : snakes_)
        for (const auto& sb : s->body)
            if (c == sb) return false;

    return true;
}

Fruit::fruitType Game::eatFruit(Coord c) {

    Fruit::fruitType t;
    for (const auto& f : fruits_)
        if (c == f.getPosition()) {
            t = f.getBrand();
            fruits_.remove(f);
            return t;
        }
    return Fruit::fruitType::NONE;
}

int Game::snakeScoring(const Fruit::fruitType& fruit_type, const Snake::snakeColor& snake_color) {
    if (static_cast<int>(fruit_type) == static_cast<int>(snake_color))
        return 2;
    if (fruit_type == Fruit::fruitType::SUPER_FRUIT)
        return 4;
    return 1;
}

bool operator== (const Fruit& lh, const Fruit& rh) {
    return ((lh.getPosition() == rh.getPosition()) && (lh.getBrand() == rh.getBrand()));
}