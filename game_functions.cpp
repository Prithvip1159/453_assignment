//
// Created by Prithvi on 05-04-2026.
//

#include "game_functions.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;

vector<SceneText> LoadScenes(const string& filename)
{
    vector<SceneText> scenes;
    ifstream file(filename);
    string line;

    while (getline(file, line))
    {
        if (line.empty()) continue;

        stringstream ss(line);
        SceneText scene;
        string temp;

        getline(ss, temp, '|');
        if (temp.empty()) continue;
        scene.id = stoi(temp);

        getline(ss, scene.title, '|');
        getline(ss, scene.description, '|');
        getline(ss, scene.choice1, '|');
        getline(ss, scene.choice2, '|');

        scenes.push_back(scene);
    }

    return scenes;
}

vector<PuzzleData> LoadPuzzles(const string& filename)
{
    vector<PuzzleData> puzzles;
    ifstream file(filename);
    string line;

    getline(file, line);

    while (getline(file, line))
    {
        if (line.empty()) continue;

        stringstream ss(line);
        PuzzleData puzzle;
        string temp;

        getline(ss, temp, ',');
        if (temp.empty()) continue;
        puzzle.scene_id = stoi(temp);

        getline(ss, puzzle.question, ',');
        getline(ss, puzzle.answer, ',');

        getline(ss, temp, ',');
        puzzle.reward_score = stoi(temp);

        getline(ss, temp, ',');
        puzzle.damage = stoi(temp);

        getline(ss, temp, ',');
        puzzle.heal = stoi(temp);

        getline(ss, puzzle.item_reward, ',');

        puzzles.push_back(puzzle);
    }

    return puzzles;
}

vector<CombatData> LoadCombat(const string& filename)
{
    vector<CombatData> combats;
    ifstream file(filename);
    string line;

    getline(file, line);

    while (getline(file, line))
    {
        if (line.empty()) continue;

        stringstream ss(line);
        CombatData combat;
        string temp;

        getline(ss, temp, ',');
        if (temp.empty()) continue;
        combat.scene_id = stoi(temp);

        getline(ss, combat.enemy_name, ',');

        getline(ss, temp, ',');
        combat.enemy_base_power = stoi(temp);

        getline(ss, temp, ',');
        combat.damage_if_lose = stoi(temp);

        getline(ss, temp, ',');
        combat.reward_score = stoi(temp);

        combats.push_back(combat);
    }

    return combats;
}

vector<ItemData> LoadItems(const string& filename)
{
    vector<ItemData> items;
    ifstream file(filename);
    string line;

    getline(file, line);

    while (getline(file, line))
    {
        if (line.empty()) continue;

        stringstream ss(line);
        ItemData item;
        string temp;

        getline(ss, temp, ',');
        if (temp.empty()) continue;
        item.scene_id = stoi(temp);

        getline(ss, item.item_name, ',');
        getline(ss, item.stat_type, ',');

        getline(ss, temp, ',');
        item.stat_bonus = stoi(temp);

        getline(ss, temp, ',');
        item.heal_bonus = stoi(temp);

        items.push_back(item);
    }

    return items;
}

SceneText GetSceneById(const vector<SceneText>& scenes, int id)
{
    for (int i = 0; i < scenes.size(); i++)
    {
        if (scenes[i].id == id)
        {
            return scenes[i];
        }
    }

    return {0, "Unknown", "Scene not found.", "Choice 1", "Choice 2"};
}

PuzzleData GetPuzzleBySceneId(const vector<PuzzleData>& puzzles, int id)
{
    for (int i = 0; i < puzzles.size(); i++)
    {
        if (puzzles[i].scene_id == id)
        {
            return puzzles[i];
        }
    }

    return {0, "", "", 0, 0, 0, "None"};
}

CombatData GetCombatBySceneId(const vector<CombatData>& combats, int id)
{
    for (int i = 0; i < combats.size(); i++)
    {
        if (combats[i].scene_id == id)
        {
            return combats[i];
        }
    }

    return {0, "Unknown", 0, 0, 0};
}

ItemData GetItemBySceneId(const vector<ItemData>& items, int id)
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i].scene_id == id)
        {
            return items[i];
        }
    }

    return {0, "None", "none", 0, 0};
}

int ReadChoice12()
{
    string input;

    while (true)
    {
        getline(cin, input);

        if (input == "1") return 1;
        if (input == "2") return 2;

        cout << "Invalid input. Please enter 1 or 2: ";
    }
}

void DisplayStats(int health, int lives, int score, int attack, int defense)
{
    cout << "\n----------- PLAYER STATS -----------\n";
    cout << "Health  : " << health << endl;
    cout << "Lives   : " << lives << endl;
    cout << "Score   : " << score << endl;
    cout << "Attack  : " << attack << endl;
    cout << "Defense : " << defense << endl;
}

void DisplayInventory(bool has_hunters_dagger, bool has_healing_berries,
                      bool has_cloak_of_thorns, bool has_ancient_amulet,
                      bool has_fire_torch, bool has_enchanted_shield)
{
    cout << "\n---------- INVENTORY ----------\n";

    bool has_items = false;

    if (has_hunters_dagger)
    {
        cout << "- Hunter's Dagger\n";
        has_items = true;
    }
    if (has_healing_berries)
    {
        cout << "- Healing Berries\n";
        has_items = true;
    }
    if (has_cloak_of_thorns)
    {
        cout << "- Cloak of Thorns\n";
        has_items = true;
    }
    if (has_ancient_amulet)
    {
        cout << "- Ancient Amulet\n";
        has_items = true;
    }
    if (has_fire_torch)
    {
        cout << "- Fire Torch\n";
        has_items = true;
    }
    if (has_enchanted_shield)
    {
        cout << "- Enchanted Shield\n";
        has_items = true;
    }

    if (!has_items)
    {
        cout << "Empty\n";
    }
}

