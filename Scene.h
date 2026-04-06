#ifndef SCENE_H
#define SCENE_H

#include "game_functions.h"

class Scene
{
protected:
    SceneText sceneText;

public:
    Scene(const SceneText& text) : sceneText(text) {}
    virtual ~Scene() {}

    virtual void play(Player& player,
                      const vector<PuzzleData>& puzzles,
                      const vector<CombatData>& combats,
                      const vector<ItemData>& items) = 0;
};

#endif