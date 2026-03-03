#include <iostream>
#include <string>
using namespace std;

int readChoice12()
{
    string input = "";
    bool valid = false;
    int choice = 0;

    while (!valid)
    {
        getline(cin,input);

        if (input == "1")
        {
            choice = 1;
            valid = true;
        }else if (input == "2"){
            choice = 2;
            valid = true;
        }else
        {
            cout <<"Invalid input. Please enter 1 or 2: ";
        }
    }
    return choice;

}

int main() {

    // START
    cout << "THE LOST FOREST - Text Adventure\n" << endl;
    cout << "You awaken at the forest's edge with no memory...\n";

    // Enter player name
    string playerName;
    cout << "Enter player name: ";
    getline(cin,playerName);

    // Initialize stats
    int health = 100;
    int lives = 3;
    int score = 0;

    cout << "\nWelcome to The Lost Forest, " << playerName << "!\n";

    // Main game loop
    bool reachedEnding = false;

    while (!reachedEnding) {

        // --- Scene text for the 1st choice[Trail vs Fog]
        cout <<" SCENE 1 - The Forest Entrance\n";
        cout << "\nYou stand at the edge of the forest. Two paths appear:\n";

        cout << "1) Follow the narrow animal trail(safer).\n";
        cout << "2) Step directly into the thick fog (dangerous).\n";
        cout << "Enter your choice (1 or 2): ";

        // Read and validate user choice
        int choice = readChoice12();

        // Appluy choice outcome and print scenario text
        if (choice == 1)
        {
            cout << "\n You follow the animal trail. The path feels steady and you make good progress\n";
            score+= 10;         // safer path = more score
        }
        else
        {
            cout<< "\nYou step into the fog. Poison spores burn your lungs and you cough violently\n";
            health -= 30;       // dangerous path = loses health
        }

        // Check if player is dead
        if (health <= 0) {
            lives--;
            cout << "You lost a life!\n";

            if (lives <= 0) {
                cout << "\nGame Over\n";
                cout << "Final Score: " << score << endl;
                return 0;
            }

            health = 100; // reset health if lives are remaining
        }


        if (score >= 20) {
            reachedEnding = true;
        }

        cout << "Health: " << health << " | Lives: " << lives
             << " | Score: " << score << endl;
    }

    // Final choice
    cout << "\nFinal Choice!\n";
    cout << "1) Save the forest\n";
    cout << "2) Walk away\n";

    cout<< "Enter your choice(1 or 2 ): ";
    int finalChoice = readChoice12();

    // Win or lose
    if (finalChoice == 1) {
        cout << "\nVictory! The forest is saved.\n";
    } else {
        cout << "\nYour strength fades. Game Over.\n";
    }

    cout << "Final Score: " << score << endl;
    cout << "End\n";



    return 0;
}

