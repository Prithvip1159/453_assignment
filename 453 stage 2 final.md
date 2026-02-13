# IY453 Stage 2

| Assessment Details | Please Complete All Details |
| ------------------ | --------------------------- |
| Group              | B                           |
| Module Title       | 453                         |
| Assessment Type    | In Class                    |
| Module Tutor Name  | Jonathan shore              |
| Student ID Number  | P500331                     |
| Date of Submission | 30-1-2026                   |
| Word Count         | 998                         |

- [x] *I confirm that this assignment is my own work. Where I have referred to academic sources, I have provided in-text citations and included the sources in
  the final reference list.*

- [x] *Where I have used AI, I have cited and referenced appropriately.

------------------------------------------------------------------------------------------------------------------------------

**Table of Contents**

1. **Purpose of the Program**
2. **Functional and Non-Functional Requirements**
3. **Input/Output Table**
4. **Gantt Chart**
5. **Diary Entries**

---

**Purpose of the Program:**

The "Lost Forest" program creates an interactive text-based adventure game which allows players to explore a fictional forest through their decision-making skills and puzzle-solving abilities and combat skills and inventory management system until they accomplish their primary objective of escaping the forest. The program shows object-oriented programming principles while entertaining users through its logical decision-making and problem-solving elements which create a unified story.

---

### *1. Functional Requirements*

- **User Interaction**: The game must prompt the player for their name and use it throughout the game.

- **Binary Choices**: At each stage, the player is presented with two options and must choose one to proceed

- **Inventory System**: The player can collect,use and view items (eg. stick,berries and key)

- Combat and Puzzles: The game includes simple combat scenarios and at least one puzzle (eg, a riddle)

- Scoring: The player earns points for solving puzzles,winning combats and collecting items. The score is displayed after major events and at the end.

- Save/Load Feature: The player can save their progress to a file and resume later.

- Error Handling: All user inputs are validated and meaningful error messages are shown for invalid inputs.

- Object oriented design: The game uses classes for player,scenes and inventory, with inheritance and polymorphism.

### 2. Non-Functional Requirements

- **Performance:** The game must respond to user inputs within 1 second, and save/load files within 2 seconds.

- **Usability:** The game must have a simple, intuitive text-based interface with clear instructions and personalized gameplay.

- **Reliability:** The game must handle unexpected inputs with error messages and ensure proper save/load functionality.

- **Scalability:** The modular design must allow easy addition of new scenes, puzzles, or features.

- **Maintainability:** The code must follow OOP principles and include clear comments for easy debugging and extension.

------------------------------------------------------------------------------------------------------------------------------

### Input Process Output Table:

| **Input**              | **Process**                                                                 | **Output**                                                                |
| ---------------------- | --------------------------------------------------------------------------- | ------------------------------------------------------------------------- |
| **Player Name**        | Player enters their name at the start, used for personalization.            | Personalized messages and dialogue throughout the game.                   |
| **Choices**            | Player selects one of two options (e.g., 1 or 2). Input is validated.       | Narrative text describing the results of the choice and updates to stats. |
| **Combat Actions**     | Player selects actions like "Attack" or "Defend." Results are calculated.   | Combat outcomes, including health updates and win/lose results.           |
| **Puzzle Answers**     | Player inputs answers to riddles or puzzles. Input is checked for accuracy. | Feedback on correctness and potential rewards for correct answers.        |
| **Save/Load Commands** | Player enters commands to save or load progress.                            | Confirmation or error messages for save/load operations.                  |
| **Narrative Text**     | Game provides scene descriptions and consequences of actions.               | Immersive storytelling and guidance for the player.                       |
| **Prompts**            | Game requests input at decision points or during combat/puzzles.            | Instructions for valid input to ensure smooth gameplay.                   |
| **Inventory/Stats**    | Game tracks and displays items, health, and score.                          | Updated inventory and stats displayed to the player.                      |
| **Feedback**           | Game provides immediate results for player actions.                         | Clear explanations of the consequences of choices or actions.             |
| **Error Messages**     | Invalid input triggers error messages and prompts for retries.              | Meaningful error messages to guide the player.                            |
| **Endgame Messages**   | Game calculates final score and displays win/lose summary.                  | Conclusive message with final score and ending narrative.                 |

### 

---

Program Code:

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
