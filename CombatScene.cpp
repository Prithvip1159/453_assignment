#include "CombatScene.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void CombatScene::play(Player& player,
                       const vector<PuzzleData>& puzzles,
                       const vector<CombatData>& combats,
                       const vector<ItemData>& items)
{
    CombatData combat = GetCombatBySceneId(combats, sceneText.id);

    cout << "=== Scene " << sceneText.id << " - " << sceneText.title << " ===\n";
    cout << sceneText.description << "\n";

    int player_roll = rand() % 6 + 1;
    int enemy_roll = rand() % 6 + 1;

    int player_power = player.getAttack() + player.getDefense() + player_roll;
    int enemy_power = combat.enemy_base_power + enemy_roll;

    cout << "\nYour combat power: " << player_power << endl;
    cout << combat.enemy_name << " combat power: " << enemy_power << endl;

    if (player_power >= enemy_power)
    {
        cout << "\nYou win the fight.\n";
        player.setScore(player.getScore() + combat.reward_score);
    }
    else
    {
        cout << "\nYou lose the fight.\n";
        player.setHealth(player.getHealth() - combat.damage_if_lose);
    }

    if (!CheckPlayerLife(player.healthRef(), player.livesRef()))
    {
        exit(0);
    }

    DisplayStats(player.getHealth(), player.getLives(), player.getScore(),
                 player.getAttack(), player.getDefense());
}