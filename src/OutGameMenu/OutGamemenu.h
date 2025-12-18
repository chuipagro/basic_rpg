/**
 * @file OutGamemenu.h
 * @author chuipagro
 * @brief 
 * @version 0.1
 * @date 12/17/25
 * * @copyright Copyright (c) 2025
 * */

#ifndef MYRPG_OUTGAMEMENU_H
#define MYRPG_OUTGAMEMENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class OutGameMenu {
public:
    OutGameMenu(sf::RenderWindow &window);
    ~OutGameMenu();

    bool run();
    int getDifficulty() const;
    int getMapSize() const;

private:
    bool handleEvents();
    void draw();
    void updateTexts();
    void updateLayout();

    sf::RenderWindow &m_window;
    sf::Font m_font;
    sf::Texture m_backgroundTexture;
    sf::Sprite m_backgroundSprite;
    sf::Texture m_cursorTexture;
    sf::Sprite m_cursorSprite;
    sf::RectangleShape m_editBox;

    sf::Text m_titleText;
    sf::Text m_difficultyText;
    sf::Text m_mapSizeText;
    sf::Text m_startText;

    int m_difficulty;
    int m_mapSize;
    int m_selectedItem; // 0: Difficulty, 1: MapSize, 2: Start
    int m_editingItem;  // -1: None, 0: Difficulty, 1: MapSize
};

#endif //MYRPG_OUTGAMEMENU_H