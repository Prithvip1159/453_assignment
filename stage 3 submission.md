# IY453 Stage 3

| Assessment Details | Please Complete All Details        |
| ------------------ | ---------------------------------- |
| Group              | B                                  |
| Module Title       | Software Implementation and Design |
| Assessment Type    | Stage 3                            |
| Module Tutor Name  | Jonathan Shore                     |
| Student ID Number  | P500331                            |
| Date of Submission | 15/03/2026                         |
| Word Count         | 1940                               |

- [x] *I confirm that this assignment is my own work. Where I have referred to academic sources, I have provided in-text citations and included the sources in
  the final reference list.*

- [x] *Where I have used AI, I have cited and referenced appropriately.

------------------------------------------------------------------------------------------------------------------------------

### Program Code:

------------------------------------------------------------------------------------------------------------------------------

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

------------------------------------------------------------------------------------------------------------------------------

### # Test Table – The Lost Forest Program

| Test No. | Item to test                  | Test Description (with example data)                | Expected Result                                                     | Actual Result                             | Comments / Actions     |
| -------- | ----------------------------- | --------------------------------------------------- | ------------------------------------------------------------------- | ----------------------------------------- | ---------------------- |
| 1        | Player name input             | Enter player name **“Prithvi”** when program starts | Program accepts name and prints *Welcome to The Lost Forest, Alex!* | Program displayed correct welcome message | Working correctly      |
| 2        | Scene 1 safe path             | Enter **1** in Scene 1                              | Player follows animal trail and **score increases by 10**           | Score increased to 10                     | Working correctly      |
| 3        | Scene 1 dangerous path        | Enter **2** in Scene 1                              | Player loses **10 health** due to fog                               | Health reduced from 100 to 90             | Working correctly      |
| 4        | Input validation              | Enter **5 or text** instead of 1 or 2               | Program asks user again for valid input                             | Program asked for correct input           | Input validation works |
| 5        | Scene 2 riddle correct answer | Enter **“footsteps”**                               | Path opens and **score increases by 10**                            | Score increased correctly                 | Working correctly      |
| 6        | Scene 2 wrong answer          | Enter **“shadow”**                                  | Player loses **5 health**                                           | Health reduced correctly                  | Working correctly      |
| 7        | Scene 3 item collection       | Choose **1 (search tent)**                          | Player obtains **Hunter's Dagger** and attack increases by 5        | Attack increased from 10 to 15            | Working correctly      |
| 8        | Scene 4 combat win            | Player power higher than wolf                       | Player defeats wolf and score increases by 15                       | Wolf defeated successfully                | Combat system working  |
| 9        | Scene 4 combat loss           | Wolf power higher than player                       | Player loses **20 health**                                          | Health reduced correctly                  | Combat damage works    |
| 10       | Scene 5 math puzzle correct   | Enter **12**                                        | Player gains **15 health** and score increases                      | Health increased correctly                | Working correctly      |
| 11       | Scene 5 wrong answer          | Enter **10**                                        | Player loses **10 health**                                          | Health decreased correctly                | Working correctly      |
| 12       | Scene 6 cloak item            | Choose **1 reach inside**                           | Player gets **Cloak of Thorns** and defense increases by 5          | Defense increased correctly               | Working correctly      |
| 13       | Scene 7 puzzle correct        | Enter **nature**                                    | Player passes trial and score increases                             | Score increased correctly                 | Working correctly      |



------------------------------------------------------------------------------------------------------------------------------

### Evaluation of Test table with screenshots:



![](C:\Users\Prithvi\AppData\Roaming\marktext\images\2026-03-15-23-36-19-image.png)![](C:\Users\Prithvi\AppData\Roaming\marktext\images\2026-03-15-23-37-02-image.png)![](C:\Users\Prithvi\AppData\Roaming\marktext\images\2026-03-15-23-38-13-image.png)![](C:\Users\Prithvi\AppData\Roaming\marktext\images\2026-03-15-23-38-49-image.png)![](C:\Users\Prithvi\AppData\Roaming\marktext\images\2026-03-15-23-39-30-image.png)![](C:\Users\Prithvi\AppData\Roaming\marktext\images\2026-03-15-23-40-57-image.png)![](C:\Users\Prithvi\AppData\Roaming\marktext\images\2026-03-15-23-41-30-image.png)![](C:\Users\Prithvi\AppData\Roaming\marktext\images\2026-03-15-23-42-07-image.png)![](C:\Users\Prithvi\AppData\Roaming\marktext\images\2026-03-15-23-42-54-image.png)![](C:\Users\Prithvi\AppData\Roaming\marktext\images\2026-03-15-23-43-35-image.png)![](C:\Users\Prithvi\AppData\Roaming\marktext\images\2026-03-15-23-44-31-image.png)![](C:\Users\Prithvi\AppData\Roaming\marktext\images\2026-03-15-23-45-07-image.png)

------------------------------------------------------------------------------------------------------------------------------ 
