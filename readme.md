# MyRPG ⚔️

![CI Status](https://github.com/username/MyRPG/actions/workflows/ci.yml/badge.svg)
![C++ Standard](https://img.shields.io/badge/C%2B%2B-23-blue.svg?logo=c%2B%2B)
![License](https://img.shields.io/badge/License-MIT-green.svg)

A modern RPG engine boilerplate built with **C++23** and **SFML**.  
This project demonstrates the use of functional programming concepts (Ranges, Views) in a game loop context.

## 🚀 Features

* **Modern C++23**: Uses `std::ranges`, `std::views`, and functional paradigms.
* **SFML**: Fast 2D rendering.
* **Automated Workflow**:
    * `CMake` for build configuration.
    * `Makefile` wrapper for easy commands.
    * GitHub Actions for CI/CD (Tests & Semantic Versioning).

## 🛠️ Prerequisites

To build this project, you need:

* **C++ Compiler**: GCC 13+ or Clang 16+ (Required for C++23 support).
* **CMake**: Version 3.14 or newer.
* **SFML**: Version 2.5+.
    * *Ubuntu/Debian:* `sudo apt install libsfml-dev`
    * *MacOS:* `brew install sfml`

## 📦 Quick Start

This project includes a Makefile wrapper to simplify CMake commands.

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/username/MyRPG.git](https://github.com/username/MyRPG.git)
    cd MyRPG
    ```

2.  **Build and Run:**
    ```bash
    make run
    ```

    *Alternatively, you can build without running:*
    ```bash
    make
    ```

3.  **Clean up:**
    ```bash
    make clean
    ```

## 🎮 Controls

| Key | Action |
| :--- | :--- |
| **Z / Q / S / D** | Move the Player |
| **Space** | Attack (Damage all enemies) |
| **Esc** | Quit Game |

## 📂 Project Structure

```text
MyRPG/
├── .github/       # CI/CD Workflows
├── assets/        # Sprites, Fonts, Audio
├── src/           # Source files (.cpp)
├── CMakeLists.txt # Build configuration
└── Makefile       # Command wrapper