void DisplayItemObtained(const string& item_name)
{
    cout << "\n******************************\n";
    cout << "You have obtained: " << item_name << " *\n";
    cout << "******************************\n";
}

bool CheckPlayerLife(int& health, int& lives)
{
    if (health <= 0)
    {
        lives--;
        cout << "\nYou lost a life!\n";

        if (lives <= 0)
        {
            cout << "\nGame Over\n";
            return false;
        }

        health = 100;
        cout << "Your health has been restored to 100.\n";
    }

    return true;
}

void SaveGame(const string& player_name, int health, int lives, int score,
              int attack, int defense, int currentScene,
              bool has_hunters_dagger, bool has_healing_berries,
              bool has_cloak_of_thorns, bool has_ancient_amulet,
              bool has_fire_torch, bool has_enchanted_shield)
{
    ofstream file("savegame.txt");

    if (!file)
    {
        cout << "\nCould not save the game.\n";
        return;
    }

    file << player_name << " "
         << health << " "
         << lives << " "
         << score << " "
         << attack << " "
         << defense << " "
         << currentScene << " "
         << has_hunters_dagger << " "
         << has_healing_berries << " "
         << has_cloak_of_thorns << " "
         << has_ancient_amulet << " "
         << has_fire_torch << " "
         << has_enchanted_shield;

    file.close();
    cout << "\nGame saved successfully.\n";
}

bool LoadGame(string& player_name, int& health, int& lives, int& score,
              int& attack, int& defense, int& currentScene,
              bool& has_hunters_dagger, bool& has_healing_berries,
              bool& has_cloak_of_thorns, bool& has_ancient_amulet,
              bool& has_fire_torch, bool& has_enchanted_shield)
{
    ifstream file("savegame.txt");

    if (!file)
    {
        cout << "\nNo saved game found.\n";
        return false;
    }

    file >> player_name
         >> health
         >> lives
         >> score
         >> attack
         >> defense
         >> currentScene
         >> has_hunters_dagger
         >> has_healing_berries
         >> has_cloak_of_thorns
         >> has_ancient_amulet
         >> has_fire_torch
         >> has_enchanted_shield;

    file.close();

    cout << "\nGame loaded successfully.\n";
    return true;
}

void Scene1(int& health, int& lives, int& score, int attack, int defense,
            const vector<SceneText>& scenes)
{
    SceneText scene = GetSceneById(scenes, 1);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << "1) " << scene.choice1 << "\n";
    cout << "2) " << scene.choice2 << "\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        cout << "\nYou follow the animal trail.\n";
        cout << "The path feels steady and you make safe progress.\n";
        score += 10;
    }
    else
    {
        cout << "\nYou step into the thick fog.\n";
        cout << "Poison spores burn your lungs and weaken you.\n";
        health -= 10;
        cout << " You lost 10 health.\n";
    }

    if (!CheckPlayerLife(health, lives)) exit(0);
    DisplayStats(health, lives, score, attack, defense);
}

void Scene2(int& health, int& lives, int& score, int attack, int defense,
            const vector<SceneText>& scenes, const vector<PuzzleData>& puzzles)
{
    SceneText scene = GetSceneById(scenes, 2);
    PuzzleData puzzle = GetPuzzleBySceneId(puzzles, 2);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << puzzle.question << "\n";
    cout << "Enter your answer: ";

    string answer;
    getline(cin, answer);

    if (answer == puzzle.answer || answer == "Footsteps" || answer == "FOOTSTEPS")
    {
        cout << "\nCorrect! The stone slides aside and the path opens.\n";
        score += puzzle.reward_score;
    }
    else
    {
        cout << "\nWrong! Ancient magic strikes you.\n";
        health -= puzzle.damage;
        cout << " You lost " << puzzle.damage << " health.\n";
    }

    if (!CheckPlayerLife(health, lives)) exit(0);
    DisplayStats(health, lives, score, attack, defense);
}

void Scene3(int& score, int& attack, int health, int lives, int defense,
            bool& has_hunters_dagger,
            const vector<SceneText>& scenes, const vector<ItemData>& items)
{
    SceneText scene = GetSceneById(scenes, 3);
    ItemData item = GetItemBySceneId(items, 3);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << "1) " << scene.choice1 << "\n";
    cout << "2) " << scene.choice2 << "\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        cout << "\nYou search the tent and find a weapon hidden under a cloth.\n";

        if (!has_hunters_dagger)
        {
            has_hunters_dagger = true;
            attack += item.stat_bonus;
            DisplayItemObtained(item.item_name);
            cout << "Your attack power increases by " << item.stat_bonus << ".\n";
        }
        else
        {
            cout << "You already have the Hunter's Dagger.\n";
        }

        score += 10;
    }
    else
    {
        cout << "\nYou leave the campsite untouched and continue deeper into the forest.\n";
    }

    DisplayStats(health, lives, score, attack, defense);
}

void Scene4(int& health, int& lives, int& score, int attack, int defense,
            bool has_hunters_dagger,
            const vector<SceneText>& scenes, const vector<CombatData>& combats)
{
    SceneText scene = GetSceneById(scenes, 4);
    CombatData combat = GetCombatBySceneId(combats, 4);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";

    if (has_hunters_dagger)
    {
        cout << "You grip the Hunter's Dagger tightly.\n";
    }

    int player_roll = rand() % 6 + 1;
    int enemy_roll = rand() % 6 + 1;

    int player_power = attack + defense + player_roll;
    int enemy_power = combat.enemy_base_power + enemy_roll;

    cout << "\nYour combat power : " << player_power << endl;
    cout << combat.enemy_name << " combat power : " << enemy_power << endl;

    if (player_power >= enemy_power)
    {
        cout << "\nYou defeat the " << combat.enemy_name << ".\n";
        score += combat.reward_score;
    }
    else
    {
        cout << "\nThe " << combat.enemy_name << " overpowers you.\n";
        health -= combat.damage_if_lose;
        cout << " You lost " << combat.damage_if_lose << " health.\n";
    }

    if (!CheckPlayerLife(health, lives)) exit(0);
    DisplayStats(health, lives, score, attack, defense);
}

