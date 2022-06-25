#include <random>

#include "AI.h"
#include "ui.h"


AI::AI() : Snake() {
    brand = snakeType::CONTROL;
}

AI::~AI() = default;

void AI::onControl() {
    View * v = View::getInst();

    Dir d[4] = {Dir::UP, Dir::DOWN, Dir::LEFT, Dir::RIGHT};

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(d, d + 4, g);
    Coord next_fruit = v->game->nearestFruit(body.front());

    dir = Dir::NO;

    bool isOk = false;

    Game * game = v->game;

    if (next_fruit != Coord(0, 0)){
        int now = next_fruit.distance(body.front());

        for (auto p : d) {
            dir = p;
            char next_p = game->checkPlaceStatus(nextPosition(p, body.front()));
            int next = next_fruit.distance(nextPosition(p, body.front()));
            if (next < now && (next_p == ' ' || next_p == 'f' ||
                               next_p == 'r'|| next_p == 'g'|| next_p == 'v'|| next_p == 'y')) {
                isOk = true;
                break;
            }
        }
    }

    if (!isOk)
        for (auto p : d) {
            dir = p;
            Coord c = nextPosition(p, body.front());
            char next = game->checkPlaceStatus(c);
            if (next == ' ' || next == 'r'|| next == 'g'|| next == 'v'|| next == 'y') {
                break;
            }
        }
}

void AI::onControl_v2() {
    View * v = View::getInst();

    Dir d[4] = {Dir::UP, Dir::DOWN, Dir::LEFT, Dir::RIGHT};

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(d, d + 4, g);
    Coord next_fruit = v->game->nearestFruit(body.front());

    Game * game = v->game;

    Dir dir_cur = dir;
    char next_p_cur = game->checkPlaceStatus(nextPosition(dir_cur, body.front()));
    int next_cur = next_fruit.distance(nextPosition(dir_cur, body.front()));

    bool isOk = false;

    if (next_fruit != Coord(0, 0)){
        int now = next_fruit.distance(body.front());

        for (auto p : d) {
            dir = p;
            char next_p = game->checkPlaceStatus(nextPosition(p, body.front()));
            int next = next_fruit.distance(nextPosition(p, body.front()));
            if (next < now && (next_p == ' ' || next_p == 'f' ||
                               next_p == 'r'|| next_p == 'g'|| next_p == 'v'|| next_p == 'y')) {
                if (next == next_cur && (next_p_cur == ' ' || next_p_cur == 'f' ||
                                         next_p == 'r'|| next_p == 'g'|| next_p == 'v'|| next_p == 'y')) {
                    dir = dir_cur;
                }
                isOk = true;
                break;
            }
        }
    }

    if (!isOk)
        for (auto p : d) {
            dir = p;
            Coord c = nextPosition(p, body.front());
            char next = game->checkPlaceStatus(c);
            if (next == ' ' || next == 'r'|| next == 'g'|| next == 'v'|| next == 'y') {
                break;
            }
        }
}