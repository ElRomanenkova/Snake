#include "ui.h"

#include <utility>
#include "game.h"

View::View() {
    x = 0;
    y = 0;
    game = nullptr;
    onkey_deligater = nullptr;
}

View::~View() {
    ontime_deligater.clear();
    control_deligater.clear();
    game = nullptr;
}

View * View::inst;

View * View::getInst() {

    if(inst != nullptr)    return inst;

    fprintf(stderr, "View has been deleted - getInst()\n");
    exit(1);
}

void View::setInst(View * instance) {
    inst = instance;
}

void View::setOnTimer(struct timespec timeout, timeoutable t) {
    std::pair <long , timeoutable> n;

    n.first = timeout.tv_nsec / 1000000 + timeout.tv_sec * 1000;
    n.second = std::move(t);

    //if(ontime_deligater.front().first >= n.first) ontime_deligater.push_front(n);
    ontime_deligater.push_back(n);
}

//auto View::getTimer() {
//    return ontime_deligater;
//}

void View::setOnKey(Keypressable * key) {
    onkey_deligater = key;
//    onkey_deligater.push_back(key);
}

//auto * View::getKey() {
//    return onkey_deligater;
//}

void View::setOnAI(Control * ctrl) {
    control_deligater.push_back(ctrl);
}

//AI * View::getAI() {
//    return AI_deligater;
//}

void View::setModel(Game * g) {
    game = g;
}