void Scene5(int& health, int& lives, int& score, int attack, int defense,
            bool& has_healing_berries,
            const vector<SceneText>& scenes, const vector<PuzzleData>& puzzles)
{
    SceneText scene = GetSceneById(scenes, 5);
    PuzzleData puzzle = GetPuzzleBySceneId(puzzles, 5);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << puzzle.question << "\n";
    cout << "Enter your answer: ";

    string input;
    getline(cin, input);

    if (input == puzzle.answer)
    {
        cout << "\nCorrect! The tree rewards you.\n";

        if (!has_healing_berries && puzzle.item_reward == "Healing Berries")
        {
            has_healing_berries = true;
            DisplayItemObtained("Healing Berries");
        }
        else if (has_healing_berries)
        {
            cout << "You already have the Healing Berries.\n";
        }

        health += puzzle.heal;
        if (health > 100) health = 100;

        cout << " You gained " << puzzle.heal << " health.\n";
        score += puzzle.reward_score;
    }
    else
    {
        cout << "\nWrong! The runes flash and hurt you.\n";
        health -= puzzle.damage;
        cout << " You lost " << puzzle.damage << " health.\n";
    }

    if (!CheckPlayerLife(health, lives)) exit(0);
    DisplayStats(health, lives, score, attack, defense);
}

void Scene6(int& score, int& defense, int health, int lives, int attack,
            bool& has_cloak_of_thorns,
            const vector<SceneText>& scenes, const vector<ItemData>& items)
{
    SceneText scene = GetSceneById(scenes, 6);
    ItemData item = GetItemBySceneId(items, 6);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << "1) " << scene.choice1 << "\n";
    cout << "2) " << scene.choice2 << "\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        cout << "\nYou reach inside and pull out a mysterious cloak.\n";

        if (!has_cloak_of_thorns)
        {
            has_cloak_of_thorns = true;
            defense += item.stat_bonus;
            DisplayItemObtained(item.item_name);
            cout << "Your defense increases by " << item.stat_bonus << ".\n";
        }
        else
        {
            cout << "You already have the Cloak of Thorns.\n";
        }

        score += 10;
    }
    else
    {
        cout << "\nYou decide not to risk it and move on.\n";
    }

    DisplayStats(health, lives, score, attack, defense);
}

void Scene7(int& health, int& lives, int& score, int attack, int defense,
            const vector<SceneText>& scenes, const vector<PuzzleData>& puzzles)
{
    SceneText scene = GetSceneById(scenes, 7);
    PuzzleData puzzle = GetPuzzleBySceneId(puzzles, 7);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << puzzle.question << "\n";
    cout << "Enter your answer: ";

    string answer;
    getline(cin, answer);

    if (answer == puzzle.answer || answer == "Nature" || answer == "NATURE")
    {
        cout << "\nCorrect! The spirit reveals the final path ahead.\n";
        score += puzzle.reward_score;
    }
    else
    {
        cout << "\nWrong! The spirit drains your life force.\n";
        health -= puzzle.damage;
        cout << " You lost " << puzzle.damage << " health.\n";
    }

    if (!CheckPlayerLife(health, lives)) exit(0);
    DisplayStats(health, lives, score, attack, defense);
}

void Scene8(int& health, int& lives, int& score, int attack, int defense,
            const vector<SceneText>& scenes)
{
    SceneText scene = GetSceneById(scenes, 8);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << "1) " << scene.choice1 << "\n";
    cout << "2) " << scene.choice2 << "\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        int outcome = rand() % 2;

        if (outcome == 0)
        {
            cout << "\nThe water is refreshing and magical!\n";
            cout << "You feel your wounds healing.\n";
            health += 20;
            if (health > 100) health = 100;
            cout << " You gained 20 health.\n";
            score += 10;
        }
        else
        {
            cout << "\nThe water is tainted with dark magic!\n";
            cout << "Your body weakens as poison spreads through you.\n";
            health -= 15;
            cout << " You lost 15 health.\n";
        }
    }
    else
    {
        cout << "\nYou follow the stream carefully.\n";
        cout << "It leads you safely to a new area of the forest.\n";
        score += 5;
    }

    if (!CheckPlayerLife(health, lives)) exit(0);
    DisplayStats(health, lives, score, attack, defense);
}

void Scene9(int& score, int& attack, int& defense, int& health, int lives,
            bool& has_ancient_amulet,
            const vector<SceneText>& scenes, const vector<ItemData>& items)
{
    SceneText scene = GetSceneById(scenes, 9);
    ItemData item = GetItemBySceneId(items, 9);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << "1) " << scene.choice1 << "\n";
    cout << "2) " << scene.choice2 << "\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        cout << "\nYou kneel before the shrine and close your eyes.\n";
        cout << "A warm energy surrounds you restoring your strength.\n";
        health += 10;
        if (health > 100) health = 100;
        cout << " You gained 10 health.\n";
        score += 10;
    }
    else
    {
        cout << "\nYou search behind the shrine and discover a glowing artifact!\n";

        if (!has_ancient_amulet)
        {
            has_ancient_amulet = true;
            attack += item.stat_bonus;
            defense += item.stat_bonus;
            DisplayItemObtained(item.item_name);
            cout << "Your attack increases by " << item.stat_bonus << ".\n";
            cout << "Your defense increases by " << item.stat_bonus << ".\n";
        }
        else
        {
            cout << "You already have the Ancient Amulet.\n";
        }

        score += 15;
    }

    DisplayStats(health, lives, score, attack, defense);
}

