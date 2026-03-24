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
                      bool has_cloak_of_thorns, bool has_ancient_amulet)
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
             bool has_hunters_dagger, bool has_cloak_of_thorns, bool has_ancient_amulet)
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

    cout << "\nWelcome to The Lost Forest, " << player_name << "!\n";

    Scene1(health, lives, score, attack, defense);
    Scene2(health, lives, score, attack, defense);

    Scene3(score, attack, health, lives, defense, has_hunters_dagger);
    DisplayInventory(has_hunters_dagger, has_healing_berries,
                     has_cloak_of_thorns, has_ancient_amulet);

    Scene4(health, lives, score, attack, defense, has_hunters_dagger);
    DisplayInventory(has_hunters_dagger, has_healing_berries,
                     has_cloak_of_thorns, has_ancient_amulet);

    Scene5(health, lives, score, attack, defense, has_healing_berries);
    DisplayInventory(has_hunters_dagger, has_healing_berries,
                     has_cloak_of_thorns, has_ancient_amulet);

    Scene6(score, defense, health, lives, attack, has_cloak_of_thorns);
    DisplayInventory(has_hunters_dagger, has_healing_berries,
                     has_cloak_of_thorns, has_ancient_amulet);

    Scene7(health, lives, score, attack, defense);
    DisplayInventory(has_hunters_dagger, has_healing_berries,
                     has_cloak_of_thorns, has_ancient_amulet);

    Scene8(health, lives, score, attack, defense);
    DisplayInventory(has_hunters_dagger, has_healing_berries,
                     has_cloak_of_thorns, has_ancient_amulet);

    Scene9(score, attack, defense, health, lives, has_ancient_amulet);
    DisplayInventory(has_hunters_dagger, has_healing_berries,
                     has_cloak_of_thorns, has_ancient_amulet);

    Scene10(health, lives, score, attack, defense,
            has_hunters_dagger, has_cloak_of_thorns, has_ancient_amulet);
    DisplayInventory(has_hunters_dagger, has_healing_berries,
                     has_cloak_of_thorns, has_ancient_amulet);

    cout << "=======END OF CURRENT GAME BUILD=======\n";
    cout << "You have reached the path toward the Verdant Core.\n";
    cout << "Final Score so far: " << score << endl;

    return 0;
}

