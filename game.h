#pragma once

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <functional>
#include <memory>

#include "objects.h"
#include "human.h"
#include "AI.h"

#define nFRUITS 1
#define FRUIT_TIME 16
#define SUPER_FRUIT_TIME 17
#define SNAKE_TIME 400000000

using SnakePainter = std::function<void(Coord, Snake::Dir, Snake::snakeColor)>;
using FruitPainter = std::function<void(Coord, Fruit::fruitType)>;
using ScorePainter  = std::function<void(int, Snake::snakeType, int)>;

class Game {
public:
    Game();
    ~Game() = default;
    void clearAll();

    void paintObjects(const SnakePainter& ps, const FruitPainter& pr, const ScorePainter& psc); //uses in Gui
    char checkPlaceStatus(Coord c); //uses in Snake
    Fruit::fruitType eatFruit(Coord c); //uses in Snake
    static int snakeScoring(const Fruit::fruitType& fruit_type, const Snake::snakeColor& snake_color); //uses in Snake
    void biteOffTail(Coord c);  //uses in Snake

    Coord nearestFruit(const Coord& c); //uses in AI //make in one of classes

protected:
//    Game();
    void snakeMovement(); //make virtual
    void addNewSnake(std::shared_ptr<Snake>& s);

//private:
    Coord getFreeCoord();
    void fruitsGenerate(Fruit::fruitType type);
    bool isPlaceFree(Coord c);

    int snake_number_;
    std::list <std::shared_ptr<Snake>> snakes_;
    std::list <Fruit> fruits_;
};

class SingleGame: public Game {
public:
    SingleGame();
};

class GameWithAi: public Game {
public:
    GameWithAi();

//    Coord nearestFruit(const Coord& c); //uses in AI //make in one of classes
};