#include <iostream>
using namespace std;

int main() {

    // START
    cout << "Welcome to \"The Lost Forest\"" << endl;

    // Enter player name
    string playerName;
    cout << "Enter player name: ";
    cin >> playerName;

    // Initialize stats
    int health = 100;
    int lives = 3;
    int score = 0;

    cout << "\nWelcome to The Lost Forest, " << playerName << "!\n";

    // Main game loop
    bool reachedEnding = false;

    while (!reachedEnding) {

        // Enter choice
        int choice;
        cout << "\nEnter your choice (1 or 2): ";
        cin >> choice;

        // Validate input
        if (choice != 1 && choice != 2) {
            cout << "Invalid input. Please enter 1 or 2.\n";
            continue;
        }

        // Apply choice outcome
        if (choice == 1) {
            cout << "You move forward carefully.\n";
            score += 10;
        } else {
            cout << "You take a dangerous path.\n";
            health -= 30;
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

            health = 100; // reset health
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

    int finalChoice;
    cin >> finalChoice;

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
