#pragma once

#include "ui.h"

#include <SFML/Graphics.hpp>

const int CELL_SIZE = 30;

class Gui : public View {
public:
    Gui();
    ~Gui() override;
    void clearAll();

    void Run() override;

private:
    void snakePainter(const Coord& c, const Snake::Dir& d, const Snake::snakeColor& color) override;
    void fruitPainter(const Coord& c, Fruit::fruitType type) override;
    void scorePainter(int score, Snake::snakeType brand, int num) override;

    void xLine(int y);
    void yLine(int x);

    void drawMainMenu() override;
    void drawInfoMenu();
    void drawGameMenu();
    void drawGame() override;

    void drawBackground();

    void runGame();
    char runInfoMenu();
    char runGameMenu();
    char runMainMenu();

    void sizeOfWin();
    void getKey(long time);
    void timerProcessing();
    static std::string writeInColumn(const sf::Text& input, float column_width);

    sf::RenderWindow window;

    //Game
    sf::Texture t_ground;
    sf::Texture t_bort_g;
    sf::Texture t_bort_y;
    sf::Texture t_bort_v;
    sf::Texture t_bort_b;
    //Snake
    sf::Texture t_body;
    sf::Texture t_head_g;
    sf::Texture t_head_l_g;
    sf::Texture t_head_r;
    sf::Texture t_head_l_r;
    sf::Texture t_head_v;
    sf::Texture t_head_l_v;
    sf::Texture t_head_y;
    sf::Texture t_head_l_y;
    //Fruit
    sf::Texture t_apple;
    sf::Texture t_lemon;
    sf::Texture t_grape;
    sf::Texture t_cherry;
    sf::Texture t_super_fruit;
    //Game
    sf::Texture t_title;
    sf::Texture t_exit_button;
    sf::Texture t_game_button;
    sf::Texture t_info_button;
    sf::Texture t_pause_window;
    sf::Texture t_single_game;
    sf::Texture t_game_with_ai;

    //Game
    sf::Sprite ground;
    sf::Sprite bort_g;
    sf::Sprite bort_y;
    sf::Sprite bort_v;
    sf::Sprite bort_b;
    //Snake
    sf::Sprite body;
    sf::Sprite head_g;
    sf::Sprite head_l_g;
    sf::Sprite head_r;
    sf::Sprite head_l_r;
    sf::Sprite head_v;
    sf::Sprite head_l_v;
    sf::Sprite head_y;
    sf::Sprite head_l_y;
    //Fruit
    sf::Sprite apple;
    sf::Sprite lemon;
    sf::Sprite grape;
    sf::Sprite cherry;
    sf::Sprite super_fruit;
    //Game
    sf::Sprite title;
    sf::Sprite exit_button;
    sf::Sprite game_button;
    sf::Sprite info_button;
    sf::Sprite pause_window;
    sf::Sprite single_game;
    sf::Sprite game_with_ai;

    //Game
    sf::Font font;
    sf::Text score_text;
//    sf::Text info_text;
};