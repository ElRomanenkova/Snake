#include "human.h"

Human::Human(): Snake() {
    brand = snakeType::HUMAN;
}

Human::~Human() = default;

void Human::setDirection(Dir d) {

    if((d == Dir::LEFT || d == Dir::RIGHT) && (dir == Dir::LEFT || dir == Dir::RIGHT))  return;
    if((d == Dir::UP || d == Dir::DOWN) && (dir == Dir::UP || dir == Dir::DOWN))  return;
    dir = d;
}

void Human::onKey(char key) {

    switch (key) {
        case 'a':
            if(dir == Dir::LEFT)  break;
            setDirection(Dir::LEFT);
            break;

        case 'd':
            if(dir == Dir::RIGHT)  break;
            setDirection(Dir::RIGHT);
            break;

        case 'w':
            if(dir == Dir::UP)  break;
            setDirection(Dir::UP);
            break;

        case 's':
            if(dir == Dir::DOWN)  break;
            setDirection(Dir::DOWN);
            break;

        default:
            break;
    }

}
