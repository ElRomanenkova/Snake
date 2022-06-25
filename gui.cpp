#include <sstream>
#include <unistd.h>

#include "gui.h"
#include "game.h"
#include "objects.h"

void Gui::sizeOfWin() {
    sf::Vector2u size = window.getSize();
//    x = 101;
//    y = 101;
    x = static_cast<int>(size.x) / CELL_SIZE;
    y = static_cast<int>(size.y) / CELL_SIZE;
}

Gui::Gui(): View() {

    window.create(sf::VideoMode(1920,1080), "Snake");
    sizeOfWin();

    font.loadFromFile("./fonts/Eight-Bit Madness.TTF");
    score_text.setFont(font);
    score_text.setCharacterSize(45);

//    info_text.setFont(font);
//    info_text.setCharacterSize(45);

    t_bort_g.loadFromFile("./images/bort_green.png");
    bort_g.setTexture(t_bort_g);
    t_bort_y.loadFromFile("./images/bort_yellow.png");
    bort_y.setTexture(t_bort_y);
    t_bort_v.loadFromFile("./images/bort_violet.png");
    bort_v.setTexture(t_bort_v);
    t_bort_b.loadFromFile("./images/bort_red.png");
    bort_b.setTexture(t_bort_b);

    t_ground.loadFromFile("./images/grass.png");
    ground.setTexture(t_ground);

    t_body.loadFromFile("./images/body_green.png");
    body.setTexture(t_body);

    t_head_g.loadFromFile("./images/head_green.png");
    head_g.setTexture(t_head_g);
    t_head_l_g.loadFromFile("./images/head_l_green.png");
    head_l_g.setTexture(t_head_l_g);
    t_head_r.loadFromFile("./images/head_red.png");
    head_r.setTexture(t_head_r);
    t_head_l_r.loadFromFile("./images/head_l_red.png");
    head_l_r.setTexture(t_head_l_r);

    t_head_v.loadFromFile("./images/head_violet.png");
    head_v.setTexture(t_head_v);
    t_head_l_v.loadFromFile("./images/head_l_violet.png");
    head_l_v.setTexture(t_head_l_v);
    t_head_y.loadFromFile("./images/head_yellow.png");
    head_y.setTexture(t_head_y);
    t_head_l_y.loadFromFile("./images/head_l_yellow.png");
    head_l_y.setTexture(t_head_l_y);

    t_apple.loadFromFile("./images/apple.png");
    apple.setTexture(t_apple);
    t_lemon.loadFromFile("./images/lemon.png");
    lemon.setTexture(t_lemon);
    t_cherry.loadFromFile("./images/cherry.png");
    cherry.setTexture(t_cherry);
    t_grape.loadFromFile("./images/grape.png");
    grape.setTexture(t_grape);
    t_super_fruit.loadFromFile("./images/super_fruit.png");
    super_fruit.setTexture(t_super_fruit);

    t_title.loadFromFile("./images/snake3.png");
    title.setTexture(t_title);
    t_exit_button.loadFromFile("./images/exit2.png");
    exit_button.setTexture(t_exit_button);
    t_game_button.loadFromFile("./images/new_game5.png");
    game_button.setTexture(t_game_button);
    t_info_button.loadFromFile("./images/info.png");
    info_button.setTexture(t_info_button);
//    t_pause_window.loadFromFile("./images/game.png"); //!!!!!!!!!!!!!
//    pause_window.setTexture(t_pause_window);
    t_single_game.loadFromFile("./images/single.png");
    single_game.setTexture(t_single_game);
    t_game_with_ai.loadFromFile("./images/ai_game.png");
    game_with_ai.setTexture(t_game_with_ai);
}


Gui::~Gui() {
    window.clear();
//    ontime_deligater.clear();
//    control_deligater.clear();
//    onkey_deligater = nullptr;
//    Game::get()->clear();
//    setModel(nullptr); //game = nullptr;
}

void Gui::clearAll() {
    ontime_deligater.clear();
    control_deligater.clear();
    onkey_deligater = nullptr;
//    onkey_deligater.clear();
    game->clearAll();
    setModel(nullptr); //Game * game = nullptr;
}

void Gui::drawBackground() {
    for(int i = 0; i < y; i++)
        for(int j = 0; j < x; j++) {
            ground.setPosition(static_cast<float>(j) * CELL_SIZE, static_cast<float>(i) * CELL_SIZE);
            window.draw(ground);
        }

    xLine(0);
    xLine(y);

    yLine(0);
    yLine(x);
}

void Gui::xLine(int y) {
    sf::Sprite bort;

    if (y == 0)
        bort = bort_g;
    else if (y == this->y)
        bort = bort_y;
    else
        std::cout << "ERROR: xLine" << std::endl;

    for (int i = 0; i < x; i ++) {
        bort.setPosition(static_cast<float>(i) * CELL_SIZE, static_cast<float>(y) * CELL_SIZE);
        window.draw(bort);
    }
}

void Gui::yLine(int x) {
    sf::Sprite bort;

    if (x == 0)
        bort = bort_b;
    else if (x == this->x)
        bort = bort_v;
    else
        std::cout << "ERROR: yLine" << std::endl;

    for (int i = 0; i < y; i ++) {
        bort.setPosition(static_cast<float>(x) * CELL_SIZE, static_cast<float>(i) * CELL_SIZE);
        window.draw(bort);
    }
}

void Gui::Run() {

    while (window.isOpen()) {
        auto game = std::make_unique<Game>();
        setModel(game.get());

        std::unique_ptr<SingleGame> game1;
        std::unique_ptr<GameWithAi> game2;
//        std::unique_ptr<Game> game;

//        auto game_single = std::make_unique<SingleGame>(); //solved problem of segfault
//        auto game_ai = std::make_unique<GameWithAi>();
//        setModel(game_single.get());

        bool isMenu = true;

        while (isMenu) {
            drawMainMenu();
            char main_code = runMainMenu();

            switch (main_code) {
                case 'g' : {
                    drawGameMenu();
                    sleep(1);

                    char game_code = runGameMenu();

                    if (game_code == 'c') {
                        isMenu = false;
                        window.close();
                    }
                    else if (game_code == 's') {
                        game1 = std::make_unique<SingleGame>();
//                        game1 = std::move(game_single);
                        setModel(game1.get());
//                        setModel(game_single.get());
                        isMenu = false;
                    }
                    else if (game_code == 'a') {
                        game2 = std::make_unique<GameWithAi>();
//                        game2 = std::move(game_ai);
                        setModel(game2.get());
//                        setModel(game_ai.get());
                        isMenu = false;
                    }
                    else if (game_code == 'q')
                        isMenu = true;
                    else
                        std::cout << "ERROR: Gui::Run 'g'" << std::endl;

//                    isMenu = false;
                    break;
                }

                case 'i' : {
                    drawInfoMenu();
                    char info_code = runInfoMenu();

                    if (info_code == 'c') {
                        isMenu = false;
                        window.close();
                    }
                    else if (info_code == 'q')
                        isMenu = true;
                    else
                        std::cout << "ERROR: Gui::Run 'i'" << std::endl;

                    break;
                }

                case 'c' :
                    isMenu = false;
                    window.close();
                    break;

                case 'e' :
                    isMenu = false;
//                    std::cout << "ERROR: Gui::Run" << std::endl;
                    break;

                default:
                    break;
            }
        }

        drawGame();
        runGame();

        clearAll();
    }
}