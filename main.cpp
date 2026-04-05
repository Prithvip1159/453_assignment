#include "game_functions.h"
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    srand(time(0));

    vector<SceneText> scenes = LoadScenes("scenes.txt");
    vector<PuzzleData> puzzles = LoadPuzzles("puzzles.csv");
    vector<CombatData> combats = LoadCombat("combat.csv");
    vector<ItemData> items = LoadItems("items.csv");

    cout << "=======THE LOST FOREST GAME=======\n";
    cout << "You awaken at the forest's edge with no memory...\n";
    cout << "A strange green mark glows softly on your hand.\n";

    string player_name;
    cout << "\nEnter player name: ";
    getline(cin, player_name);

    Player player(player_name);
    int currentScene = 1;

    cout << "\nWelcome to The Lost Forest, " << player.getName() << "!\n";

    while (currentScene <= 30)
    {
        cout << "\n=========== GAME MENU ===========\n";
        cout << "1. Continue\n";
        cout << "2. Show Inventory\n";
        cout << "3. Save Game\n";
        cout << "4. Exit\n";
        cout << "Choose: ";

        string choice;
        getline(cin, choice);

        if (choice == "1")
        {
            PlaySceneByNumber(currentScene,
                              player.healthRef(),
                              player.livesRef(),
                              player.scoreRef(),
                              player.attackRef(),
                              player.defenseRef(),
                              player.huntersDaggerRef(),
                              player.healingBerriesRef(),
                              player.cloakOfThornsRef(),
                              player.ancientAmuletRef(),
                              player.fireTorchRef(),
                              player.enchantedShieldRef(),
                              scenes, puzzles, combats, items);

            currentScene++;
            if (choice == "1")
            {
                PlaySceneByNumber(currentScene,
                                  player.healthRef(),
                                  player.livesRef(),
                                  player.scoreRef(),
                                  player.attackRef(),
                                  player.defenseRef(),
                                  player.huntersDaggerRef(),
                                  player.healingBerriesRef(),
                                  player.cloakOfThornsRef(),
                                  player.ancientAmuletRef(),
                                  player.fireTorchRef(),
                                  player.enchantedShieldRef(),
                                  scenes, puzzles, combats, items);

                currentScene++;

                SaveGame(player.getName(),
                         player.getHealth(),
                         player.getLives(),
                         player.getScore(),
                         player.getAttack(),
                         player.getDefense(),
                         currentScene,
                         player.getHuntersDagger(),
                         player.getHealingBerries(),
                         player.getCloakOfThorns(),
                         player.getAncientAmulet(),
                         player.getFireTorch(),
                         player.getEnchantedShield());
                
            }
        }
        else if (choice == "2")
        {

            DisplayInventory(player.getHuntersDagger(),
                             player.getHealingBerries(),
                             player.getCloakOfThorns(),
                             player.getAncientAmulet(),
                             player.getFireTorch(),
                             player.getEnchantedShield());
        }
        else if (choice == "3")
        {
            SaveGame(player.getName(),
                     player.getHealth(),
                     player.getLives(),
                     player.getScore(),
                     player.getAttack(),
                     player.getDefense(),
                     currentScene,
                     player.getHuntersDagger(),
                     player.getHealingBerries(),
                     player.getCloakOfThorns(),
                     player.getAncientAmulet(),
                     player.getFireTorch(),
                     player.getEnchantedShield());
        }
        else if (choice == "4")
        {
            SaveGame(player.getName(),
             player.getHealth(),
             player.getLives(),
             player.getScore(),
             player.getAttack(),
             player.getDefense(),
             currentScene,
             player.getHuntersDagger(),
             player.getHealingBerries(),
             player.getCloakOfThorns(),
             player.getAncientAmulet(),
             player.getFireTorch(),
             player.getEnchantedShield());

            cout << "Exiting game...\n";
            return 0;
        }
        else
        {
            cout << "Invalid input\n";
        }
    }

    cout << "\n=======THE LOST FOREST COMPLETE=======\n";
    cout << "Final Score: " << player.getScore() << endl;

    SaveGame(player.getName(),
         player.getHealth(),
         player.getLives(),
         player.getScore(),
         player.getAttack(),
         player.getDefense(),
         currentScene,
         player.getHuntersDagger(),
         player.getHealingBerries(),
         player.getCloakOfThorns(),
         player.getAncientAmulet(),
         player.getFireTorch(),
         player.getEnchantedShield());

    cout << "\nGame automatically saved at the end!\n";

    return 0;
}