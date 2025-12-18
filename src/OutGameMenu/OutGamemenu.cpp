/**
 * @file OutGamemenu.cpp
 * @author chuipagro
 * @brief 
 * @version 0.1
 * @date 12/17/25
 * * @copyright Copyright (c) 2025
 * */

#include "OutGamemenu.h"
#include <iostream>

OutGameMenu::OutGameMenu(sf::RenderWindow &window) : m_window(window), m_difficulty(1), m_mapSize(20), m_selectedItem(-1), m_editingItem(-1) {
    if (!m_font.loadFromFile("../assets/OutGameMenu/menu.otf")) {
        std::cerr << "Error loading font" << std::endl;
    }
    if (!m_backgroundTexture.loadFromFile("../assets/OutGameMenu/background_menu_light.png")) {
        std::cerr << "Error loading background texture" << std::endl;
    }
    if (!m_cursorTexture.loadFromFile("../assets/OutGameMenu/cursor.png")) {
        std::cerr << "Error loading cursor texture" << std::endl;
    }

    m_backgroundSprite.setTexture(m_backgroundTexture);
    m_cursorSprite.setTexture(m_cursorTexture);

    m_editBox.setFillColor(sf::Color::Transparent);
    m_editBox.setOutlineColor(sf::Color::White);
    m_editBox.setOutlineThickness(2);

    m_titleText.setFont(m_font);
    m_titleText.setString("Settings");

    m_difficultyText.setFont(m_font);
    m_mapSizeText.setFont(m_font);
    m_startText.setFont(m_font);
    m_startText.setString("Start");

    updateLayout();
    updateTexts();
}

OutGameMenu::~OutGameMenu() {}

bool OutGameMenu::run() {
    while (m_window.isOpen()) {
        if (handleEvents()) {
            return true;
        }
        draw();
    }
    return false;
}

bool OutGameMenu::handleEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }
        if (event.type == sf::Event::Resized) {
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            m_window.setView(sf::View(visibleArea));
            updateLayout();
        }

        if (m_editingItem != -1) {
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                    if (m_editingItem == 0) {
                        m_difficulty = m_difficulty * 10 + (event.text.unicode - '0');
                    } else if (m_editingItem == 1) {
                        m_mapSize = m_mapSize * 10 + (event.text.unicode - '0');
                    }
                    updateTexts();
                }
            }
             if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace) {
                if (m_editingItem == 0) {
                    m_difficulty /= 10;
                } else if (m_editingItem == 1) {
                    m_mapSize /= 10;
                }
                updateTexts();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                m_editingItem = -1;
            }
        } else {
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
                if (m_difficultyText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    m_selectedItem = 0;
                } else if (m_mapSizeText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    m_selectedItem = 1;
                } else if (m_startText.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    m_selectedItem = 2;
                } else {
                    m_selectedItem = -1;
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (m_selectedItem == 0) {
                        m_editingItem = 0;
                        m_difficulty = 0;
                        updateTexts();
                    } else if (m_selectedItem == 1) {
                        m_editingItem = 1;
                        m_mapSize = 0;
                        updateTexts();
                    } else if (m_selectedItem == 2) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void OutGameMenu::updateLayout() {
    sf::Vector2u windowSize = m_window.getSize();
    sf::Vector2u textureSize = m_backgroundTexture.getSize();

    float scaleX = (float)windowSize.x / textureSize.x;
    float scaleY = (float)windowSize.y / textureSize.y;
    m_backgroundSprite.setScale(scaleX, scaleY);

    float scale = windowSize.y / 600.0f;

    m_titleText.setCharacterSize(50 * scale);

    m_titleText.setPosition(windowSize.x / 2.0f - m_titleText.getGlobalBounds().width / 2.0f, 50 * scale);

    m_difficultyText.setCharacterSize(30 * scale);
    m_difficultyText.setPosition(windowSize.x / 2.0f - m_difficultyText.getGlobalBounds().width / 2.0f, 200 * scale);

    m_mapSizeText.setCharacterSize(30 * scale);
    m_mapSizeText.setPosition(windowSize.x / 2.0f - m_mapSizeText.getGlobalBounds().width / 2.0f, 300 * scale);

    m_startText.setCharacterSize(30 * scale);
    m_startText.setPosition(windowSize.x / 2.0f - m_startText.getGlobalBounds().width / 2.0f, 400 * scale);

    m_cursorSprite.setScale(0.1f * scale, 0.1f * scale);
}

void OutGameMenu::updateTexts() {
    m_difficultyText.setString("Difficulty: " + std::to_string(m_difficulty));
    m_mapSizeText.setString("Map Size: " + std::to_string(m_mapSize));
    updateLayout();
}

void OutGameMenu::draw() {
    m_window.clear();
    m_window.draw(m_backgroundSprite);
    m_window.draw(m_titleText);
    m_window.draw(m_difficultyText);
    m_window.draw(m_mapSizeText);
    m_window.draw(m_startText);

    sf::Text* selectedText = nullptr;
    if (m_editingItem != -1) {
        if (m_editingItem == 0) selectedText = &m_difficultyText;
        else selectedText = &m_mapSizeText;

        sf::FloatRect bounds = selectedText->getGlobalBounds();
        std::string numStr = (m_editingItem == 0) ? std::to_string(m_difficulty) : std::to_string(m_mapSize);
        sf::Text numText(numStr, m_font, selectedText->getCharacterSize());
        numText.setPosition(bounds.left + bounds.width - numText.getGlobalBounds().width, bounds.top);

        sf::FloatRect numBounds = numText.getGlobalBounds();
        m_editBox.setSize(sf::Vector2f(numBounds.width + 10, numBounds.height + 10));
        m_editBox.setPosition(numBounds.left - 5, numBounds.top - 5);
        m_window.draw(m_editBox);

    } else if (m_selectedItem != -1) {
        if (m_selectedItem == 0) selectedText = &m_difficultyText;
        else if (m_selectedItem == 1) selectedText = &m_mapSizeText;
        else selectedText = &m_startText;
    }

    if (selectedText && m_editingItem == -1) {
        sf::FloatRect bounds = selectedText->getGlobalBounds();
        m_cursorSprite.setPosition(bounds.left - m_cursorSprite.getGlobalBounds().width - 5, bounds.top + bounds.height / 2 - m_cursorSprite.getGlobalBounds().height / 2);
        m_window.draw(m_cursorSprite);
        m_cursorSprite.setPosition(bounds.left + bounds.width + 5, bounds.top + bounds.height / 2 - m_cursorSprite.getGlobalBounds().height / 2);
        m_window.draw(m_cursorSprite);
    }

    m_window.display();
}

int OutGameMenu::getDifficulty() const {
    return m_difficulty;
}

int OutGameMenu::getMapSize() const {
    return m_mapSize;
}