void Scene10(int& health, int& lives, int& score, int attack, int defense,
             bool has_hunters_dagger, bool has_cloak_of_thorns,
             bool has_ancient_amulet, bool& has_healing_berries,
             const vector<SceneText>& scenes, const vector<CombatData>& combats)
{
    SceneText scene = GetSceneById(scenes, 10);
    CombatData combat = GetCombatBySceneId(combats, 10);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << "1) " << scene.choice1 << "\n";
    cout << "2) " << scene.choice2 << "\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        if (has_hunters_dagger) cout << "\nYou draw the Hunter's Dagger.\n";
        if (has_cloak_of_thorns) cout << "The Cloak of Thorns shields your body.\n";
        if (has_ancient_amulet) cout << "The Ancient Amulet pulses with energy.\n";

        if (has_healing_berries)
        {
            cout << "\nYou Have Healing Berries.\n";
            cout << "Do you want to eat them before the fight?\n";
            cout << "1) Yes\n";
            cout << "2) No\n";
            cout << "Enter your choice (1 or 2): ";

            int berry_choice = ReadChoice12();

            if (berry_choice == 1)
            {
                health += 10;
                if (health > 100) health = 100;
                cout << "\nYou eat the Healing Berries.\n";
                cout << "Health restored.\n";
                has_healing_berries = false;
            }
        }

        int player_roll = rand() % 6 + 1;
        int enemy_roll = rand() % 6 + 1;

        int player_power = attack + defense + player_roll;
        int enemy_power = combat.enemy_base_power + enemy_roll;

        cout << "\nYour combat power    : " << player_power << endl;
        cout << combat.enemy_name << " combat power : " << enemy_power << endl;

        if (player_power >= enemy_power)
        {
            cout << "\nYou slay the forest serpent!\n";
            cout << "Its body dissolves into green mist.\n";
            score += combat.reward_score;
        }
        else
        {
            cout << "\nThe serpent strikes you with its venomous fangs!\n";
            health -= combat.damage_if_lose;
            cout << " You lost " << combat.damage_if_lose << " health.\n";
        }
    }
    else
    {
        cout << "\nYou turn and sprint through the trees!\n";
        cout << "The serpent's tail catches your leg as you flee.\n";
        health -= 10;
        cout << " You lost 10 health.\n";
    }

    if (!CheckPlayerLife(health, lives)) exit(0);
    DisplayStats(health, lives, score, attack, defense);
}

void Scene11(int& score, int& health, int lives, int attack, int defense,
             bool& has_fire_torch,
             const vector<SceneText>& scenes, const vector<ItemData>& items)
{
    SceneText scene = GetSceneById(scenes, 11);
    ItemData item = GetItemBySceneId(items, 11);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << "1) " << scene.choice1 << "\n";
    cout << "2) " << scene.choice2 << "\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        cout << "\nYou step inside the hut and find shelves of strange potions.\n";
        cout << "On the table you spot a burning torch that never seems to fade.\n";

        if (!has_fire_torch)
        {
            has_fire_torch = true;
            DisplayItemObtained(item.item_name);
            cout << "This will help you see in dark places.\n";
        }
        else
        {
            cout << "You already have the Fire Torch.\n";
        }

        health += 10;
        if (health > 100) health = 100;
        cout << " You gained 10 health.\n";
        score += 10;
    }
    else
    {
        cout << "\nYou walk past the hut and continue on your journey.\n";
        score += 5;
    }

    DisplayStats(health, lives, score, attack, defense);
}

void Scene12(int& health, int& lives, int& score, int attack, int defense,
             bool has_fire_torch,
             const vector<SceneText>& scenes)
{
    SceneText scene = GetSceneById(scenes, 12);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << "1) " << scene.choice1 << "\n";
    cout << "2) " << scene.choice2 << "\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        if (has_fire_torch)
        {
            cout << "\nYou light the Fire Torch and step into the tunnel.\n";
            cout << "The torch reveals the path clearly and you pass through safely.\n";
            score += 15;
        }
        else
        {
            cout << "\nYou stumble through the darkness blindly.\n";
            cout << "You trip over a rock and cut your leg on a sharp stone.\n";
            health -= 15;
            cout << " You lost 15 health.\n";
            score += 5;
        }
    }
    else
    {
        cout << "\nYou take the long way around the hill.\n";
        cout << "The path is tiring but safe.\n";
        health -= 5;
        cout << " You lost 5 health from exhaustion.\n";
        score += 5;
    }

    if (!CheckPlayerLife(health, lives)) exit(0);
    DisplayStats(health, lives, score, attack, defense);
}

void Scene13(int& health, int& lives, int& score, int attack, int defense,
             const vector<SceneText>& scenes, const vector<PuzzleData>& puzzles)
{
    SceneText scene = GetSceneById(scenes, 13);
    PuzzleData puzzle = GetPuzzleBySceneId(puzzles, 13);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << puzzle.question << "\n";
    cout << "Enter your answer: ";

    string answer;
    getline(cin, answer);

    if (answer == puzzle.answer || answer == "O")
    {
        cout << "\nCorrect! The vines part and reveal the way forward.\n";
        score += puzzle.reward_score;
    }
    else
    {
        cout << "\nWrong! The vines lash out and cut your arms.\n";
        health -= puzzle.damage;
        cout << " You lost " << puzzle.damage << " health.\n";
    }

    if (!CheckPlayerLife(health, lives)) exit(0);
    DisplayStats(health, lives, score, attack, defense);
}

