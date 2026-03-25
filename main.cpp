#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// reads only choice 1 or 2
int ReadChoice12()
{
    string input = "";
    bool valid = false;
    int choice = 0;

    while (!valid)
    {
        getline(cin, input);

        if (input == "1")
        {
            choice = 1;
            valid = true;
        }
        else if (input == "2")
        {
            choice = 2;
            valid = true;
        }
        else
        {
            cout << "Invalid input. Please enter 1 or 2: ";
        }
    }

    return choice;
}

// displays current player stats
void DisplayStats(int health, int lives, int score, int attack, int defense)
{
    cout << "\n----------- PLAYER STATUS -----------\n";
    cout << "Health  : " << health << endl;
    cout << "Lives   : " << lives << endl;
    cout << "Score   : " << score << endl;
    cout << "Attack  : " << attack << endl;
    cout << "Defense : " << defense << endl;
}

// displays simple inventory
void DisplayInventory(bool has_hunters_dagger, bool has_healing_berries,
                      bool has_cloak_of_thorns, bool has_ancient_amulet,
                      bool has_fire_torch,bool has_enchanted_shield)
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

// displays a message when the player obtains a new item
void DisplayItemObtained(const string& item_name)
{
    cout << "\n******************************\n";
    cout << "* You have obtained: " << item_name << " *\n";
    cout << "******************************\n";
}

// checks if the player has lost all health
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

// scene 1 - opening choice
void Scene1(int& health, int& lives, int& score, int attack, int defense)
{
    cout << "===Scene 1- Forest Entrance===\n";

    cout << "You stand at the edge of the forest.\n";
    cout << "Two paths appear before you:\n\n";
    cout << "1) Follow the narrow animal trail (safer)\n";
    cout << "2) Step directly into the thick fog (dangerous)\n";
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
        health -= 10; // fog damages the player
        cout << " You lost 10 health.\n";
    }

    if (!CheckPlayerLife(health, lives))
        exit(0);

    DisplayStats(health, lives, score, attack, defense);
}

// scene 2 - puzzle scene
void Scene2(int& health, int& lives, int& score, int attack, int defense)
{
    cout << "===Scene 2- The Stone Riddle===\n";

    cout << "A moss-covered stone blocks the path.\n";
    cout << "\"The more you take, the more you leave behind. What am I?\"\n";
    cout << "Enter your answer: ";

    string answer;
    getline(cin, answer);

    if (answer == "footsteps" || answer == "Footsteps" || answer == "FOOTSTEPS")
    {
        cout << "\nCorrect! The  stone  slides aside and the path opens.\n";
        score += 10;
    }
    else
    {
        cout << "\nWrong!  Ancient magic  strikes you.\n";
        health -= 5; // wrong answer reduces health
        cout << " You lost 5 health.\n";
    }

    if (!CheckPlayerLife(health, lives))
        exit(0);

    DisplayStats(health, lives, score, attack, defense);
}

// scene 3 - item collection
void Scene3(int& score, int& attack, int health, int lives, int defense, bool& has_hunters_dagger)
{
    cout << "===Scene 3- Abandoned Campsite===\n";

    cout << "You discover  an abandoned  campsite hidden between twisted trees.\n";
    cout << "1) Search the  tent\n";
    cout << "2) Ignore  it and  continue\n";
    cout << "Enter your  choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        cout << "\nYou search  the tent and find a weapon hidden under a cloth.\n";

        if (!has_hunters_dagger)
        {
            has_hunters_dagger = true;
            attack += 5; // dagger increases attack
            DisplayItemObtained("Hunter's Dagger");
            cout << "Your attack power increases by 5.\n";
        }
        else
        {
            cout << "You already have the Hunter's Dagger.\n";
        }

        score += 10;
    }
    else
    {
        cout << "\nYou leave the  campsite untouched  and continue deeper into the forest.\n";
    }

    DisplayStats(health, lives, score, attack, defense);
}

