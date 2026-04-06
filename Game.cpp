    #include "Game.h"
    #include "ChoiceScene.h"
    #include "PuzzleScene.h"
    #include "ItemScene.h"
    #include "CombatScene.h"
    #include <iostream>
    #include <cstdlib>

    using namespace std;

    Game::Game()
    {
        currentScene = 1;

        scenes = LoadScenes("scenes.txt");
        puzzles = LoadPuzzles("puzzles.csv");
        combats = LoadCombat("combat.csv");
        items = LoadItems("items.csv");

        createScenes();
    }

    Game::~Game()
    {
        for (int i = 0; i < sceneObjects.size(); i++)
        {
            delete sceneObjects[i];
        }
    }

    void Game::createScenes()
    {
        for (int i = 0; i < scenes.size(); i++)
        {
            int id = scenes[i].id;

            if (id == 2 || id == 5 || id == 7 || id == 13 || id == 15 || id == 19)
            {
                sceneObjects.push_back(new PuzzleScene(scenes[i]));
            }
            else if (id == 3 || id == 6 || id == 9 || id == 11 || id == 17)
            {
                sceneObjects.push_back(new ItemScene(scenes[i]));
            }
            else if (id == 4 || id == 10 || id == 14 || id == 18 || id == 20 || id == 22 || id == 27)
            {
                sceneObjects.push_back(new CombatScene(scenes[i]));
            }
            else
            {
                sceneObjects.push_back(new ChoiceScene(scenes[i]));
            }
        }
    }

    void Game::start()
    {
        cout << "======= THE LOST FOREST GAME =======\n";
        cout << "You awaken at the forest's edge with no memory...\n";
        cout << "A strange green mark glows softly on your hand.\n";

        string playerName;
        cout << "\nEnter player name: ";
        getline(cin, playerName);

        player = Player(playerName);

        cout << "\nWelcome to The Lost Forest, " << player.getName() << "!\n";

        while (currentScene <= sceneObjects.size())
        {
            showMenu();
        }

        endGame();
    }

    void Game::showMenu()
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
            continueGame();
        }
        else if (choice == "2")
        {
            showInventory();
        }
        else if (choice == "3")
        {
            saveGame();
        }
        else if (choice == "4")
        {
            saveGame();
            cout << "Game saved. Exiting...\n";
            exit(0);
        }
        else
        {
            cout << "Invalid input.\n";
        }
    }

    void Game::continueGame()
    {
        sceneObjects[currentScene - 1]->play(player, puzzles, combats, items);
        currentScene++;
    }

    void Game::showInventory()
    {
        DisplayInventory(player.getHuntersDagger(),
                         player.getHealingBerries(),
                         player.getCloakOfThorns(),
                         player.getAncientAmulet(),
                         player.getFireTorch(),
                         player.getEnchantedShield());
    }

    void Game::saveGame()
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

    void Game::endGame()
    {
        cout << "\n======= THE LOST FOREST COMPLETE =======\n";
        cout << "Final Score: " << player.getScore() << endl;

        saveGame();

        cout << "\nGame automatically saved at the end!\n";
    }