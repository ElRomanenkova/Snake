#include "objects.h"
#include "ui.h"

int mod(int a) {
    return (a > 0) ? a : -a;
}

int Coord::distance(const Coord &c) const {
    int x = View::getInst()->x;
    int y = View::getInst()->y;

    int min_distance = mod(c.first - first) + mod(c.second - second);
    int bot = mod(c.first - first) + mod(c.second - (y + second));
    int top = mod(c.first - first) + mod(c.second - (- y + second));
    int left = mod(c.first - (- x + first)) + mod(c.second - second);
    int right = mod(c.first - (x + first)) + mod(c.second - second);

    min_distance = std::min(min_distance, std::min(bot, std::min(top, std::min(left, right))));

    return min_distance;
}

Fruit::Fruit(Coord pos, fruitType type) {
    position_ = pos;
    brand_ = type;
}

Fruit::fruitType Fruit::getBrand() const {
    return brand_;
}

Coord Fruit::getPosition() const {
    return position_;
}

Snake::Snake() {

    alive = true;
    dir = Dir::UP;
    Coord c;
    snake_score = 0;
    brand = snakeType::NONE;
    color = snakeColor::GREEN;
    number = 0;

//    srand(time(nullptr));
    c.first = View::getInst()->x / 3 + rand() % (View::getInst()->x / 3);
    c.second = View::getInst()->y / 3 + rand() % (View::getInst()->y / 3);

    for (int i = 0; i < 3; i++) {
        body.emplace_back(++c.first, c.second);
    }
}

Snake::~Snake() = default;
//{
//    delete[] body;
//}

void Snake::move() {

    View * v = View::getInst();

    Coord a = body.front();
    a = nextPosition(dir, a);

    switch (v->game->checkPlaceStatus(a)) {
        case ' ' :
            body.push_front(a);
            body.pop_back();
            break;

        case 's' :
//            Game::getInst()->biteOffTail(a);
            alive = false;
            break;

        case 'f' : {
            auto type_of_fruit = v->game->eatFruit(a);
            int score = Game::snakeScoring(type_of_fruit, color);
            snake_score += score;

            body.push_front(a);
            break;
        }

        //different borders: red, green, violet, yellow
        case 'r' :
            color = snakeColor::RED;
            body.emplace_front(abs(v->x - a.first - 1), a.second);
            body.pop_back();
            break;

        case 'g' :
            color = snakeColor::GREEN;
            body.emplace_front(a.first, abs(v->y - a.second - 1));
            body.pop_back();
            break;

        case 'v' :
            color = snakeColor::VIOLET;
            body.emplace_front(abs(v->x - a.first - 1), a.second);
            body.pop_back();
            break;

        case 'y' :
            color = snakeColor::YELLOW;
            body.emplace_front(a.first, abs(v->y - a.second - 1));
            body.pop_back();
            break;

        default:
            break;
    }
}

Coord Snake::nextPosition(const Dir& d, Coord a) {

    switch (d) {
        case Dir::UP:
            a.second ++;
            break;

        case Dir::DOWN:
            a.second --;
            break;

        case Dir::LEFT:
            a.first --;
            break;

        case Dir::RIGHT:
            a.first ++;
            break;

        default:
            break;
    }
    return a;
}