// scene 4 - combat scene
void Scene4(int& health, int& lives, int& score, int attack, int defense, bool has_hunters_dagger)
{
    cout << "===Scene 4- Corrupted Forest Wolf===\n";

    cout << "A corrupted  forest wolf leaps  from the bushes.\n";
    cout << "Its glowing red eyes  lock onto you.\n";

    if (has_hunters_dagger)
    {
        cout << "You grip the Hunter's  Dagger tightly.\n";
    }

    // random combat values
    int player_roll = rand() % 6 + 1;
    int wolf_roll = rand() % 6 + 1;

    int player_power = attack + defense + player_roll;
    int wolf_power = 12 + wolf_roll;

    cout << "\nYour combat power : " << player_power << endl;
    cout << "Wolf  combat power : " << wolf_power << endl;

    if (player_power >= wolf_power)
    {
        cout << "\nYou defeat  the corrupted wolf.\n";
        score += 15;
    }
    else
    {
        cout << "\nThe wolf overpowers  you and leaves  deep wounds.\n";
        health -= 20; // wolf attack damages the player
        cout << " You lost 20 health.\n";
    }

    if (!CheckPlayerLife(health, lives))
        exit(0);

    DisplayStats(health, lives, score, attack, defense);
}

// scene 5 - math puzzle
void Scene5(int& health, int& lives, int& score, int attack, int defense, bool& has_healing_berries)
{
    cout << "===Scene 5- The Rune Tree===\n";

    cout << "Glowing  runes appear across  the bark of a  huge tree.\n";
    cout << "\"There are 3 sacred roots  and 4 branches  on each.\"\n";
    cout << "\"How  many branches grow  in total?\"\n";
    cout << "Enter your  answer: ";

    string input;
    getline(cin, input);

    if (input == "12")
    {
        cout << "\nCorrect! The tree rewards you.\n";

        if (!has_healing_berries)
        {
            has_healing_berries = true;
            DisplayItemObtained("Healing Berries");
        }
        else
        {
            cout << "You already have the Healing Berries.\n";
        }

        health += 15; // correct answer rewards health
        if (health > 100)
        {
            health = 100;
        }

        cout << " You gained 15 health.\n";
        score += 10;
    }
    else
    {
        cout << "\nWrong! The runes flash and hurt you.\n";
        health -= 10; // wrong answer reduces health
        cout << " You lost 10 health.\n";
    }

    if (!CheckPlayerLife(health, lives))
        exit(0);

    DisplayStats(health, lives, score, attack, defense);
}

// scene 6 - defensive item
void Scene6(int& score, int& defense, int health, int lives, int attack, bool& has_cloak_of_thorns)
{
    cout << "===Scene 6- Hollow Tree===\n";

    cout << "You discover  a dark hollow  tree.\n";
    cout << "1) Reach  inside\n";
    cout << "2) Walk away\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        cout << "\nYou  reach inside and pull out  a mysterious cloak.\n";

        if (!has_cloak_of_thorns)
        {
            has_cloak_of_thorns = true;
            defense += 5; // cloak increases defense
            DisplayItemObtained("Cloak of Thorns");
            cout << "Your defense increases by 5.\n";
        }
        else
        {
            cout << "You already have the Cloak of Thorns.\n";
        }

        score += 10;
    }
    else
    {
        cout << "\nYou decide  not to risk it and move on.\n";
    }

    DisplayStats(health, lives, score, attack, defense);
}

// scene 7 - anagram puzzle
void Scene7(int& health, int& lives, int& score, int attack, int defense)
{
    cout << "===Scene 7- Spirit's Trial===\n";

    cout << "A forest spirit whispers  through the trees.\n";
    cout << "Unscramble  this word: T  A  N  R  E  U  \n";
    cout << "Enter your  answer: ";

    string answer;
    getline(cin, answer);

    if (answer == "nature" || answer == "Nature" || answer == "NATURE")
    {
        cout << "\nCorrect!  The spirit reveals  the final path  ahead.\n";
        score += 20;
    }
    else
    {
        cout << "\nWrong! The spirit  drains your  life force.\n";
        health -= 15; // wrong answer damages the player
        cout << "- You lost 15 health.\n";
    }

    if (!CheckPlayerLife(health, lives))
        exit(0);

    DisplayStats(health, lives, score, attack, defense);
}

