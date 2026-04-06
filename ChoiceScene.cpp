#include "ChoiceScene.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void ChoiceScene::play(Player& player,
                       const vector<PuzzleData>& puzzles,
                       const vector<CombatData>& combats,
                       const vector<ItemData>& items)
{
    cout << "=== Scene " << sceneText.id << " - " << sceneText.title << " ===\n";
    cout << sceneText.description << "\n";
    cout << "1) " << sceneText.choice1 << "\n";
    cout << "2) " << sceneText.choice2 << "\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        cout << "\nYou chose option 1.\n";
        player.setScore(player.getScore() + 10);
    }
    else
    {
        cout << "\nYou chose option 2.\n";
        player.setHealth(player.getHealth() - 10);
    }

    if (!CheckPlayerLife(player.healthRef(), player.livesRef()))
    {
        exit(0);
    }

    DisplayStats(player.getHealth(), player.getLives(), player.getScore(),
                 player.getAttack(), player.getDefense());
}