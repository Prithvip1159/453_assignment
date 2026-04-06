#ifndef CHOICE_SCENE_H
#define CHOICE_SCENE_H

#include "Scene.h"

class ChoiceScene : public Scene
{
public:
    ChoiceScene(const SceneText& text) : Scene(text) {}

    void play(Player& player,
              const vector<PuzzleData>& puzzles,
              const vector<CombatData>& combats,
              const vector<ItemData>& items) override;
};

#endif