// scene 8 - risk reward choice at the whispering stream
void Scene8(int& health, int& lives, int& score, int attack, int defense)
{
    cout << "===Scene 8- The Whispering Stream===\n";

    cout << "You come across  a crystal-clear stream.\n";
    cout << "The water seems  to whisper your name softly.\n";
    cout << "1) Drink from  the stream\n";
    cout << "2) Follow the  stream deeper  into the forest\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        // drinking has a random outcome
        int outcome = rand() % 2;

        if (outcome == 0)
        {
            cout << "\nThe water is  refreshing and magical!\n";
            cout << "You feel your  wounds healing.\n";

            health += 20; // magical water restores health
            if (health > 100)
            {
                health = 100;
            }

            cout << " You gained 20 health.\n";
            score += 10;
        }
        else
        {
            cout << "\nThe water is  tainted with dark magic!\n";
            cout << "Your body weakens  as poison spreads  through you.\n";
            health -= 15; // tainted water damages the player
            cout << " You lost 15 health.\n";
        }
    }
    else
    {
        cout << "\nYou follow the  stream carefully.\n";
        cout << "It leads you  safely to a  new area of the forest.\n";
        score += 5;
    }

    if (!CheckPlayerLife(health, lives))
        exit(0);

    DisplayStats(health, lives, score, attack, defense);
}

// scene 9 - item collection at the forgotten shrine
void Scene9(int& score, int& attack, int& defense, int& health, int lives, bool& has_ancient_amulet)
{
    cout << "===Scene 9- The Forgotten Shrine===\n";

    cout << "You stumble upon  a crumbling stone shrine.\n";
    cout << "Vines have overtaken  the structure but a faint  glow radiates from within.\n";
    cout << "1) Pray at  the shrine\n";
    cout << "2) Search behind  the shrine\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        cout << "\nYou kneel before  the shrine and close  your eyes.\n";
        cout << "A warm energy  surrounds you  restoring your strength.\n";

        health += 10; // praying restores some health
        if (health > 100)
        {
            health = 100;
        }

        cout << " You gained 10 health.\n";
        score += 10;
    }
    else
    {
        cout << "\nYou search behind  the shrine and discover  a glowing artifact!\n";

        if (!has_ancient_amulet)
        {
            has_ancient_amulet = true;
            attack += 3; // amulet increases attack
            defense += 3; // amulet increases defense
            DisplayItemObtained("Ancient Amulet");
            cout << "Your attack increases by 3.\n";
            cout << "Your defense increases by 3.\n";
        }
        else
        {
            cout << "You already have the Ancient Amulet.\n";
        }

        score += 15;
    }

    DisplayStats(health, lives, score, attack, defense);
}

// scene 10 - combat with the forest serpent
void Scene10(int& health, int& lives, int& score, int attack, int defense,
             bool has_hunters_dagger, bool has_cloak_of_thorns, bool has_ancient_amulet, bool& has_healing_berries)
{
    cout << "===Scene 10- The Forest Serpent===\n";

    cout << "A massive forest  serpent slithers out  from the undergrowth!\n";
    cout << "Its scales shimmer  with a sickly green glow.\n";
    cout << "1) Stand your  ground and fight\n";
    cout << "2) Try to escape  through the trees\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        if (has_hunters_dagger)
        {
            cout << "\nYou draw the  Hunter's Dagger.\n";
        }
        if (has_cloak_of_thorns)
        {
            cout << "The Cloak of Thorns  shields your body.\n";
        }
        if (has_ancient_amulet)
        {
            cout << "The Ancient Amulet  pulses with energy.\n";
        }
        if (has_healing_berries)
        {
            cout<< "\nYou Have Healing Berries.\n";
            cout<< "Do you want to eat them before the fight?\n";
            cout<< "1) Yes\n";
            cout<< "2) No\n";
            cout<< "Enter your choice (1 or 2): ";

            int berryChoice = ReadChoice12();

            if (berryChoice == 1 )
            {
                health += 10;

                if (health>100)
                    health = 100;
                cout << "\nYou eat the Healing berries.\n";
                cout << "Health restored.\n";

                has_healing_berries = false; // consume item
            }
        }

        // random combat values
        int player_roll = rand() % 6 + 1;
        int serpent_roll = rand() % 6 + 1;

        int player_power = attack + defense + player_roll;
        int serpent_power = 18 + serpent_roll; // serpent is stronger than the wolf

        cout << "\nYour combat power    : " << player_power << endl;
        cout << "Serpent combat power : " << serpent_power << endl;

        if (player_power >= serpent_power)
        {
            cout << "\nYou slay the  forest serpent!\n";
            cout << "Its body dissolves  into green mist.\n";
            score += 25;
        }
        else
        {
            cout << "\nThe serpent strikes  you with its  venomous fangs!\n";
            health -= 30; // serpent deals heavy damage
            cout << " You lost 30 health.\n";
        }
    }
    else
    {
        cout << "\nYou turn and  sprint through the trees!\n";
        cout << "The serpent's tail  catches your leg  as you flee.\n";
        health -= 10; // escaping still costs health
        cout << " You lost 10 health.\n";
    }

    if (!CheckPlayerLife(health, lives))
        exit(0);

    DisplayStats(health, lives, score, attack, defense);
}
// scene 11 - item collection at the herbalists hut
void Scene11(int& score, int& health, int lives, int attack, int defense, bool& has_fire_torch)
{
    cout << "===Scene 11- The Herbalist's Hut===\n";

    cout << "You find a  small wooden hut  overgrown with moss.\n";
    cout << "The door hangs  open and smoke  rises from inside.\n";
    cout << "1) Enter the  hut\n";
    cout << "2) Walk past  the hut\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        cout << "\nYou step inside  the hut and find  shelves of strange potions.\n";
        cout << "On the table  you spot a  burning torch that  never seems to fade.\n";

        if (!has_fire_torch)
        {
            has_fire_torch = true;
            DisplayItemObtained("Fire Torch");
            cout << "This will help  you see in  dark places.\n";
        }
        else
        {
            cout << "You already have the Fire Torch.\n";
        }

        health += 10; // resting in the hut restores some health
        if (health > 100)
        {
            health = 100;
        }

        cout << " You gained 10 health.\n";
        score += 10;
    }
    else
    {
        cout << "\nYou walk past  the hut and  continue on your journey.\n";
        score += 5;
    }

    DisplayStats(health, lives, score, attack, defense);
}