void Scene14(int& health, int& lives, int& score, int attack, int defense,
             bool has_hunters_dagger, bool has_ancient_amulet,
             const vector<SceneText>& scenes, const vector<CombatData>& combats)
{
    SceneText scene = GetSceneById(scenes, 14);
    CombatData combat = GetCombatBySceneId(combats, 14);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << "1) " << scene.choice1 << "\n";
    cout << "2) " << scene.choice2 << "\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        if (has_hunters_dagger) cout << "\nYou ready the Hunter's Dagger.\n";
        if (has_ancient_amulet) cout << "The Ancient Amulet glows with power.\n";

        int player_roll = rand() % 6 + 1;
        int enemy_roll = rand() % 6 + 1;

        int player_power = attack + defense + player_roll;
        int enemy_power = combat.enemy_base_power + enemy_roll;

        cout << "\nYour combat power : " << player_power << endl;
        cout << combat.enemy_name << " combat power : " << enemy_power << endl;

        if (player_power >= enemy_power)
        {
            cout << "\nYou strike the bear down with a powerful blow!\n";
            cout << "The corruption fades from its body as it collapses.\n";
            score += combat.reward_score;
        }
        else
        {
            cout << "\nThe bear swipes you with its massive claws!\n";
            health -= combat.damage_if_lose;
            cout << " You lost " << combat.damage_if_lose << " health.\n";
        }
    }
    else
    {
        cout << "\nYou scramble up the nearest tree!\n";
        cout << "The bear claws at the trunk but cannot reach you.\n";
        cout << "However a branch snaps and you fall hitting the ground.\n";
        health -= 15;
        cout << " You lost 15 health.\n";
    }

    if (!CheckPlayerLife(health, lives)) exit(0);
    DisplayStats(health, lives, score, attack, defense);
}

void Scene15(int& health, int& lives, int& score, int attack, int defense,
             const vector<SceneText>& scenes, const vector<PuzzleData>& puzzles)
{
    SceneText scene = GetSceneById(scenes, 15);
    PuzzleData puzzle = GetPuzzleBySceneId(puzzles, 15);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << puzzle.question << "\n";
    cout << "Enter your answer: ";

    string input;
    getline(cin, input);

    if (input == puzzle.answer)
    {
        cout << "\nCorrect! The ancient door slowly opens.\n";
        score += puzzle.reward_score;
    }
    else
    {
        cout << "\nWrong! A burst of energy knocks you backwards.\n";
        health -= puzzle.damage;
        cout << " You lost " << puzzle.damage << " health.\n";
    }

    if (!CheckPlayerLife(health, lives)) exit(0);
    DisplayStats(health, lives, score, attack, defense);
}

void Scene16(int& health, int& lives, int& score, int attack, int defense,
             const vector<SceneText>& scenes)
{
    SceneText scene = GetSceneById(scenes, 16);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << "1) " << scene.choice1 << "\n";
    cout << "2) " << scene.choice2 << "\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        int outcome = rand() % 3;

        if (outcome == 0)
        {
            cout << "\nThe liquid is a powerful healing elixir!\n";
            health += 30;
            if (health > 100) health = 100;
            cout << " You gained 30 health.\n";
            score += 10;
        }
        else if (outcome == 1)
        {
            cout << "\nThe liquid burns your throat with cursed energy!\n";
            health -= 25;
            cout << " You lost 25 health.\n";
        }
        else
        {
            cout << "\nThe liquid tastes like nothing and has no effect.\n";
        }
    }
    else
    {
        cout << "\nYou hurry across the clearing.\n";
        cout << "Dark tendrils rise from the ground and scratch your legs.\n";
        health -= 5;
        cout << " You lost 5 health.\n";
        score += 5;
    }

    if (!CheckPlayerLife(health, lives)) exit(0);
    DisplayStats(health, lives, score, attack, defense);
}

void Scene17(int& score, int& defense, int& health, int lives, int attack,
             bool& has_enchanted_shield,
             const vector<SceneText>& scenes, const vector<ItemData>& items)
{
    SceneText scene = GetSceneById(scenes, 17);
    ItemData item = GetItemBySceneId(items, 17);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << "1) " << scene.choice1 << "\n";
    cout << "2) " << scene.choice2 << "\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        cout << "\nYou lift the shield from the wall.\n";
        cout << "It hums with ancient protective magic.\n";

        if (!has_enchanted_shield)
        {
            has_enchanted_shield = true;
            defense += item.stat_bonus;
            DisplayItemObtained(item.item_name);
            cout << "Your defense increases by " << item.stat_bonus << ".\n";
        }
        else
        {
            cout << "You already have the Enchanted Shield.\n";
        }

        score += 15;
    }
    else
    {
        cout << "\nYou leave the armoury and continue your journey.\n";
        score += 5;
    }

    DisplayStats(health, lives, score, attack, defense);
}

