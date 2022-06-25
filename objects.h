#pragma once

#include <utility>
#include <list>

#include <SFML/Graphics.hpp>

struct Coord : public std::pair<int, int> {
    using Base = std::pair<int, int>;
    [[nodiscard]] int distance(const Coord & c) const;
    using Base::Base;
};

class Snake {
public:
    enum class Dir {
        UP,
        DOWN,
        RIGHT,
        LEFT,
        BODY,
        NO
    };

    enum class snakeType {
        NONE,
        HUMAN,
        CONTROL
    };

    enum class snakeColor {
        GREEN = 1,
        YELLOW = 2,
        VIOLET = 3,
        RED = 4
    };

    virtual ~Snake();
    void move();

    bool alive;
    int snake_score;
    int number;
    Dir dir;
    snakeType brand;
    snakeColor color;

    std::list <Coord> body;

protected:
    Snake();
    Coord nextPosition(const Dir& d, Coord a);
};

class Fruit {
public:
    enum class fruitType {
        APPLE = 1, //green bord
        LEMON = 2, //yellow bord
        GRAPE = 3, //violet bord
        CHERRY = 4, //red bord
        SUPER_FRUIT, //give more snake_score
        NONE
    };

    Fruit(Coord pos, fruitType type);

    [[nodiscard]] Coord getPosition() const;
    [[nodiscard]] fruitType getBrand() const;

//    sf::Sprite apple;
//    sf::Sprite lemon;
//    sf::Sprite grape;
//    sf::Sprite cherry;
//    sf::Sprite super_fruit;

private:
    Coord position_;
    fruitType brand_;
};

//bool operator== (const Fruit& lh, const Fruit& rh) {
//    return ((lh.getPosition() == rh.getPosition()) && (lh.getBrand() == rh.getBrand()));
//}