// scene 12 - the dark tunnel requires fire torch for advantage
void Scene12(int& health, int& lives, int& score, int attack, int defense, bool has_fire_torch)
{
    cout << "===Scene 12- The Dark Tunnel===\n";

    cout << "A dark tunnel  stretches before you.\n";
    cout << "You can hear  water dripping  from somewhere deep inside.\n";
    cout << "1) Enter the  tunnel\n";
    cout << "2) Go around  the hill instead\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        if (has_fire_torch)
        {
            cout << "\nYou light the  Fire Torch and  step into the tunnel.\n";
            cout << "The torch reveals  the path clearly  and you pass through safely.\n";
            score += 15;
        }
        else
        {
            cout << "\nYou stumble through  the darkness blindly.\n";
            cout << "You trip over  a rock and  cut your leg  on a sharp stone.\n";
            health -= 15; // no torch means damage in the dark
            cout << " You lost 15 health.\n";
            score += 5;
        }
    }
    else
    {
        cout << "\nYou take the  long way around  the hill.\n";
        cout << "The path is  tiring but safe.\n";
        health -= 5; // tiredness from the long path
        cout << " You lost 5 health from exhaustion.\n";
        score += 5;
    }

    if (!CheckPlayerLife(health, lives))
        exit(0);

    DisplayStats(health, lives, score, attack, defense);
}

// scene 13 - puzzle scene with a word completion challenge
void Scene13(int& health, int& lives, int& score, int attack, int defense)
{
    cout << "===Scene 13- The Vine Puzzle===\n";

    cout << "Thick magical vines  block your path.\n";
    cout << "Letters glow on  each vine forming  an incomplete word:\n";
    cout << "\"F _ R E S T\"\n";
    cout << "What is the  missing letter?\n";
    cout << "Enter your answer: ";

    string answer;
    getline(cin, answer);

    if (answer == "O" || answer == "o")
    {
        cout << "\nCorrect! The vines  part and reveal  the way forward.\n";
        score += 15;
    }
    else
    {
        cout << "\nWrong! The vines  lash out and  cut your arms.\n";
        health -= 10; // wrong answer damages the player
        cout << " You lost 10 health.\n";
    }

    if (!CheckPlayerLife(health, lives))
        exit(0);

    DisplayStats(health, lives, score, attack, defense);
}

