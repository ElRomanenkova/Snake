#pragma once

#include "keypressable.h"
#include "game.h"
#include "control.h"
#include "objects.h"

#include <poll.h>
#include <ctime>
#include <functional>

using timeoutable = std::function<void()>;

class View {
public:
    View();
    virtual ~View();

    void setOnKey(Keypressable * key); //Human
    void setOnTimer(struct timespec timeout, timeoutable t); //game
    void setOnAI(Control * ctrl); //AI
    void setModel(Game * g); //main
//    auto * getKey();
//    auto getTimer();
//    AI * getAI();

    static View * getInst();
    static void setInst(View * instance);

    virtual void drawMainMenu() = 0;
//    virtual void drawBack() = 0;
//    virtual void drawObjects() = 0;
    virtual void drawGame() = 0;
    virtual void Run() = 0;

    int x, y;

    Keypressable * onkey_deligater;
//    std::list <Keypressable *> onkey_deligater;
    std::list <Control *> control_deligater;
    std::list <std::pair <long, timeoutable>> ontime_deligater;
    Game * game;

protected:
    virtual void snakePainter(const Coord& c, const Snake::Dir& d, const Snake::snakeColor& color) = 0;
    virtual void fruitPainter(const Coord& c, Fruit::fruitType type) = 0;
    virtual void scorePainter(int score, Snake::snakeType brand, int num) = 0;

    static View * inst;
};