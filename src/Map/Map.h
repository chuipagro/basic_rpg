/**
* @file Map.h
 * @author chuipagro
 * @brief
 * @version 0.1
 * @date 12/17/25
 * * @copyright Copyright (c) 2025
 * */

#ifndef MYRPG_MAP_H
#define MYRPG_MAP_H

#include <vector>
#include <SFML/Graphics.hpp>

class Map {
public:
    Map(int size);
    ~Map();

    void generate();
    void draw(sf::RenderWindow &window);
    void print();
    void setCurrentRoom(int x, int y);

private:
    void generateLabyrinth();
    void carvePath(int x1, int y1, int x2, int y2);

    int m_size;
    sf::Vector2i m_currentRoom;
    std::vector<std::vector<int>> m_grid;
    sf::Texture m_tileTexture;
    sf::Sprite m_tileSprite;
};

#endif //MYRPG_MAP_H