// scene 14 - combat with the corrupted bear
void Scene14(int& health, int& lives, int& score, int attack, int defense,
             bool has_hunters_dagger, bool has_ancient_amulet)
{
    cout << "===Scene 14- The Corrupted Bear===\n";

    cout << "A massive corrupted  bear crashes through  the trees!\n";
    cout << "Dark veins pulse  across its body  and its roar  shakes the ground.\n";
    cout << "1) Fight the  bear head on\n";
    cout << "2) Try to  climb a tree  and escape\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        if (has_hunters_dagger)
        {
            cout << "\nYou ready the  Hunter's Dagger.\n";
        }
        if (has_ancient_amulet)
        {
            cout << "The Ancient Amulet  glows with power.\n";
        }

        // random combat values
        int player_roll = rand() % 6 + 1;
        int bear_roll = rand() % 6 + 1;

        int player_power = attack + defense + player_roll;
        int bear_power = 20 + bear_roll; // bear is stronger than the serpent

        cout << "\nYour combat power : " << player_power << endl;
        cout << "Bear combat power : " << bear_power << endl;

        if (player_power >= bear_power)
        {
            cout << "\nYou strike the  bear down with  a powerful blow!\n";
            cout << "The corruption fades  from its body  as it collapses.\n";
            score += 30;
        }
        else
        {
            cout << "\nThe bear swipes  you with its  massive claws!\n";
            health -= 35; // bear deals very heavy damage
            cout << " You lost 35 health.\n";
        }
    }
    else
    {
        cout << "\nYou scramble up  the nearest tree!\n";
        cout << "The bear claws  at the trunk  but cannot reach you.\n";
        cout << "However a branch  snaps and you  fall hitting the ground.\n";
        health -= 15; // falling from the tree costs health
        cout << " You lost 15 health.\n";
    }

    if (!CheckPlayerLife(health, lives))
        exit(0);

    DisplayStats(health, lives, score, attack, defense);
}

// scene 15 - math puzzle at the ancient door
void Scene15(int& health, int& lives, int& score, int attack, int defense)
{
    cout << "===Scene 15- The Ancient Door===\n";

    cout << "A stone door  blocks the path.\n";
    cout << "Numbers are carved  into the surface.\n";
    cout << "\"I am a number.  If you multiply  me by 6 and  add 4 you get 40.\"\n";
    cout << "\"What number am I?\"\n";
    cout << "Enter your answer: ";

    string input;
    getline(cin, input);

    if (input == "6")
    {
        cout << "\nCorrect! The ancient  door slowly opens.\n";
        score += 15;
    }
    else
    {
        cout << "\nWrong! A burst  of energy knocks  you backwards.\n";
        health -= 10; // wrong answer damages the player
        cout << "[-10] You lost 10 health.\n";
    }

    if (!CheckPlayerLife(health, lives))
        exit(0);

    DisplayStats(health, lives, score, attack, defense);
}

// scene 16 - the cursed clearing with a risk reward choice
void Scene16(int& health, int& lives, int& score, int attack, int defense)
{
    cout << "===Scene 16- The Cursed Clearing===\n";

    cout << "You enter a  clearing where the  air feels heavy.\n";
    cout << "A glowing pool  of liquid sits  in the centre.\n";
    cout << "1) Drink from  the glowing pool\n";
    cout << "2) Avoid the  pool and cross  the clearing quickly\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        // random outcome for drinking from the pool
        int outcome = rand() % 3;

        if (outcome == 0)
        {
            cout << "\nThe liquid is  a powerful healing  elixir!\n";
            health += 30; // powerful heal
            if (health > 100)
            {
                health = 100;
            }
            cout << "[+30] You gained 30 health.\n";
            score += 10;
        }
        else if (outcome == 1)
        {
            cout << "\nThe liquid burns  your throat with  cursed energy!\n";
            health -= 25; // cursed liquid damages the player
            cout << "[-25] You lost 25 health.\n";
        }
        else
        {
            cout << "\nThe liquid tastes  like nothing and  has no effect.\n";
        }
    }
    else
    {
        cout << "\nYou hurry across  the clearing.\n";
        cout << "Dark tendrils rise  from the ground  and scratch your legs.\n";
        health -= 5; // minor damage from the clearing
        cout << "[-5] You lost 5 health.\n";
        score += 5;
    }

    if (!CheckPlayerLife(health, lives))
        exit(0);

    DisplayStats(health, lives, score, attack, defense);
}
// scene 17 - item collection at the ancient armoury
void Scene17(int& score, int& defense, int& health, int lives, int attack, bool& has_enchanted_shield)
{
    cout << "\n===Scene 17- The Ancient Armoury===\n";

    cout << "Hidden behind a  waterfall you discover  an ancient armoury.\n";
    cout << "Rusted weapons line  the walls but  one item still glows.\n";
    cout << "1) Take the  glowing shield\n";
    cout << "2) Leave the  armoury undisturbed\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        cout << "\nYou lift the  shield from the  wall.\n";
        cout << "It hums with  ancient protective magic.\n";

        if (!has_enchanted_shield)
        {
            has_enchanted_shield = true;
            defense += 7; // enchanted shield gives a strong defense boost
            DisplayItemObtained("Enchanted Shield");
            cout << "Your defense increases by 7.\n";
        }
        else
        {
            cout << "You already have the Enchanted Shield.\n";
        }

        score += 15;
    }
    else
    {
        cout << "\nYou leave the  armoury and continue  your journey.\n";
        score += 5;
    }

    DisplayStats(health, lives, score, attack, defense);
}

