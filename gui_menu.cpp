#include "gui.h"
//#include "game.h"
//#include "objects.h"

void Gui::drawMainMenu() {
    sizeOfWin();
    window.clear();

    drawBackground();

    title.setPosition(543, 100); //width - 1860
    window.draw(title);

    game_button.setPosition(760, 400);
    window.draw(game_button);

    info_button.setPosition(849, 550);
    window.draw(info_button);

    exit_button.setPosition(860, 700);
    window.draw(exit_button);

    window.display();
}

void Gui::drawGameMenu() {
    sizeOfWin();
    window.clear();

    drawBackground();

    title.setPosition(543, 100); //from 543 to 1317
    window.draw(title);

    single_game.setPosition(711, 400);
    window.draw(single_game);

    game_with_ai.setPosition(708, 550);
    window.draw(game_with_ai);

    window.display();
}

void Gui::drawInfoMenu() {
    sizeOfWin();
    window.clear();

    drawBackground();

    title.setPosition(543, 100); //from 543 to 1317
    window.draw(title);

    //text of game rules
    sf::Text info_text("", font, 45);

    info_text.setFillColor(sf::Color(193, 12, 33)); //~42 letter per line
    info_text.setString("Welcome to SNAKE :3\n");

    info_text.setString(writeInColumn(info_text, 774));

    info_text.setPosition(543, 300);
    window.draw(info_text);

    window.display();
}

char Gui::runMainMenu() {
    while(window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }

//        if (sf::IntRect(760, 400, 340, 50).contains(sf::Mouse::getPosition(window)))
//            game_button.setColor(sf::Color::Blue); //draw new button
//        if (sf::IntRect(860, 700, 139, 50).contains(sf::Mouse::getPosition(window)))
//            exit_button.setColor(sf::Color::Blue); //draw new button

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (sf::IntRect(760, 400, 340, 50).contains(sf::Mouse::getPosition(window)))
                return 'g'; //-> go to the selection of the game mode
            if (sf::IntRect(850, 550, 140, 50).contains(sf::Mouse::getPosition(window)))
                return 'i'; //-> go to the info menu
            if (sf::IntRect(860, 700, 139, 50).contains(sf::Mouse::getPosition(window)))
                return 'c'; //-> close game
        }
    }

    return 'e'; //-> window was closed
}

char Gui::runGameMenu() {
    while(window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                return 'c';
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Q) {
                    return 'q';
                }
            }

        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))  {
            if (sf::IntRect(711, 400, 438, 50).contains(sf::Mouse::getPosition(window)))
                return 's';
            if (sf::IntRect(708, 550, 444, 50).contains(sf::Mouse::getPosition(window)))
                return 'a';
        }
    }

    return 'e'; //never
}

char Gui::runInfoMenu() {
    while(window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                return 'c';
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Q) {
                    return 'q';
                }
            }

        }
    }
    return 'e'; //error
}

std::string Gui::writeInColumn(const sf::Text& input, float column_width) {
    std::string input_string = input.getString();
    size_t text_size = input_string.size();

    std::vector<int> pos_of_columns;

    int iter_1 = 1;
    for (int i = 1; i < text_size; i++) {
        if (input.findCharacterPos(i).x > column_width * static_cast<float>(iter_1) &&
            input.findCharacterPos(i - 1).x <= column_width * static_cast<float>(iter_1)) {
            pos_of_columns.push_back(i);
            iter_1++;
        }
    }

    int iter_2 = 0;
    for (auto pos : pos_of_columns) {
//        if (input_string[pos + iter_2 - 1] == ' ')
        input_string.insert(pos + iter_2, 2, '\n');
//        else {
//            input_string.insert(pos + iter_2, 1, '-');
//            iter_2++;
//            input_string.insert(pos + iter_2, 2, '\n');
//        }
        iter_2 += 2;
    }

    return input_string;
}