void Scene18(int& health, int& lives, int& score, int attack, int defense,
             bool has_hunters_dagger, bool has_enchanted_shield,
             const vector<SceneText>& scenes, const vector<CombatData>& combats)
{
    SceneText scene = GetSceneById(scenes, 18);
    CombatData combat = GetCombatBySceneId(combats, 18);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << "1) " << scene.choice1 << "\n";
    cout << "2) " << scene.choice2 << "\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        if (has_hunters_dagger) cout << "\nYou slash at the wolves with the Hunter's Dagger.\n";
        if (has_enchanted_shield) cout << "The Enchanted Shield blocks their attacks.\n";

        int player_roll = rand() % 6 + 1;
        int enemy_roll = rand() % 6 + 1;

        int player_power = attack + defense + player_roll;
        int enemy_power = combat.enemy_base_power + enemy_roll;

        cout << "\nYour combat power  : " << player_power << endl;
        cout << combat.enemy_name << " combat power: " << enemy_power << endl;

        if (player_power >= enemy_power)
        {
            cout << "\nYou fight off the shadow wolves!\n";
            cout << "They dissolve into black mist.\n";
            score += combat.reward_score;
        }
        else
        {
            cout << "\nThe wolves overwhelm you with their numbers!\n";
            health -= combat.damage_if_lose;
            cout << " You lost " << combat.damage_if_lose << " health.\n";
        }
    }
    else
    {
        int outcome = rand() % 2;

        if (outcome == 0)
        {
            cout << "\nYou grab a branch and wave fire at the wolves!\n";
            cout << "They scatter into the darkness.\n";
            score += 15;
        }
        else
        {
            cout << "\nThe fire does not scare them!\n";
            cout << "One wolf bites your arm before you can escape.\n";
            health -= 20;
            cout << " You lost 20 health.\n";
        }
    }

    if (!CheckPlayerLife(health, lives)) exit(0);
    DisplayStats(health, lives, score, attack, defense);
}

void Scene19(int& health, int& lives, int& score, int attack, int defense,
             const vector<SceneText>& scenes, const vector<PuzzleData>& puzzles)
{
    SceneText scene = GetSceneById(scenes, 19);
    PuzzleData puzzle = GetPuzzleBySceneId(puzzles, 19);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << puzzle.question << "\n";
    cout << "Enter your answer: ";

    string answer;
    getline(cin, answer);

    if (answer == puzzle.answer || answer == "Map" || answer == "MAP" ||
        answer == "a map" || answer == "A map" || answer == "A Map")
    {
        cout << "\nCorrect! The Elder Tree bows its branches and clears the way.\n";
        score += puzzle.reward_score;
    }
    else
    {
        cout << "\nWrong! The Elder Tree slams a branch down on you.\n";
        health -= puzzle.damage;
        cout << " You lost " << puzzle.damage << " health.\n";
    }

    if (!CheckPlayerLife(health, lives)) exit(0);
    DisplayStats(health, lives, score, attack, defense);
}

void Scene20(int& health, int& lives, int& score, int attack, int defense,
             bool has_hunters_dagger, bool has_cloak_of_thorns,
             bool has_ancient_amulet, bool has_enchanted_shield,
             const vector<SceneText>& scenes, const vector<CombatData>& combats)
{
    SceneText scene = GetSceneById(scenes, 20);
    CombatData combat = GetCombatBySceneId(combats, 20);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << "1) " << scene.choice1 << "\n";
    cout << "2) " << scene.choice2 << "\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        if (has_hunters_dagger) cout << "\nYou raise the Hunter's Dagger.\n";
        if (has_cloak_of_thorns) cout << "The Cloak of Thorns wraps around you protectively.\n";
        if (has_ancient_amulet) cout << "The Ancient Amulet blazes with light.\n";
        if (has_enchanted_shield) cout << "The Enchanted Shield forms a barrier of light.\n";

        int player_roll = rand() % 6 + 1;
        int enemy_roll = rand() % 6 + 1;

        int player_power = attack + defense + player_roll;
        int enemy_power = combat.enemy_base_power + enemy_roll;

        cout << "\nYour combat power  : " << player_power << endl;
        cout << combat.enemy_name << " combat power: " << enemy_power << endl;

        if (player_power >= enemy_power)
        {
            cout << "\nYou vanquish the forest wraith!\n";
            cout << "It screams and dissolves into green sparks of light.\n";
            cout << "The path to the Verdant Core is now open.\n";
            score += combat.reward_score;
        }
        else
        {
            cout << "\nThe wraith strikes you with its poisonous claws!\n";
            health -= combat.damage_if_lose;
            cout << " You lost " << combat.damage_if_lose << " health.\n";
        }
    }
    else
    {
        cout << "\nYou sprint past the wraith!\n";
        cout << "Its claws rake across your back as you escape.\n";
        health -= 20;
        cout << " You lost 20 health.\n";
    }

    if (!CheckPlayerLife(health, lives)) exit(0);
    DisplayStats(health, lives, score, attack, defense);
}

void Scene21(int& health, int& lives, int& score, int attack, int defense,
             const vector<SceneText>& scenes)
{
    SceneText scene = GetSceneById(scenes, 21);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << "1) " << scene.choice1 << "\n";
    cout << "2) " << scene.choice2 << "\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        cout << "\nThe runes glow brightly and the door opens slowly.\n";
        score += 15;
    }
    else
    {
        cout << "\nYou slam against the heavy door and dark magic shocks you.\n";
        health -= 10;
        cout << " You lost 10 health.\n";
    }

    if (!CheckPlayerLife(health, lives)) exit(0);
    DisplayStats(health, lives, score, attack, defense);
}

