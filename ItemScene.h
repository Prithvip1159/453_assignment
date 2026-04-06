#ifndef ITEM_SCENE_H
#define ITEM_SCENE_H

#include "Scene.h"

class ItemScene : public Scene
{
public:
    ItemScene(const SceneText& text) : Scene(text) {}

    void play(Player& player,
              const vector<PuzzleData>& puzzles,
              const vector<CombatData>& combats,
              const vector<ItemData>& items) override;
};

#endif