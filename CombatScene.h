#ifndef COMBAT_SCENE_H
#define COMBAT_SCENE_H

#include "Scene.h"

class CombatScene : public Scene
{
public:
    CombatScene(const SceneText& text) : Scene(text) {}

    void play(Player& player,
              const vector<PuzzleData>& puzzles,
              const vector<CombatData>& combats,
              const vector<ItemData>& items) override;
};

#endif