#ifndef PUZZLE_SCENE_H
#define PUZZLE_SCENE_H

#include "Scene.h"

class PuzzleScene : public Scene
{
public:
    PuzzleScene(const SceneText& text) : Scene(text) {}

    void play(Player& player,
              const vector<PuzzleData>& puzzles,
              const vector<CombatData>& combats,
              const vector<ItemData>& items) override;
};

#endif