void Scene22(int& health, int& lives, int& score, int attack, int defense,
             bool has_hunters_dagger,
             const vector<SceneText>& scenes, const vector<CombatData>& combats)
{
    SceneText scene = GetSceneById(scenes, 22);
    CombatData combat = GetCombatBySceneId(combats, 22);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << "1) " << scene.choice1 << "\n";
    cout << "2) " << scene.choice2 << "\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        int player_roll = rand() % 6 + 1;
        int enemy_roll = rand() % 6 + 1;

        int player_power = attack + defense + player_roll;
        int enemy_power = combat.enemy_base_power + enemy_roll;

        cout << "\nYour combat power  : " << player_power << endl;
        cout << combat.enemy_name << " combat power: " << enemy_power << endl;

        if (player_power >= enemy_power)
        {
            cout << "\nYou defeat the wolf pack.\n";
            score += combat.reward_score;
        }
        else
        {
            cout << "\nThe wolves bite and scratch you badly.\n";
            health -= combat.damage_if_lose;
            cout << " You lost " << combat.damage_if_lose << " health.\n";
        }
    }
    else
    {
        if (has_hunters_dagger)
        {
            cout << "\nYou raise the Hunter's Dagger and the wolves back away.\n";
            score += 10;
        }
        else
        {
            cout << "\nYou try to scare them, but you have no weapon.\n";
            health -= 10;
            cout << " You lost 10 health.\n";
        }
    }

    if (!CheckPlayerLife(health, lives)) exit(0);
    DisplayStats(health, lives, score, attack, defense);
}

void Scene23(int& health, int& lives, int& score, int attack, int defense,
             const vector<SceneText>& scenes)
{
    SceneText scene = GetSceneById(scenes, 23);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << "1) " << scene.choice1 << "\n";
    cout << "2) " << scene.choice2 << "\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        cout << "\nYou wait safely until the storm passes.\n";
        score += 5;
    }
    else
    {
        cout << "\nWind and branches strike your body as you run.\n";
        health -= 15;
        cout << " You lost 15 health.\n";
    }

    if (!CheckPlayerLife(health, lives)) exit(0);
    DisplayStats(health, lives, score, attack, defense);
}

void Scene24(int& health, int& lives, int& score, int attack, int defense,
             const vector<SceneText>& scenes)
{
    SceneText scene = GetSceneById(scenes, 24);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << "1) " << scene.choice1 << "\n";
    cout << "2) " << scene.choice2 << "\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        cout << "\nYou help the traveller and give them support.\n";
        cout << "They thank you and point you toward a safer path.\n";
        score += 15;
        health += 5;
        if (health > 100) health = 100;
        cout << " You gained 5 health.\n";
    }
    else
    {
        cout << "\nYou leave the traveller behind and continue deeper into the forest.\n";
        cout << "The path ahead feels colder and more silent.\n";
        score += 5;
    }

    if (!CheckPlayerLife(health, lives)) exit(0);
    DisplayStats(health, lives, score, attack, defense);
}

void Scene25(int& health, int& lives, int& score, int attack, int defense,
             const vector<SceneText>& scenes)
{
    SceneText scene = GetSceneById(scenes, 25);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << "1) " << scene.choice1 << "\n";
    cout << "2) " << scene.choice2 << "\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        int outcome = rand() % 2;

        if (outcome == 0)
        {
            cout << "\nYou leap across the pit and land safely.\n";
            score += 15;
        }
        else
        {
            cout << "\nYou misjudge the jump and slip into the edge of the pit.\n";
            cout << "You climb out, but not without injury.\n";
            health -= 15;
            cout << " You lost 15 health.\n";
        }
    }
    else
    {
        cout << "\nYou carefully move around the unstable ground.\n";
        cout << "It is slow, but you stay safe.\n";
        score += 5;
    }

    if (!CheckPlayerLife(health, lives)) exit(0);
    DisplayStats(health, lives, score, attack, defense);
}

void Scene26(int& health, int& lives, int& score, int attack, int defense,
             const vector<SceneText>& scenes)
{
    SceneText scene = GetSceneById(scenes, 26);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << "1) " << scene.choice1 << "\n";
    cout << "2) " << scene.choice2 << "\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        cout << "\nThe lake glows and shows you a vision.\n";
        cout << "You see yourself standing before the Verdant Core.\n";
        cout << "A voice whispers that your fate is tied to the forest.\n";
        score += 15;
    }
    else
    {
        cout << "\nYou step away from the lake and continue along the path.\n";
        score += 5;
    }

    if (!CheckPlayerLife(health, lives)) exit(0);
    DisplayStats(health, lives, score, attack, defense);
}

void Scene27(int& health, int& lives, int& score, int attack, int defense,
             bool has_cloak_of_thorns,
             const vector<SceneText>& scenes, const vector<CombatData>& combats)
{
    SceneText scene = GetSceneById(scenes, 27);
    CombatData combat = GetCombatBySceneId(combats, 27);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << "1) " << scene.choice1 << "\n";
    cout << "2) " << scene.choice2 << "\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        int player_roll = rand() % 6 + 1;
        int enemy_roll = rand() % 6 + 1;

        int player_power = attack + defense + player_roll;
        int enemy_power = combat.enemy_base_power + enemy_roll;

        cout << "\nYour combat power   : " << player_power << endl;
        cout << combat.enemy_name << " combat power : " << enemy_power << endl;

        if (player_power >= enemy_power)
        {
            cout << "\nYou defeat the shadow creature.\n";
            score += combat.reward_score;
        }
        else
        {
            cout << "\nThe shadow creature tears across your chest.\n";
            health -= combat.damage_if_lose;
            cout << " You lost " << combat.damage_if_lose << " health.\n";
        }
    }
    else
    {
        if (has_cloak_of_thorns)
        {
            cout << "\nThe Cloak of Thorns glows and shields you from the attack.\n";
            cout << "The creature recoils and melts back into darkness.\n";
            score += 20;
        }
        else
        {
            cout << "\nYou reach for protection, but you have no cloak.\n";
            health -= 15;
            cout << " You lost 15 health.\n";
        }
    }

    if (!CheckPlayerLife(health, lives)) exit(0);
    DisplayStats(health, lives, score, attack, defense);
}