// scene 18 - combat with the shadow wolves
void Scene18(int& health, int& lives, int& score, int attack, int defense,
             bool has_hunters_dagger, bool has_enchanted_shield)
{
    cout << "===Scene 18- The Shadow Wolves===\n";

    cout << "A pack of  shadow wolves surround  you!\n";
    cout << "Their dark forms  flicker like smoke  and their eyes  burn with hatred.\n";
    cout << "1) Stand and  fight the pack\n";
    cout << "2) Use fire  to scare them  away\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        if (has_hunters_dagger)
        {
            cout << "\nYou slash at  the wolves with  the Hunter's Dagger.\n";
        }
        if (has_enchanted_shield)
        {
            cout << "The Enchanted Shield  blocks their attacks.\n";
        }

        // random combat values
        int player_roll = rand() % 6 + 1;
        int wolves_roll = rand() % 6 + 1;

        int player_power = attack + defense + player_roll;
        int wolves_power = 22 + wolves_roll; // wolf pack is very strong

        cout << "\nYour combat power  : " << player_power << endl;
        cout << "Wolves combat power: " << wolves_power << endl;

        if (player_power >= wolves_power)
        {
            cout << "\nYou fight off  the shadow wolves!\n";
            cout << "They dissolve into  black mist.\n";
            score += 30;
        }
        else
        {
            cout << "\nThe wolves overwhelm  you with their  numbers!\n";
            health -= 35; // wolf pack deals heavy damage
            cout << "[-35] You lost 35 health.\n";
        }
    }
    else
    {
        // using fire has a random chance of working
        int outcome = rand() % 2;

        if (outcome == 0)
        {
            cout << "\nYou grab a  branch and wave  fire at the wolves!\n";
            cout << "They scatter into  the darkness.\n";
            score += 15;
        }
        else
        {
            cout << "\nThe fire does  not scare them!\n";
            cout << "One wolf bites  your arm before  you can escape.\n";
            health -= 20; // failed scare attempt costs health
            cout << "[-20] You lost 20 health.\n";
        }
    }

    if (!CheckPlayerLife(health, lives))
        exit(0);

    DisplayStats(health, lives, score, attack, defense);
}


