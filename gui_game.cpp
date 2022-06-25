#include <sstream>

#include "gui.h"
//#include "objects.h"

void Gui::drawGame() {
    sizeOfWin();

    window.clear();

    drawBackground();

    score_text.setFillColor(sf::Color(152, 0, 198));
    score_text.setString("Score : ");
    score_text.setPosition(30,5);
    window.draw(score_text);

    using namespace std::placeholders;

    game->paintObjects(std::bind(&Gui::snakePainter, this, _1, _2, _3),
                       std::bind(&Gui::fruitPainter, this, _1, _2),
                       std::bind(&Gui::scorePainter, this, _1, _2, _3));

    fflush(stdout);
    window.display();
}

void Gui::snakePainter(const Coord& c, const Snake::Dir& d, const Snake::snakeColor& color) {
    sf::Sprite head, head_l;

    if (color == Snake::snakeColor::GREEN) {
        head = head_g;
        head_l = head_l_g;
    } else if (color == Snake::snakeColor::RED) {
        head = head_r;
        head_l = head_l_r;
    } else if (color == Snake::snakeColor::VIOLET) {
        head = head_v;
        head_l = head_l_v;
    } else if (color == Snake::snakeColor::YELLOW) {
        head = head_y;
        head_l = head_l_y;
    } else
        std::cout << "ERROR: snakePainter" << std::endl;

    switch (d) {
        case Snake::Dir::DOWN: {
            head.setTextureRect(sf::IntRect(0, 0, CELL_SIZE, CELL_SIZE));
            head.setPosition(static_cast<float>(c.first) * CELL_SIZE, static_cast<float>(c.second) * CELL_SIZE);
            window.draw(head);
            break;
        }

        case Snake::Dir::UP: {
            head.setTextureRect(sf::IntRect(0, CELL_SIZE, CELL_SIZE, -CELL_SIZE));
            head.setPosition(static_cast<float>(c.first) * CELL_SIZE, static_cast<float>(c.second) * CELL_SIZE);
            window.draw(head);
            break;
        }

        case Snake::Dir::LEFT: {
            head_l.setTextureRect(sf::IntRect(0, 0, CELL_SIZE, CELL_SIZE));
            head_l.setPosition(static_cast<float>(c.first) * CELL_SIZE, static_cast<float>(c.second) * CELL_SIZE);
            window.draw(head_l);
            break;
        }

        case Snake::Dir::RIGHT: {
            head_l.setTextureRect(sf::IntRect(CELL_SIZE, 0, -CELL_SIZE, CELL_SIZE));
            head_l.setPosition(static_cast<float>(c.first) * CELL_SIZE, static_cast<float>(c.second) * CELL_SIZE);
            window.draw(head_l);
            break;
        }

        default: {
            body.setPosition(static_cast<float>(c.first) * CELL_SIZE, static_cast<float>(c.second) * CELL_SIZE);
            window.draw(body);
            break;
        }

    }
}

void Gui::fruitPainter(const Coord& c, Fruit::fruitType type) {
    sf::Sprite t;

    if (type == Fruit::fruitType::APPLE)
        t = apple;
    else if (type == Fruit::fruitType::LEMON)
        t = lemon;
    else if (type == Fruit::fruitType::CHERRY)
        t = cherry;
    else if (type == Fruit::fruitType::GRAPE)
        t = grape;
    else
        t = super_fruit;

    t.setPosition(static_cast<float>(c.first) * CELL_SIZE, static_cast<float>(c.second) * CELL_SIZE);
    window.draw(t);
}

void Gui::scorePainter(int score, Snake::snakeType brand, int num) {

    if (brand == Snake::snakeType::HUMAN)
        score_text.setFillColor(sf::Color::Yellow);
    else if (brand == Snake::snakeType::CONTROL)
        score_text.setFillColor(sf::Color::Green);
    else score_text.setFillColor(sf::Color::Red);

    std::ostringstream p;
    p << score;
    score_text.setString(p.str());
    score_text.setPosition(static_cast<float>(100 * (num + 1)), 5);
    window.draw(score_text);
}

void Gui::getKey(long time) {

    sf::Clock clock;
    sf::Time timer = sf::microseconds(1000);
    clock.restart();
    timer = clock.getElapsedTime();
    char c;

    while (timer.asMicroseconds() / 1000 < time) {

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            c = 'd';
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            c = 'a';
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            c = 's';
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            c = 'w';
        }

        onkey_deligater->onKey(c);
        timer = clock.getElapsedTime();
    }

}

void Gui::runGame() {
    while(window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) { //Closed
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) { //While running

                if (event.key.code == sf::Keyboard::P) { //Pause
//                    Если оставить так, то не видно остановленной игры во время поузы
//                    pause_window.setPosition(500, 500);
//                    window.draw(pause_window);
//                    window.display();

                    bool isPause = true;
                    sf::Event pause_event{};

                    while(isPause) {
                        window.pollEvent(pause_event);
                        if (pause_event.type == sf::Event::KeyPressed)
                            isPause = false;
                    }
                }
                if (event.key.code == sf::Keyboard::Q) { //Quit
                    //по сути костыльный (или нет) выход из двойного цикла
                    goto stop;
                }
            }
        }

        timerProcessing();

        drawGame();
    }

    stop:;
}

void Gui::timerProcessing() {
    struct timespec start_time{}, finish_time{}, work_time{};

    clock_gettime(CLOCK_REALTIME,  &start_time);
    getKey(static_cast<long>(ontime_deligater.front().first));
    clock_gettime(CLOCK_REALTIME,  &finish_time);

    work_time.tv_sec = finish_time.tv_sec - start_time.tv_sec;
    work_time.tv_nsec = finish_time.tv_nsec - start_time.tv_nsec;
    int d = static_cast<int>(work_time.tv_sec * 1000) + static_cast<int>(work_time.tv_nsec / 1000000);

    for(int i = 0; i < ontime_deligater.size(); i ++) {
        std::pair<long, timeoutable> a = ontime_deligater.front();
        ontime_deligater.pop_front();
        a.first -= d;
        ontime_deligater.push_back(a);
    }

    for(int i = 0; i < ontime_deligater.size(); i ++) {
        std::pair<long, timeoutable> a = ontime_deligater.front();
        ontime_deligater.pop_front();

        if(a.first <= 0) {
            a.second();
        }

        else ontime_deligater.push_back(a);
    }
}