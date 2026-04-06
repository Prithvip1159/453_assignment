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

        file << "Name=" << player_name
             << ",Health=" << health
             << ",Lives=" << lives
             << ",Score=" << score
             << ",Attack=" << attack
             << ",Defense=" << defense
             << ",CurrentScene=" << currentScene
             << ",HuntersDagger=" << has_hunters_dagger
             << ",HealingBerries=" << has_healing_berries
             << ",CloakOfThorns=" << has_cloak_of_thorns
             << ",AncientAmulet=" << has_ancient_amulet
             << ",FireTorch=" << has_fire_torch
             << ",EnchantedShield=" << has_enchanted_shield
             << endl;

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

        string line, lastLine;
        while (getline(file, line))
        {
            if (!line.empty())
            {
                lastLine = line;
            }
        }
        file.close();

        if (lastLine.empty())
        {
            cout << "\nNo saved game data found.\n";
            return false;
        }

        vector<string> parts;
        string temp;
        stringstream ss(lastLine);

        while (getline(ss, temp, ','))
        {
            parts.push_back(temp);
        }

        if (parts.size() != 13)
        {
            cout << "\nSaved game format is invalid.\n";
            return false;
        }

        auto getValue = [](string part) -> string
        {
            size_t pos = part.find('=');
            if (pos != string::npos)
            {
                return part.substr(pos + 1);
            }
            return "";
        };

        player_name = getValue(parts[0]);
        health = stoi(getValue(parts[1]));
        lives = stoi(getValue(parts[2]));
        score = stoi(getValue(parts[3]));
        attack = stoi(getValue(parts[4]));
        defense = stoi(getValue(parts[5]));
        currentScene = stoi(getValue(parts[6]));
        has_hunters_dagger = stoi(getValue(parts[7]));
        has_healing_berries = stoi(getValue(parts[8]));
        has_cloak_of_thorns = stoi(getValue(parts[9]));
        has_ancient_amulet = stoi(getValue(parts[10]));
        has_fire_torch = stoi(getValue(parts[11]));
        has_enchanted_shield = stoi(getValue(parts[12]));

        cout << "\nGame loaded successfully.\n";
        return true;
    }
