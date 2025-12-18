cmake_minimum_required(VERSION 3.14)

project(MyRPG VERSION 1.0 LANGUAGES CXX)

# Force C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

add_compile_options(-Wall -Wextra -Wpedantic)

set(SOURCES
        src/Main.cpp
        src/OutGameMenu/OutGamemenu.cpp
        src/OutGameMenu/OutGamemenu.h
        src/Map/Map.cpp
        src/Map/Map.h
)

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

include_directories(include)

add_executable(MyRPG ${SOURCES})

target_link_libraries(MyRPG sfml-graphics sfml-window sfml-system sfml-audio)

enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(MyRPG_Tests
        test/Test.cpp)
target_link_libraries(MyRPG_Tests GTest::gtest_main sfml-system)

include(GoogleTest)
gtest_discover_tests(MyRPG_Tests)