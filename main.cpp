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
void DisplayInventory(bool has_hunters_dagger, bool has_healing_berries, bool has_cloak_of_thorns)
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

    if (!has_items)
    {
        cout << "Empty\n";
    }
}

// checks if the player has lost all health
bool CheckPlayerLife(int &health, int &lives)
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
void Scene1(int &health, int &lives, int &score, int attack, int defense)
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
        cout << "You lost 10 health.\n";
    }

    if (!CheckPlayerLife(health, lives))
        exit(0);

    DisplayStats(health, lives, score, attack, defense);
}

// scene 2 - puzzle scene
void Scene2(int &health, int &lives, int &score, int attack, int defense)
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
        cout << "You lost 5 health.\n";
    }

    if (!CheckPlayerLife(health, lives))
        exit(0);

    DisplayStats(health, lives, score, attack, defense);
}

// scene 3 - item collection
void Scene3(int &score, int &attack, int health, int lives, int defense, bool &has_hunters_dagger)
{
    cout << "Scene 3- Abandoned Campsite===\n";

    cout << "You discover  an abandoned  campsite hidden between twisted trees.\n";
    cout << "1) Search the  tent\n";
    cout << "2) Ignore  it and  continue\n";
    cout << "Enter your  choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        cout << "\nYou search  the tent and find the Hunter's Dagger.\n";
        cout << "Your attack power increases.\n";

        if (!has_hunters_dagger)
        {
            has_hunters_dagger = true;
            attack += 5; // dagger increases attack
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
void Scene4(int &health, int &lives, int &score, int attack, int defense, bool has_hunters_dagger)
{
    cout << "===Scene 4-Corrupted Forest Wolf===\n";

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
        cout << "You lost 20 health.\n";
    }

    if (!CheckPlayerLife(health, lives))
        exit(0);

    DisplayStats(health, lives, score, attack, defense);
}

// scene 5 - math puzzle
void Scene5(int &health, int &lives, int &score, int attack, int defense, bool &has_healing_berries)
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
        cout << "\nCorrect! You receive Healing Berries.\n";

        if (!has_healing_berries)
        {
            has_healing_berries = true;
        }

        health += 15; // correct answer rewards health
        if (health > 100)
        {
            health = 100;
        }

        cout << "You gained 15 health.\n";
        score += 10;
    }
    else
    {
        cout << "\nWrong! The runes flash and hurt you.\n";
        health -= 10; // wrong answer reduces health
        cout << "You lost 10 health.\n";
    }

    if (!CheckPlayerLife(health, lives))
        exit(0);

    DisplayStats(health, lives, score, attack, defense);
}

// scene 6 - defensive item
void Scene6(int &score, int &defense, int health, int lives, int attack, bool &has_cloak_of_thorns)
{
    cout << "===Scene 6- Hollow Tree===\n";

    cout << "You discover  a dark hollow  tree.\n";
    cout << "1) Reach  inside\n";
    cout << "2) Walk away\n";
    cout << "Enter your choice (1 or 2): ";

    int choice = ReadChoice12();

    if (choice == 1)
    {
        cout << "\nYou  reach inside and pull out  the Cloak of Thorns.\n";
        cout << "Your defense increases.\n";

        if (!has_cloak_of_thorns)
        {
            has_cloak_of_thorns = true;
            defense += 5; // cloak increases defense
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
void Scene7(int &health, int &lives, int &score, int attack, int defense)
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
        cout << "You  lost  15  health.\n";
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

    cout << "\nWelcome to The Lost Forest, " << player_name << "!\n";

    Scene1(health, lives, score, attack, defense);
    Scene2(health, lives, score, attack, defense);
    Scene3(score, attack, health, lives, defense, has_hunters_dagger);
    DisplayInventory(has_hunters_dagger, has_healing_berries, has_cloak_of_thorns);

    Scene4(health, lives, score, attack, defense, has_hunters_dagger);
    DisplayInventory(has_hunters_dagger, has_healing_berries, has_cloak_of_thorns);

    Scene5(health, lives, score, attack, defense, has_healing_berries);
    DisplayInventory(has_hunters_dagger, has_healing_berries, has_cloak_of_thorns);

    Scene6(score, defense, health, lives, attack, has_cloak_of_thorns);
    DisplayInventory(has_hunters_dagger, has_healing_berries, has_cloak_of_thorns);

    Scene7(health, lives, score, attack, defense);
    DisplayInventory(has_hunters_dagger, has_healing_berries, has_cloak_of_thorns);


    cout << "=======END OF CURRENT GAME BUILD=======\n";
    cout << "You have reached the path toward the Verdant Core.\n";
    cout << "Final Score so far: " << score << endl;

    return 0;
}