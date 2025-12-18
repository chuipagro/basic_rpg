/**
 * @file Main
 * @author chuipagro
 * @brief 
 * @version 0.1
 * @date 12/17/25
 * * @copyright Copyright (c) 2025
 * */

#include "OutGameMenu/OutGamemenu.h"
#include "Map/Map.h"
#include <iostream>

int main(int ac, char **av)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "MyRPG");
    OutGameMenu menu(window);

    if (menu.run()) {
        int difficulty = menu.getDifficulty();
        int mapSize = menu.getMapSize();

        std::cout << "Starting game with..." << std::endl;
        std::cout << "Difficulty: " << difficulty << std::endl;
        std::cout << "Map Size: " << mapSize << std::endl;

        Map gameMap(mapSize);
        gameMap.generate();
        gameMap.print();
        gameMap.setCurrentRoom(0, 0);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            window.clear();
            gameMap.draw(window);
            window.display();
        }
    }

    return 0;
}