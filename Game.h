#ifndef GAME_H
#define GAME_H

#include "game_functions.h"
#include "Scene.h"
#include <vector>

using namespace std;

class Game
{
private:
    Player player;
    int currentScene;

    vector<SceneText> scenes;
    vector<PuzzleData> puzzles;
    vector<CombatData> combats;
    vector<ItemData> items;

    vector<Scene*> sceneObjects;

public:
    Game();
    ~Game();

    void start();
    void showMenu();
    void continueGame();
    void showInventory();
    void saveGame();
    void endGame();
    void createScenes();
};

#endif