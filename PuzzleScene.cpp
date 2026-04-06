#include "PuzzleScene.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void PuzzleScene::play(Player& player,
                       const vector<PuzzleData>& puzzles,
                       const vector<CombatData>& combats,
                       const vector<ItemData>& items)
{
    PuzzleData puzzle = GetPuzzleBySceneId(puzzles, sceneText.id);

    cout << "=== Scene " << sceneText.id << " - " << sceneText.title << " ===\n";
    cout << sceneText.description << "\n";
    cout << puzzle.question << "\n";
    cout << "Enter your answer: ";

    string answer;
    getline(cin, answer);

    if (answer == puzzle.answer)
    {
        cout << "\nCorrect!\n";
        player.setScore(player.getScore() + puzzle.reward_score);
    }
    else
    {
        cout << "\nWrong answer!\n";
        player.setHealth(player.getHealth() - puzzle.damage);
    }

    if (!CheckPlayerLife(player.healthRef(), player.livesRef()))
    {
        exit(0);
    }

    DisplayStats(player.getHealth(), player.getLives(), player.getScore(),
                 player.getAttack(), player.getDefense());
}