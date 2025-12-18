/**
 * @file Map.cpp
 * @author your name
 * @brief
 * @version 0.1
 * @date 2023-10-29
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "Map.h"
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

Map::Map(int size) : m_size(size), m_currentRoom(0, 0) {
    if (!m_tileTexture.loadFromFile("../assets/map_tile.png")) {
        std::cerr << "Error loading map tile texture" << std::endl;
    }
    m_tileSprite.setTexture(m_tileTexture);
    m_grid.resize(m_size * 21, std::vector<int>(m_size * 21, 1)); // 1 for wall, 0 for path
}

Map::~Map() {}

void Map::generate() {
    generateLabyrinth();
}

void Map::setCurrentRoom(int x, int y) {
    m_currentRoom.x = x;
    m_currentRoom.y = y;
}

void Map::generateLabyrinth() {
    // Create rooms
    for (int i = 0; i < m_size; ++i) {
        for (int j = 0; j < m_size; ++j) {
            for (int row = 1; row < 20; ++row) {
                for (int col = 1; col < 20; ++col) {
                    m_grid[i * 21 + row][j * 21 + col] = 0;
                }
            }
        }
    }

    // Generate maze using Prim's algorithm
    std::vector<std::pair<int, int>> frontiers;
    std::vector<std::pair<int, int>> in_maze;
    std::random_device rd;
    std::mt19937 g(rd());

    in_maze.push_back({0, 0});

    if (0 + 1 < m_size) frontiers.push_back({0, 1});
    if (0 + 1 < m_size) frontiers.push_back({1, 0});

    while (!frontiers.empty()) {
        std::uniform_int_distribution<> distrib(0, frontiers.size() - 1);
        int frontier_idx = distrib(g);
        std::pair<int, int> frontier = frontiers[frontier_idx];
        frontiers.erase(frontiers.begin() + frontier_idx);

        std::vector<std::pair<int, int>> neighbors;
        if (frontier.second > 0) {
            auto it = std::find(in_maze.begin(), in_maze.end(), std::make_pair(frontier.first, frontier.second - 1));
            if (it != in_maze.end()) neighbors.push_back({frontier.first, frontier.second - 1});
        }
        if (frontier.second < m_size - 1) {
            auto it = std::find(in_maze.begin(), in_maze.end(), std::make_pair(frontier.first, frontier.second + 1));
            if (it != in_maze.end()) neighbors.push_back({frontier.first, frontier.second + 1});
        }
        if (frontier.first > 0) {
            auto it = std::find(in_maze.begin(), in_maze.end(), std::make_pair(frontier.first - 1, frontier.second));
            if (it != in_maze.end()) neighbors.push_back({frontier.first - 1, frontier.second});
        }
        if (frontier.first < m_size - 1) {
            auto it = std::find(in_maze.begin(), in_maze.end(), std::make_pair(frontier.first + 1, frontier.second));
            if (it != in_maze.end()) neighbors.push_back({frontier.first + 1, frontier.second});
        }

        if (!neighbors.empty()) {
            std::uniform_int_distribution<> distrib_n(0, neighbors.size() - 1);
            int neighbor_idx = distrib_n(g);
            std::pair<int, int> neighbor = neighbors[neighbor_idx];
            carvePath(frontier.first, frontier.second, neighbor.first, neighbor.second);
        }

        in_maze.push_back(frontier);

        if (frontier.second > 0 && std::find(in_maze.begin(), in_maze.end(), std::make_pair(frontier.first, frontier.second - 1)) == in_maze.end()) frontiers.push_back({frontier.first, frontier.second - 1});
        if (frontier.second < m_size - 1 && std::find(in_maze.begin(), in_maze.end(), std::make_pair(frontier.first, frontier.second + 1)) == in_maze.end()) frontiers.push_back({frontier.first, frontier.second + 1});
        if (frontier.first > 0 && std::find(in_maze.begin(), in_maze.end(), std::make_pair(frontier.first - 1, frontier.second)) == in_maze.end()) frontiers.push_back({frontier.first - 1, frontier.second});
        if (frontier.first < m_size - 1 && std::find(in_maze.begin(), in_maze.end(), std::make_pair(frontier.first + 1, frontier.second)) == in_maze.end()) frontiers.push_back({frontier.first + 1, frontier.second});
    }
}

void Map::carvePath(int x1, int y1, int x2, int y2) {
    if (x1 == x2) { // Vertical door
        int doorY = (y1 < y2) ? y1 * 21 + 20 : y2 * 21 + 20;
        for (int i = 8; i < 13; ++i) m_grid[doorY][x1 * 21 + i] = 2; // 2 for vertical door
    } else { // Horizontal door
        int doorX = (x1 < x2) ? x1 * 21 + 20 : x2 * 21 + 20;
        for (int i = 8; i < 13; ++i) m_grid[y1 * 21 + i][doorX] = 3; // 3 for horizontal door
    }
}

void Map::draw(sf::RenderWindow &window) {
    int startX = m_currentRoom.x * 21;
    int startY = m_currentRoom.y * 21;
    sf::Vector2u windowSize = window.getSize();
    float tileWidth = (float)windowSize.x / 21.0f;
    float tileHeight = (float)windowSize.y / 21.0f;

    for (int i = 0; i < 21; ++i) {
        for (int j = 0; j < 21; ++j) {
            int tileType = m_grid[startY + i][startX + j];
            if (tileType == 1) { // Wall
                m_tileSprite.setTextureRect(sf::IntRect(256, 0, 128, 128)); // Using Wall 1 for now
            } else if (tileType == 0) { // Floor
                m_tileSprite.setTextureRect(sf::IntRect(0, 0, 128, 128)); // Using Floor 1 for now
            } else if (tileType == 2) { // Vertical Door
                m_tileSprite.setTextureRect(sf::IntRect(128, 128, 128, 128));
            } else if (tileType == 3) { // Horizontal Door
                m_tileSprite.setTextureRect(sf::IntRect(256, 128, 128, 128));
            }
            m_tileSprite.setScale(tileWidth / 128.0f, tileHeight / 128.0f);
            m_tileSprite.setPosition(j * tileWidth, i * tileHeight);
            window.draw(m_tileSprite);
        }
    }
}

void Map::print() {
    for (const auto& row : m_grid) {
        for (int cell : row) {
            std::cout << (cell == 1 ? '#' : ' ');
        }
        std::cout << std::endl;
    }
}