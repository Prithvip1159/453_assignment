#include "ItemScene.h"
#include <iostream>

using namespace std;

void ItemScene::play(Player& player,
                     const vector<PuzzleData>& puzzles,
                     const vector<CombatData>& combats,
                     const vector<ItemData>& items)
{
    ItemData item = GetItemBySceneId(items, sceneText.id);

    cout << "=== Scene " << sceneText.id << " - " << sceneText.title << " ===\n";
    cout << sceneText.description << "\n";
    cout << "1) " << sceneText.choice1 << "\n";
    cout << "2) " << sceneText.choice2 << "\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        cout << "\nYou found: " << item.item_name << "\n";

        if (item.item_name == "Hunter's Dagger")
        {
            if (!player.getHuntersDagger())
            {
                player.setHuntersDagger(true);
                player.setAttack(player.getAttack() + item.stat_bonus);
                DisplayItemObtained(item.item_name);
            }
            else
            {
                cout << "You already have the Hunter's Dagger.\n";
            }
        }
        else if (item.item_name == "Healing Berries")
        {
            if (!player.getHealingBerries())
            {
                player.setHealingBerries(true);
                DisplayItemObtained(item.item_name);
            }
            else
            {
                cout << "You already have the Healing Berries.\n";
            }
        }
        else if (item.item_name == "Cloak of Thorns")
        {
            if (!player.getCloakOfThorns())
            {
                player.setCloakOfThorns(true);
                player.setDefense(player.getDefense() + item.stat_bonus);
                DisplayItemObtained(item.item_name);
            }
            else
            {
                cout << "You already have the Cloak of Thorns.\n";
            }
        }
        else if (item.item_name == "Ancient Amulet")
        {
            if (!player.getAncientAmulet())
            {
                player.setAncientAmulet(true);
                player.setAttack(player.getAttack() + item.stat_bonus);
                player.setDefense(player.getDefense() + item.stat_bonus);
                DisplayItemObtained(item.item_name);
            }
            else
            {
                cout << "You already have the Ancient Amulet.\n";
            }
        }
        else if (item.item_name == "Fire Torch")
        {
            if (!player.getFireTorch())
            {
                player.setFireTorch(true);
                DisplayItemObtained(item.item_name);
            }
            else
            {
                cout << "You already have the Fire Torch.\n";
            }
        }
        else if (item.item_name == "Enchanted Shield")
        {
            if (!player.getEnchantedShield())
            {
                player.setEnchantedShield(true);
                player.setDefense(player.getDefense() + item.stat_bonus);
                DisplayItemObtained(item.item_name);
            }
            else
            {
                cout << "You already have the Enchanted Shield.\n";
            }
        }

        if (item.heal_bonus > 0)
        {
            player.setHealth(player.getHealth() + item.heal_bonus);
            if (player.getHealth() > 100)
            {
                player.setHealth(100);
            }
        }

        player.setScore(player.getScore() + 10);
    }
    else
    {
        cout << "\nYou move on.\n";
    }

    DisplayStats(player.getHealth(), player.getLives(), player.getScore(),
                 player.getAttack(), player.getDefense());
}