void Scene28(int& health, int& lives, int& score, int attack, int defense,
             const vector<SceneText>& scenes)
{
    SceneText scene = GetSceneById(scenes, 28);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << "1) " << scene.choice1 << "\n";
    cout << "2) " << scene.choice2 << "\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        cout << "\nYou force the heavy gate open and squeeze through.\n";
        cout << "The path to the inner forest is now clear.\n";
        score += 15;
    }
    else
    {
        cout << "\nYou climb the gate, but the old metal tears your hands.\n";
        health -= 15;
        cout << " You lost 15 health.\n";
    }

    if (!CheckPlayerLife(health, lives)) exit(0);
    DisplayStats(health, lives, score, attack, defense);
}

void Scene29(int& health, int& lives, int& score, int attack, int defense,
             const vector<SceneText>& scenes)
{
    SceneText scene = GetSceneById(scenes, 29);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << "1) " << scene.choice1 << "\n";
    cout << "2) " << scene.choice2 << "\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        cout << "\nThe spirits bow and allow you to pass.\n";
        cout << "A calm energy fills your body.\n";
        score += 20;
    }
    else
    {
        cout << "\nThe spirits shrink back in anger.\n";
        cout << "A dark weight settles on the path ahead.\n";
        score += 5;
    }

    if (!CheckPlayerLife(health, lives)) exit(0);
    DisplayStats(health, lives, score, attack, defense);
}

void Scene30(int& health, int& lives, int& score, int attack, int defense,
             const vector<SceneText>& scenes)
{
    SceneText scene = GetSceneById(scenes, 30);

    cout << "===Scene " << scene.id << "- " << scene.title << "===\n";
    cout << scene.description << "\n";
    cout << "1) " << scene.choice1 << "\n";
    cout << "2) " << scene.choice2 << "\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        cout << "\nYou place your hand upon the Verdant Core.\n";
        cout << "The corruption fades and life returns to the forest.\n";
        cout << "Eldoria is saved.\n";
        score += 50;
        cout << "\n=== TRUE ENDING ===\n";
    }
    else
    {
        cout << "\nYou strike the Verdant Core with all your strength.\n";
        cout << "The chamber shakes as the forest begins to collapse.\n";
        cout << "The corruption is gone, but so is the ancient magic.\n";
        cout << "\n=== DARK ENDING ===\n";
    }

    DisplayStats(health, lives, score, attack, defense);
}

void PlaySceneByNumber(int currentScene,
                       int& health, int& lives, int& score, int& attack, int& defense,
                       bool& has_hunters_dagger, bool& has_healing_berries,
                       bool& has_cloak_of_thorns, bool& has_ancient_amulet,
                       bool& has_fire_torch, bool& has_enchanted_shield,
                       const vector<SceneText>& scenes,
                       const vector<PuzzleData>& puzzles,
                       const vector<CombatData>& combats,
                       const vector<ItemData>& items)
{
    switch (currentScene)
    {
        case 1:  Scene1(health, lives, score, attack, defense, scenes); break;
        case 2:  Scene2(health, lives, score, attack, defense, scenes, puzzles); break;
        case 3:  Scene3(score, attack, health, lives, defense, has_hunters_dagger, scenes, items); break;
        case 4:  Scene4(health, lives, score, attack, defense, has_hunters_dagger, scenes, combats); break;
        case 5:  Scene5(health, lives, score, attack, defense, has_healing_berries, scenes, puzzles); break;
        case 6:  Scene6(score, defense, health, lives, attack, has_cloak_of_thorns, scenes, items); break;
        case 7:  Scene7(health, lives, score, attack, defense, scenes, puzzles); break;
        case 8:  Scene8(health, lives, score, attack, defense, scenes); break;
        case 9:  Scene9(score, attack, defense, health, lives, has_ancient_amulet, scenes, items); break;
        case 10: Scene10(health, lives, score, attack, defense, has_hunters_dagger, has_cloak_of_thorns, has_ancient_amulet, has_healing_berries, scenes, combats); break;
        case 11: Scene11(score, health, lives, attack, defense, has_fire_torch, scenes, items); break;
        case 12: Scene12(health, lives, score, attack, defense, has_fire_torch, scenes); break;
        case 13: Scene13(health, lives, score, attack, defense, scenes, puzzles); break;
        case 14: Scene14(health, lives, score, attack, defense, has_hunters_dagger, has_ancient_amulet, scenes, combats); break;
        case 15: Scene15(health, lives, score, attack, defense, scenes, puzzles); break;
        case 16: Scene16(health, lives, score, attack, defense, scenes); break;
        case 17: Scene17(score, defense, health, lives, attack, has_enchanted_shield, scenes, items); break;
        case 18: Scene18(health, lives, score, attack, defense, has_hunters_dagger, has_enchanted_shield, scenes, combats); break;
        case 19: Scene19(health, lives, score, attack, defense, scenes, puzzles); break;
        case 20: Scene20(health, lives, score, attack, defense, has_hunters_dagger, has_cloak_of_thorns, has_ancient_amulet, has_enchanted_shield, scenes, combats); break;
        case 21: Scene21(health, lives, score, attack, defense, scenes); break;
        case 22: Scene22(health, lives, score, attack, defense, has_hunters_dagger, scenes, combats); break;
        case 23: Scene23(health, lives, score, attack, defense, scenes); break;
        case 24: Scene24(health, lives, score, attack, defense, scenes); break;
        case 25: Scene25(health, lives, score, attack, defense, scenes); break;
        case 26: Scene26(health, lives, score, attack, defense, scenes); break;
        case 27: Scene27(health, lives, score, attack, defense, has_cloak_of_thorns, scenes, combats); break;
        case 28: Scene28(health, lives, score, attack, defense, scenes); break;
        case 29: Scene29(health, lives, score, attack, defense, scenes); break;
        case 30: Scene30(health, lives, score, attack, defense, scenes); break;
    }
}