int main()
{
    srand(time(0));

    cout << "=======THE LOST FOREST GAME=======\n";

    cout << "You  awaken at the forest's  edge with no  memory...\n";
    cout << "A strange green mark glows softly on your hand.\n";

    string player_name;
    cout << "\nEnter  player  name: ";
    getline(cin, player_name);

    int health = 100;
    int lives = 3;
    int score = 0;
    int attack = 10;
    int defense = 5;

    bool has_hunters_dagger = false;
    bool has_healing_berries = false;
    bool has_cloak_of_thorns = false;
    bool has_ancient_amulet = false;
    bool has_fire_torch = false;
    bool has_enchanted_shield = false;

    cout << "\nWelcome to The Lost Forest, " << player_name << "!\n";

    Scene1(health, lives, score, attack, defense);
    Scene2(health, lives, score, attack, defense);

    Scene3(score, attack, health, lives, defense, has_hunters_dagger);
    DisplayInventory(has_hunters_dagger, has_healing_berries,
                     has_cloak_of_thorns, has_ancient_amulet,
                     has_fire_torch,has_enchanted_shield    );

    Scene4(health, lives, score, attack, defense, has_hunters_dagger);
    DisplayInventory(has_hunters_dagger, has_healing_berries,
                     has_cloak_of_thorns, has_ancient_amulet,
                     has_fire_torch,has_enchanted_shield);

    Scene5(health, lives, score, attack, defense, has_healing_berries);
    DisplayInventory(has_hunters_dagger, has_healing_berries,
                     has_cloak_of_thorns, has_ancient_amulet,
                     has_fire_torch,has_enchanted_shield);

    Scene6(score, defense, health, lives, attack, has_cloak_of_thorns);
    DisplayInventory(has_hunters_dagger, has_healing_berries,
                     has_cloak_of_thorns, has_ancient_amulet,
                     has_fire_torch,has_enchanted_shield);

    Scene7(health, lives, score, attack, defense);
    DisplayInventory(has_hunters_dagger, has_healing_berries,
                     has_cloak_of_thorns, has_ancient_amulet,
                     has_fire_torch,has_enchanted_shield);

    Scene8(health, lives, score, attack, defense);
    DisplayInventory(has_hunters_dagger, has_healing_berries,
                     has_cloak_of_thorns, has_ancient_amulet,
                     has_fire_torch,has_enchanted_shield);

    Scene9(score, attack, defense, health, lives, has_ancient_amulet);
    DisplayInventory(has_hunters_dagger, has_healing_berries,
                     has_cloak_of_thorns, has_ancient_amulet,
                     has_fire_torch,has_enchanted_shield);

    Scene10(health, lives, score, attack, defense,
            has_hunters_dagger, has_cloak_of_thorns, has_ancient_amulet,has_healing_berries);
    DisplayInventory(has_hunters_dagger, has_healing_berries,
                     has_cloak_of_thorns, has_ancient_amulet,
                     has_fire_torch,has_enchanted_shield);

    Scene11(score, health, lives, attack, defense, has_fire_torch);
    DisplayInventory(has_hunters_dagger, has_healing_berries,
                     has_cloak_of_thorns, has_ancient_amulet,
                     has_fire_torch,has_enchanted_shield);

    Scene12(health, lives, score, attack, defense, has_fire_torch);
    DisplayInventory(has_hunters_dagger, has_healing_berries,
                     has_cloak_of_thorns, has_ancient_amulet,
                     has_fire_torch,has_enchanted_shield);

    Scene13(health, lives, score, attack, defense);
    DisplayInventory(has_hunters_dagger, has_healing_berries,
                     has_cloak_of_thorns, has_ancient_amulet,
                     has_fire_torch,has_enchanted_shield);

    Scene14(health, lives, score, attack, defense,
            has_hunters_dagger, has_ancient_amulet);
    DisplayInventory(has_hunters_dagger, has_healing_berries,
                     has_cloak_of_thorns, has_ancient_amulet,
                     has_fire_torch,has_enchanted_shield);

    Scene15(health, lives, score, attack, defense);
    DisplayInventory(has_hunters_dagger, has_healing_berries,
                     has_cloak_of_thorns, has_ancient_amulet,
                     has_fire_torch,has_enchanted_shield);

    Scene16(health, lives, score, attack, defense);
    DisplayInventory(has_hunters_dagger, has_healing_berries,
                     has_cloak_of_thorns, has_ancient_amulet,
                     has_fire_torch,has_enchanted_shield);

    Scene17(score, defense, health, lives, attack, has_enchanted_shield);
    DisplayInventory(has_hunters_dagger, has_healing_berries,
                     has_cloak_of_thorns, has_ancient_amulet,
                     has_fire_torch, has_enchanted_shield);

    Scene18(health, lives, score, attack, defense,
            has_hunters_dagger, has_enchanted_shield);
    DisplayInventory(has_hunters_dagger, has_healing_berries,
                     has_cloak_of_thorns, has_ancient_amulet,
                     has_fire_torch, has_enchanted_shield);


    cout << "=======END OF CURRENT GAME BUILD=======\n";
    cout << "You have survived the forest and reached the path toward the Verdant Core.\n";
    cout << "Final Score so far: " << score << endl;

    return 0;
}
