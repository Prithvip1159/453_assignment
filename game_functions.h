//
// Created by Prithvi on 05-04-2026.
//

#ifndef INC_453_ASSIGNMENT_GAME_FUNCTIONS_H
#define INC_453_ASSIGNMENT_GAME_FUNCTIONS_H

#include <string>
#include <vector>

using namespace std;

class Player
{
private:
    string name;
    int health;
    int lives;
    int score;
    int attack;
    int defense;

    bool has_hunters_dagger;
    bool has_healing_berries;
    bool has_cloak_of_thorns;
    bool has_ancient_amulet;
    bool has_fire_torch;
    bool has_enchanted_shield;

public:
    Player()
    {
        name = "";
        health = 100;
        lives = 3;
        score = 0;
        attack = 10;
        defense = 5;

        has_hunters_dagger = false;
        has_healing_berries = false;
        has_cloak_of_thorns = false;
        has_ancient_amulet = false;
        has_fire_torch = false;
        has_enchanted_shield = false;
    }

    Player(const string& player_name)
    {
        name = player_name;
        health = 100;
        lives = 3;
        score = 0;
        attack = 10;
        defense = 5;

        has_hunters_dagger = false;
        has_healing_berries = false;
        has_cloak_of_thorns = false;
        has_ancient_amulet = false;
        has_fire_torch = false;
        has_enchanted_shield = false;
    }

    string getName() const { return name; }
    int getHealth() const { return health; }
    int getLives() const { return lives; }
    int getScore() const { return score; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }

    bool getHuntersDagger() const { return has_hunters_dagger; }
    bool getHealingBerries() const { return has_healing_berries; }
    bool getCloakOfThorns() const { return has_cloak_of_thorns; }
    bool getAncientAmulet() const { return has_ancient_amulet; }
    bool getFireTorch() const { return has_fire_torch; }
    bool getEnchantedShield() const { return has_enchanted_shield; }

    void setName(const string& value) { name = value; }
    void setHealth(int value) { health = value; }
    void setLives(int value) { lives = value; }
    void setScore(int value) { score = value; }
    void setAttack(int value) { attack = value; }
    void setDefense(int value) { defense = value; }

    void setHuntersDagger(bool value) { has_hunters_dagger = value; }
    void setHealingBerries(bool value) { has_healing_berries = value; }
    void setCloakOfThorns(bool value) { has_cloak_of_thorns = value; }
    void setAncientAmulet(bool value) { has_ancient_amulet = value; }
    void setFireTorch(bool value) { has_fire_torch = value; }
    void setEnchantedShield(bool value) { has_enchanted_shield = value; }

    int& healthRef() { return health; }
    int& livesRef() { return lives; }
    int& scoreRef() { return score; }
    int& attackRef() { return attack; }
    int& defenseRef() { return defense; }

    bool& huntersDaggerRef() { return has_hunters_dagger; }
    bool& healingBerriesRef() { return has_healing_berries; }
    bool& cloakOfThornsRef() { return has_cloak_of_thorns; }
    bool& ancientAmuletRef() { return has_ancient_amulet; }
    bool& fireTorchRef() { return has_fire_torch; }
    bool& enchantedShieldRef() { return has_enchanted_shield; }
};

struct SceneText
{
    int id;
    string title;
    string description;
    string choice1;
    string choice2;
};

struct PuzzleData
{
    int scene_id;
    string question;
    string answer;
    int reward_score;
    int damage;
    int heal;
    string item_reward;
};

struct CombatData
{
    int scene_id;
    string enemy_name;
    int enemy_base_power;
    int damage_if_lose;
    int reward_score;
};

struct ItemData
{
    int scene_id;
    string item_name;
    string stat_type;
    int stat_bonus;
    int heal_bonus;
};

vector<SceneText> LoadScenes(const string& filename);
vector<PuzzleData> LoadPuzzles(const string& filename);
vector<CombatData> LoadCombat(const string& filename);
vector<ItemData> LoadItems(const string& filename);

SceneText GetSceneById(const vector<SceneText>& scenes, int id);
PuzzleData GetPuzzleBySceneId(const vector<PuzzleData>& puzzles, int id);
CombatData GetCombatBySceneId(const vector<CombatData>& combats, int id);
ItemData GetItemBySceneId(const vector<ItemData>& items, int id);

int ReadChoice12();
void DisplayStats(int health, int lives, int score, int attack, int defense);
void DisplayInventory(bool has_hunters_dagger, bool has_healing_berries,
                      bool has_cloak_of_thorns, bool has_ancient_amulet,
                      bool has_fire_torch, bool has_enchanted_shield);
void DisplayItemObtained(const string& item_name);
bool CheckPlayerLife(int& health, int& lives);

void SaveGame(const string& player_name, int health, int lives, int score,
              int attack, int defense, int currentScene,
              bool has_hunters_dagger, bool has_healing_berries,
              bool has_cloak_of_thorns, bool has_ancient_amulet,
              bool has_fire_torch, bool has_enchanted_shield);

bool LoadGame(string& player_name, int& health, int& lives, int& score,
              int& attack, int& defense, int& currentScene,
              bool& has_hunters_dagger, bool& has_healing_berries,
              bool& has_cloak_of_thorns, bool& has_ancient_amulet,
              bool& has_fire_torch, bool& has_enchanted_shield);

#endif //INC_453_ASSIGNMENT_GAME_FUNCTIONS_H