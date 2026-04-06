cmake_minimum_required(VERSION 4.1)
project(453_assignment)

set(CMAKE_CXX_STANDARD 20)

add_executable(453_assignment main.cpp
        game_functions.h
        game_functions.cpp
        Game.h
        Game.cpp
        Scene.h
        ChoiceScene.h
        PuzzleScene.h
        ItemScene.h
        CombatScene.h
        ChoiceScene.cpp
        PuzzleScene.cpp
        ItemScene.cpp
        CombatScene.cpp
)
