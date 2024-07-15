#include <iostream>
#include <fstream>
#include <cstdlib>   // For rand() and srand()
#include <ctime>     // For time()
#include <algorithm> // For shuffle
#include <random>    // For std::shuffle, std::mt19937, and std::random_device
#include "Player.h"
#include "Enemy.h"
#include "Goblin.h"
#include "Zombie.h"
#include "Dragon.h"
#include <sstream>

int tokens = 0;

void clearScreen() {
#ifdef _WIN32
    system("cls"); // clear console For Windows
#else
    if (system("clear") != 0) { //clear console For Unix-like systems
        std::cerr << "Error: Unable to clear the screen." << std::endl;
    }
#endif
}

bool solvePuzzle(const std::vector<std::string>& parts) {
    // Shuffle the parts
     std::vector<std::string> shuffledParts = parts;
     std::shuffle(shuffledParts.begin(), shuffledParts.end(), std::mt19937(std::random_device()()));
    // Present the shuffled parts to the player
    clearScreen();
     std::cout << "You encounter a puzzle game! (worth 10 tokens)\n";
     std::cout << std::endl;
     std::cout << "  ⠀⠀⠀⠀⠀⠀⠀⣤⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
     std::cout << "  ⠀⢀⣄⠀⣠⠶⠲⠞⠁⠀⠙⠛⠳⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
     std::cout << "  ⠀⡟⠙⠛⠁⣀⣀⢀⡤⢤⠀⠀⠀⠙⢷⣄⠀⠀⠀⠀⠀⠀⠀" << std::endl;
     std::cout << "  ⢠⡷⢄⣠⠊⠀⠀⠁⠀⡀⠑⠒⠈⢳⠀⢻⡆⠀⠀⠀⠀⠀⠀" << std::endl;
     std::cout << "  ⠀⣷⠃⢠⡀⠀⠀⠀⠀⠈⠀⠀⠀⢎⠀⢸⡇⠀⠀⠀⠀⠀⠀" << std::endl;
     std::cout << "  ⢠⡇⠀⠘⢁⡄⠀⠀⠉⠉⠀⠀⠀⣳⢧⣾⠃⠀⠀⠀⠀⠀⠀" << std::endl;
     std::cout << "  ⢸⡇⠀⠀⠘⠆⠀⠀⢀⠀⠀⠀⠀⠁⢿⡏⠀⠀⠀⠀⠀⠀⠀" << std::endl;
     std::cout << "  ⠈⣇⠸⢖⡀⠀⠐⣂⠹⡇⠀⠀⠀⣀⣼⠇⠀⠀⠀⠀⠀⠀⠀" << std::endl;
     std::cout << "  ⠀⠹⣦⠀⠈⠭⠉⠀⠀⠀⠀⣠⡾⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
     std::cout << "⠀  ⠀⠈⠳⢦⣄⣀⣀⣠⡴⠞⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
     std::cout << "⠀  ⠀⠀⠀⠀⠀⠈⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
     std::cout << std::endl;
     std::cout << "   -GOOD LUCK!- " << std::endl;
     std::cout << std::endl;
     std::cout << "Arrange the parts to form a sentence:\n";
    for (int i = 0; i < shuffledParts.size(); ++i) {
        std::cout << i + 1 << ". " << shuffledParts[i] << std::endl;
    }

    // Get the player's input for the order of parts
    std::vector<int> playerOrder; // Declare a vector to store the player's order of parts
    std::cout << std::endl;
    std::cout << "Enter the order of parts (e.g., 1 2 3): "; // Prompt the player to enter the order of parts
    std::string input;
    std::getline(std::cin, input); // Clear the newline character from previous input
    while (true) {
        std::getline(std::cin, input);
        std::istringstream iss(input);// Create an input stream from the input string
        int part;
        bool validInput = true;

        while (iss >> part) { // Extract each part number from the input
            if (part < 1 || part > shuffledParts.size()) { //Check if the part number is within the valid range
                validInput = false;
                break;
            }
            playerOrder.push_back(part);
        }

        if (validInput && playerOrder.size() == shuffledParts.size()) { // Check if the input is valid and all parts have been entered
            break; // Exit the loop since the player has entered all parts correctly
        } else {
            std::cout << "Invalid input. Make sure to enter the correct order of parts separated by spaces.\n"; // Prompt the player to try again
            std::cout << std::endl;
            std::cout << "Enter the order of parts (e.g., 1 2 3): ";
            playerOrder.clear(); // Clear the previous input
        }
    }

    // Check if the player's order matches the correct order
    bool solved = true;
    for (int i = 0; i < playerOrder.size(); ++i) {
        if (shuffledParts[playerOrder[i] - 1] != parts[i]) { // Compare the player's order with the correct order
            solved = false;
            break;
        }
    }
    return solved; // Return true if the player's order matches the correct order, false otherwise
}

// Function for combat between the player and an enemy

void combat(Player& player, Enemy& enemy) {
    while (player.isAlive() && enemy.isAlive()) {
        // Player chooses action
        std::cout << std::endl;
        std::cout << "Options: A/a: Attack, F/f: Flee\n";
        char choice;
        std::cout << "Choose your action: ";
        std::cin >> choice;
        std::cout << std::endl;
        int playerDamage, enemyDamage; // Declare variables outside the switch block

        switch (choice) {
            case 'A':
            case 'a':
                // Player attacks the enemy
                playerDamage = player.attack();
                enemy.takeDamage(playerDamage);
                // Check if the enemy is defeated
                if (!enemy.isAlive()) {
                    clearScreen();
                    std::cout << " You defeated the enemy!\n";
                    std::cout << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⢀⡠⢀⢔⠝⢮⡽⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⢈⠔⡡⢂⢀⠜⠙⠺⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠈⡍⢣⣠⢊⡼⠁⢠⠛⠠⡜⢰⢋⠀⠀⠀⣀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⣼⠁⣼⡁⢸⠁⢰⠋⠀⢰⠀⡾⠋⠀⢀⡈⠤⡐⡐⠦⠄" << std::endl;
                    std::cout << "⠀⢰⢀⠃⠀⠈⠂⠩⠄⠰⠋⢡⠓⡒⢉⣩⠴⠒⠉⡃⢄⠃" << std::endl;
                    std::cout << "⠀⢸⠸⠀⠀⠀⠀⠀⠀⠈⢆⣾⠀⢸⣁⣀⡤⠒⢘⡀⠊⠀" << std::endl;
                    std::cout << "⢀⣸⠀⠀⠀⠀⠀⠀⠀⠀⡸⢉⠗⠀⡅⣀⣧⠖⢉⠇⠀⠀" << std::endl;
                    std::cout << "⠀⢀⡇⠀⠀⠀⠀⠀⡠⡳⠃⠈⠉⠁⠏⠁⣠⠔⠁⠀⠀⠀" << std::endl;
                    std::cout << "⠐⠁⠀⠀⠀⠑⢦⢈⠜⣁⣠⣶⣒⡢⠞⡩⠔⡂⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⢠⠞⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠐⠋⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << std::endl;
                    if (dynamic_cast<Goblin*>(&enemy)) {
                        tokens += 1;
                        std::cout << " -You have gained 1 token!-\n";
                        std::cout << std::endl;
                        
                        std::cout << "** Your current health: " << player.getHealth() << " **" << std::endl;
        std::cout << "** Your current tokens: " << tokens << " **" << std::endl;
                    } else if (dynamic_cast<Zombie*>(&enemy)){
                      tokens += 2;
                      std::cout << " -You have gained 2 tokens!-\n";
                      std::cout << std::endl;
                      std::cout << "** Your current health: " << player.getHealth() << " **" << std::endl;
        std::cout << "** Your current tokens: " << tokens << " **" << std::endl;
                    }
                    else if (dynamic_cast<Dragon*>(&enemy)){
                      tokens += 5;
                      std::cout << " -You have gained 5 tokens!-\n";
                      std::cout << std::endl;
                      std::cout << "** Your current health: " << player.getHealth() << " **" << std::endl;
        std::cout << "** Your current tokens: " << tokens << " **" << std::endl;
                    }

                    return;
                }
                // Enemy attacks the player
                enemyDamage = enemy.getAttackPower();
                std::cout << enemy.getName() << " attacks you for " << enemyDamage << " damage!\n";
                player.takeDamage(enemyDamage);
                break;
            case 'F':
            case 'f':
                // Player flees from the enemy
                clearScreen();
                std::cout << "You chose to flee from the enemy!\n";
                std::cout << std::endl;
                std::cout << std::endl;
                std::cout << "            _( }" << std::endl;
                std::cout << "   -=  _  <<  \\" << std::endl;
                std::cout << "      `.\\_/`/\\\\" << std::endl;
                std::cout << " -=     '--'\\\\ `" << std::endl;
                std::cout << "      -=    //" << std::endl;
                std::cout << "  -=        \\)" << std::endl;
                std::cout << std::endl;
                std::cout << std::endl;
                // Implement flee logic (for example, break out of the loop)
                return;
            default:
                clearScreen();
                std::cout << "Invalid choice!\n";
                break;
        }
        std::cout << std::endl;
        // Display remaining health points
        std::cout << "Your remaining health: " << player.getHealth() << std::endl;
        std::cout << "Enemy's remaining health: " << enemy.getHealth() << std::endl;
    }
}

void saveGame(const std::string& filename, const Player& player, int& tokens) { //pass by reference saving game
    std::ofstream file(filename);
    if (file.is_open()) {
        file << player.getHealth() << std::endl;
        file << tokens << std::endl;
        clearScreen();
        std::cout << "Game saved successfully." << std::endl;
        std::cout << std::endl;
        std::cout << "** Your current health: " << player.getHealth() << " **" << std::endl;
        std::cout << "** Your current tokens: " << tokens << " **" << std::endl;
    } else {
        //clearScreen();
        std::cerr << "Error: Unable to save game." << std::endl;
    }
}

void loadGame(const std::string& filename, Player& player , int& tokens) { //pass by reference loading game
    std::ifstream file(filename);
    if (file.is_open()) {
        int health;
        file >> health;
        player.setHealth(health);
        file >> tokens;
        clearScreen();
        std::cout << "-Game loaded successfully-" << std::endl;
        std::cout << std::endl;
        std::cout << "** Your current health: " << player.getHealth() << " **" << std::endl;
        std::cout << "** Your current tokens: " << tokens << " **" << std::endl;
    } else {
        clearScreen();
        std::cerr << "Error: Unable to load game." << std::endl;
    }
}

int main() {
    // Seed the random number generator
    srand(static_cast<unsigned>(time(nullptr)));

    Player player;
  
    

    // Define enemies
    Goblin goblin;
    Zombie zombie;
    Dragon dragon;

    std::cout << "    *** ╦═╗┬ ┬┬┌┐┌┌─┐  ┌─┐┌─┐  ┬─┐┌─┐┌┬┐┌─┐┌┬┐┌─┐┌┬┐┬┌─┐┌┐┌ ***" << std::endl;
    std::cout << "    *** ╠╦╝│ │││││└─┐  │ │├┤   ├┬┘├┤  ││├┤ │││├─┘ │ ││ ││││ ***" << std::endl;
    std::cout << "    *** ╩╚═└─┘┴┘└┘└─┘  └─┘└    ┴└─└─┘─┴┘└─┘┴ ┴┴   ┴ ┴└─┘┘└┘ ***" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "   -MAIN STORY-\n";
    std::cout << std::endl;
    std::cout << "In a world of powerful wizards, there lived a young apprentice." << std::endl;
    std::cout << "Despite his dedication to the arcane arts, he still struggled to fully control his magical abilities." << std::endl;
    std::cout << "His fellow wizards, born with an innate mastery of their powers, would often mock and bully him for his shortcomings." << std::endl;
    std::cout << "Tired of being the outcast, he resolved to prove his worth." << std::endl;
    std::cout << "He set out on a perilous journey to an abandoned ruin deep in the heart of the enchanted forest." << std::endl;
    std::cout << "It was said that within these crumbling walls, an ancient artifact lay waiting – a collection of 30 enchanted tokens that would grant the wielder with unparalleled magical powers." << std::endl;
   std::cout << std::endl;
   std::cout << "  -DAMAGE DIFFERENT ENEMIES INFLICT ON YOU-" << std::endl;
   std::cout << "   ** Dragons health 100 : damage 20 **" << std::endl;
   std::cout << "   ** Zombies health 75 : damage 15 **" << std::endl;
   std::cout << "   ** Goblins health 50 : damage 10 **" << std::endl;
   std::cout << std::endl;

  std::cout << "               /\\   " << std::endl;
  std::cout << "            /\\|  |/\\" << std::endl;
  std::cout << "         [] ||_/\\_|| []" << std::endl;
  std::cout << "         ||_||____||_||" << std::endl;
  std::cout << "         ||____[]____||" << std::endl;
  std::cout << "        {::     \\__    }" << std::endl;
  std::cout << "    ___  \\v:    .'\"\\ _V ___" << std::endl;
  std::cout << "  (      \\_      __/  --  )_" << std::endl;
  std::cout << "  (__---    |:::\\ :/  ---     )" << std::endl;
  std::cout << "     (       \\:::\\/  ----- ___)" << std::endl;
  std::cout << "      (______  \\/     _____)" << std::endl;

  
    // Player encounters rooms until the player is defeated or tokens collected
      while (player.isAlive() && tokens < 30) {
      // Ask if the player wants to continue exploring or save/load the game
      std::cout << std::endl;
      std::cout << "OPTIONS:\n";
      std::cout << std::endl;
      std::cout << "    Y/y: Continue exploring the vast, mysterious RUIN?\n";
      std::cout << "    S/s: Save your journey and return another time\n";
      std::cout << "    L/l: Load a previously saved adventure\n";
      std::cout << "    Any other key: EXIT your exploration for now\n";
      std::cout << std::endl;
      std::cout << "Enter your choice: ";
      
      char continueChoice;
      std::cin >> continueChoice;
      if (continueChoice != 'Y' && continueChoice != 'y') {
          if (continueChoice == 'S' || continueChoice == 's') {
              saveGame("savegame.txt", player, tokens);
              continue;
          } else if (continueChoice == 'L' || continueChoice == 'l') {
              loadGame("savegame.txt", player, tokens);
              continue;
          } else {
              break;
          }
      }
        int leftRoomEncounter = rand() % 3;  // 0: Health loot, 1: Enemy encounter, 2: Puzzle game
        int rightRoomEncounter = rand() % 3; // 0: Health loot, 1: Enemy encounter, 2: Puzzle game
        clearScreen();
        std::cout << "You encounter a left room and a right room. Choose your path (L/l: Left, R/r: Right): ";
        std::cout << std::endl;
        std::cout << " _________________________________________________________" << std::endl;
        std::cout << " /|     -_-                                             _-  |\\     " << std::endl;
        std::cout << "/ |_-_- _                                         -_- _-   -| \\   " << std::endl;
        std::cout << "  |                            _-  _--                      | " << std::endl;
        std::cout << "  |                            ,                            |" << std::endl;
        std::cout << "  |      .-'````````'.        '(`        .-'```````'-.      |" << std::endl;
        std::cout << "  |    .` |           `.      `)'      .` |           `.    |          " << std::endl;
        std::cout << "  |   /   |   ()        \\      U      /   |    ()       \\   |" << std::endl;
        std::cout << "  |  |    |    ;         | o   T   o |    |    ;         |  |" << std::endl;
        std::cout << "  |  |    |     ;        |  .  |  .  |    |    ;         |  |" << std::endl;
        std::cout << "  |  |    |     ;        |   . | .   |    |    ;         |  |" << std::endl;
        std::cout << "  |  |    |     ;        |    .|.    |    |    ;         |  |" << std::endl;
        std::cout << "  |  |    |____;_________|     |     |    |____;_________|  |  " << std::endl;
        std::cout << "  |  |   /  __ ;   -     |     !     |   /     `'() _ -  |  |" << std::endl;
        std::cout << "  |  |  / __  ()        -|        -  |  /  __--      -   |  |" << std::endl;
        std::cout << "  |  | /        __-- _   |   _- _ -  | /        __--_    |  |" << std::endl;
        std::cout << "  |__|/__________________|___________|/__________________|__|" << std::endl;
        std::cout << " /                                             _ -        lc \\" << std::endl;
        std::cout << "/   -_- _ -             _- _---                       -_-  -_ \\" << std::endl;
        std::cout << std::endl;
        char choice;
        std::cin >> choice;

        if (choice == 'L' || choice == 'l') { // Encounter in the left room
            if (leftRoomEncounter == 0) {
                // Health loot
                int healthGain = rand() % 21 + 10; // Gain between 10 to 30 health points
                player.heal(healthGain);
                clearScreen();
                std::cout << std::endl;
                std::cout << " -You entered a room with health loot-" << std::endl;
                std::cout << std::endl;
                std::cout << "You found health loot and gained " << healthGain << " health points!\n";
                std::cout << std::endl;
                std::cout << "⠀⠀⠀⠀    ⠀⢀⣤." << std::endl;
                std::cout << "⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⣿⡆ ⣠⣶⣿⣶⡀" << std::endl;
                std::cout << "⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿" << std::endl;
                std::cout << "⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏" << std::endl;
                std::cout << "⠀⠀⠀⠀⠀⠀⠀⠈⣿⣿⣿⣿⣿⣿⣿⠋" << std::endl;
                std::cout << "⠀⠀⠀⠀⣾⣿⣿⣧⠀⠻⣿⣿⠿⠉" << std::endl;
                std::cout << "⣰⣿⣿⣿⣿⣿⣿⣿" << std::endl;
                std::cout << "⠸⣿⣿⣿⣿⣿⣿⠏" << std::endl;
                std::cout << "⠀⠈⠛⠿⣿⣿⡟" << std::endl;
                std::cout << std::endl;
              std::cout << "** Your current health: " << player.getHealth() << " **" << std::endl;
            } else if (leftRoomEncounter == 1) {
                // Enemy encounter
                clearScreen();
                std::cout << "You encounter an enemy! Goblins(1 token)  Zombies(2 tokens) Dragons(5 tokens)\n";
                Enemy* enemy;
                int enemyType = rand() % 3; // 0: Goblin, 1: Zombie, 2: Dragon
                switch (enemyType) {
                    case 0:
                        enemy = new Goblin();
                        break;
                    case 1:
                        enemy = new Zombie();
                        break;
                    case 2:
                        enemy = new Dragon();
                        break;
                }
                combat(player, *enemy); // Start combat
                delete enemy; // Free memory
            } else {
                // Puzzle game
                std::vector<std::string> parts = {"In", "the", "deepest", "darkness,", "even", "a", "small", "light", "brings", "hope"};
                if (solvePuzzle(parts)) {
                    clearScreen();
                    std::cout << std::endl;
                    std::cout << "You solved the puzzle!\n";
                    tokens += 10;
                    std::cout << "You won 10 tokens!\n";
                    std::cout << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣠⠔⠉⠒⠤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⠺⠤⠔⠁⠀⠀⢀⣀⠀⠀⠀⠑⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡀⢀⡰⠋⠉⠈⠉⠉⠳⠤⠔⢦⡈⢳⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢣⡜⠑⠂⠀⠀⠀⠀⠒⠄⠀⠀⣴⠃⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡸⠀⢰⠄⢀⠆⠀⠰⢦⠀⠀⠀⢽⣳⣰⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠔⠋⢹⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠠⣏⠀⠀⠀⠀⠀⠀⠀⠕⢻⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⢸⠀⠀⠸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣇⢠⡄⣀⣀⣀⠠⠴⣄⠀⠀⠀⠀⢈⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⢀⣀⣠⣧⣀⠘⠢⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⡌⠉⠒⣦⠖⠒⠉⠉⠀⠀⣠⠖⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⢮⠀⢀⡀⠀⠙⡆⠘⣦⣤⣀⣀⣀⠀⠀⢀⣀⣀⣙⣦⡀⠀⠀⠀⠀⠀⠠⡾⠓⢦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⢸⠉⠉⠉⠉⠚⡅⢀⡟⡄⠀⠈⠉⠉⠉⠉⠀⠀⠀⢸⠉⠳⢶⣤⣀⡤⠖⠁⢀⡞⠀⠈⠓⢤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠈⡗⠉⠓⠒⠲⡇⢸⢁⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢳⠀⠀⠀⠀⣀⣠⠴⠋⠀⠀⠀⠀⠀⠈⠲⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠙⠶⢖⣒⣺⣵⣣⠊⠀⣀⣀⣀⡠⠤⠔⡿⠀⠀⠀⡞⠀⠀⠀⡞⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠣⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠉⠀⠀⠀⠀⠀⣇⠀⠀⠀⡇⠀⠀⠀⡇⠀⠀⠀⠀⢦⣄⣀⠀⠀⠀⠀⠀⠀⢙⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠀⠀⠀⠃⠀⠀⢸⠇⠀⠀⠀⠀⣿⣿⣿⠛⢲⡄⠀⠀⢀⣼⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⢰⠀⠀⠀⢸⠀⠀⠀⠀⢰⣿⣿⡟⢀⡞⠀⢀⣠⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠦⢄⣈⠀⠀⠀⢸⠀⠀⠀⠀⣼⣿⣿⣇⡎⣠⣴⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⡇⠀⠈⠀⠀⠀⠈⠓⠒⠒⠚⠋⠉⢸⡿⢿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣷⢄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣸⡇⠀⠉⡹⠻⡅⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⠀⠈⠉⠛⠒⠒⠒⠒⠚⣿⣿⣿⣿⣷⣀⣀⣙⣢⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠄⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠛⠛⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << std::endl;
                    std::cout << " ** You now have " << tokens << " tokens!! ** \n";
                    // Implement reward for solving the puzzle
                  
                } else {
                    clearScreen();
                    std::cout << "You failed to solve the puzzle.\n";
                    // Implement consequence for failing to solve the puzzle
                }
            }
        } else if (choice == 'R' || choice == 'r') {
            // Encounter in the right room
            if (rightRoomEncounter == 0) {
                // Health loot
                int healthGain = rand() % 21 + 10; // Gain between 10 to 30 health points
                player.heal(healthGain);
                 clearScreen();
                std::cout << std::endl;
                std::cout << " -You entered a room with health loot-" << std::endl;
                std::cout << std::endl;
                std::cout << "You found health loot and gained " << healthGain << " health points!\n";
                std::cout << std::endl;
                std::cout << "⠀⠀⠀⠀    ⠀⢀⣤." << std::endl;
                std::cout << "⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⣿⡆ ⣠⣶⣿⣶⡀" << std::endl;
                std::cout << "⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿" << std::endl;
                std::cout << "⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏" << std::endl;
                std::cout << "⠀⠀⠀⠀⠀⠀⠀⠈⣿⣿⣿⣿⣿⣿⣿⠋" << std::endl;
                std::cout << "⠀⠀⠀⠀⣾⣿⣿⣧⠀⠻⣿⣿⠿⠉" << std::endl;
                std::cout << "⣰⣿⣿⣿⣿⣿⣿⣿" << std::endl;
                std::cout << "⠸⣿⣿⣿⣿⣿⣿⠏" << std::endl;
                std::cout << "⠀⠈⠛⠿⣿⣿⡟" << std::endl;
                std::cout << std::endl;
              std::cout << "** Your current health: " << player.getHealth() << " **" << std::endl;
            } else if (rightRoomEncounter == 1) {
                // Enemy encounter
                clearScreen();
                std::cout << "You encounter an enemy! Goblins(1 token)  Zombies(2 tokens) Dragons(5 tokens)\n";
                std::cout << std::endl;
                Enemy* enemy;
                int enemyType = rand() % 3; // 0: Goblin, 1: Zombie, 2: Dragon
                switch (enemyType) {
                    case 0:
                        enemy = new Goblin();
                        break;
                    case 1:
                        enemy = new Zombie();
                        break;
                    case 2:
                        enemy = new Dragon();
                        break;
                }
                combat(player, *enemy); // Start combat
                delete enemy; // Free memory
            } else {
                // Puzzle game
                
                std::cout << "You encounter a puzzle game! (worth 10 tokens)\n";
                std::vector<std::string> parts = {"Each", "defeat", "teaches;", "every", "victory", "makes", "you", "stronger"};
                if (solvePuzzle(parts)) {
                    clearScreen();
                    std::cout << "You solved the puzzle!\n";
                    tokens += 10;
                    std::cout << "You won 10 tokens!\n";
                    std::cout << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣠⠔⠉⠒⠤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⠺⠤⠔⠁⠀⠀⢀⣀⠀⠀⠀⠑⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡀⢀⡰⠋⠉⠈⠉⠉⠳⠤⠔⢦⡈⢳⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢣⡜⠑⠂⠀⠀⠀⠀⠒⠄⠀⠀⣴⠃⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡸⠀⢰⠄⢀⠆⠀⠰⢦⠀⠀⠀⢽⣳⣰⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠔⠋⢹⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠠⣏⠀⠀⠀⠀⠀⠀⠀⠕⢻⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⢸⠀⠀⠸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣇⢠⡄⣀⣀⣀⠠⠴⣄⠀⠀⠀⠀⢈⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⢀⣀⣠⣧⣀⠘⠢⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⡌⠉⠒⣦⠖⠒⠉⠉⠀⠀⣠⠖⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⢮⠀⢀⡀⠀⠙⡆⠘⣦⣤⣀⣀⣀⠀⠀⢀⣀⣀⣙⣦⡀⠀⠀⠀⠀⠀⠠⡾⠓⢦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⢸⠉⠉⠉⠉⠚⡅⢀⡟⡄⠀⠈⠉⠉⠉⠉⠀⠀⠀⢸⠉⠳⢶⣤⣀⡤⠖⠁⢀⡞⠀⠈⠓⢤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠈⡗⠉⠓⠒⠲⡇⢸⢁⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢳⠀⠀⠀⠀⣀⣠⠴⠋⠀⠀⠀⠀⠀⠈⠲⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠙⠶⢖⣒⣺⣵⣣⠊⠀⣀⣀⣀⡠⠤⠔⡿⠀⠀⠀⡞⠀⠀⠀⡞⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠣⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠉⠀⠀⠀⠀⠀⣇⠀⠀⠀⡇⠀⠀⠀⡇⠀⠀⠀⠀⢦⣄⣀⠀⠀⠀⠀⠀⠀⢙⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠀⠀⠀⠃⠀⠀⢸⠇⠀⠀⠀⠀⣿⣿⣿⠛⢲⡄⠀⠀⢀⣼⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⢰⠀⠀⠀⢸⠀⠀⠀⠀⢰⣿⣿⡟⢀⡞⠀⢀⣠⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠦⢄⣈⠀⠀⠀⢸⠀⠀⠀⠀⣼⣿⣿⣇⡎⣠⣴⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⡇⠀⠈⠀⠀⠀⠈⠓⠒⠒⠚⠋⠉⢸⡿⢿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣷⢄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣸⡇⠀⠉⡹⠻⡅⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⠀⠈⠉⠛⠒⠒⠒⠒⠚⣿⣿⣿⣿⣷⣀⣀⣙⣢⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠄⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠛⠛⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
                    std::cout << std::endl;
                    std::cout << " ** You now have " << tokens << " tokens!! ** \n";
                    // Implement reward for solving the puzzle
                } else {
                    clearScreen();
                    std::cout << "You failed to solve the puzzle.\n";
                    // Implement consequence for failing to solve the puzzle
                }
            }
        }
      if (tokens >= 30) {
          clearScreen();
          std::cout << "   ***Congratulations! You have collected 30 enchanted tokens and mastered your magical abilities!***\n";
          std::cout << std::endl;
          std::cout << "                             /\\" << std::endl;
          std::cout << "                            /  \\" << std::endl;
          std::cout << "                           |    |" << std::endl;
          std::cout << "                         --:'''':--" << std::endl;
          std::cout << "                           :'_' :" << std::endl;
          std::cout << "                           _:\"\":\\___" << std::endl;
          std::cout << "            ' '      ____.' :::     '._" << std::endl;
          std::cout << "           . *=====<<=)           \\    :" << std::endl;
          std::cout << "            .  '      '-'-'\\_      /'._.'" << std::endl;
          std::cout << "                             \\====:_ \"\"" << std::endl;
          std::cout << "                            .'     \\\\" << std::endl;
          std::cout << "                           :       :" << std::endl;
          std::cout << "                          /   :    \\" << std::endl;
          std::cout << "                         :   .      '." << std::endl;
          std::cout << "         ,. _        snd :  : :      :" << std::endl;
          std::cout << "      '-'    ).          :__:-:__.;--'" << std::endl;
          std::cout << "    (        '  )        '-'   '-'" << std::endl;
          std::cout << " ( -   .00.   - _" << std::endl;
          std::cout << "(    .'  _ )     )" << std::endl;
          std::cout << "'-  ()_.,   -" << std::endl;
            
          break;
      }

        // Check if the player is still alive
        if (!player.isAlive()) {
            clearScreen();
            std::cout << "Game over! :(\n";
            std::cout << std::endl;
            std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⡴⠖⠒⠛⠛⠒⠶⢤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
            std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡼⠁⠀⠀⠀⣠⠖⠲⣄⣀⣤⡬⣷⣄⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
            std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡾⠁⠀⠀⣠⡤⠇⠀⠀⠉⢴⣒⣿⠀⠀⠀⢱⠤⢤⠤⢤⣤⢤⣀⡀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
            std::cout << "⢠⣦⣤⣴⣶⠀⣤⣶⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⣸⠉⠀⠀⠀⠀⠀⠘⠋⠁⠀⠀⠀⠛⣧⣸⠟⠉⠀⠀⠀⠉⠳⢦⡀⠀⠀⠀⠀" << std::endl;
            std::cout << "⠈⠉⠉⠉⠉⠀⠉⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⢸⡁⠀⢸⠁⠀⠀⠀⠴⢛⡁⠀⠀⠀⠀⠀⠀⠀⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠻⣄⠀⠀⠀" << std::endl;
            std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢨⠇⠀⣸⢀⡀⠀⠀⠀⠙⠃⠀⢀⣦⡖⠀⠀⣸⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢧⠀⠀" << std::endl;
            std::cout << "⠀⠀⠀⠀⣠⢦⡄⠀⠀⠀⠀⠀⠀⠀⠀⠘⠛⠥⠤⠖⠧⣘⠁⣦⠘⢧⡀⢀⠀⡼⡿⠀⠀⣰⠏⠀⠀⠀⠀⠀⠀⠀⣦⠀⠀⠀⠀⠀⢧⠀" << std::endl;
            std::cout << "⠀⠀⠀⠀⣿⠀⢳⣄⣀⠀⠀⣴⠳⡶⠦⣤⣀⠀⠀⠀⠀⠈⠓⢦⣀⠀⠙⠩⣾⠼⠁⢀⡴⠋⠀⠀⠀⠀⠀⠀⠀⣸⠃⠀⠀⠀⠀⠀⠈⡆" << std::endl;
            std::cout << "⠀⠀⠀⠀⢻⣆⠀⢻⠈⠳⣄⠘⣦⠻⡄⣇⠈⠳⣄⠀⢀⣠⠴⠚⠉⠉⠓⠒⢒⣶⠾⠋⠁⠀⠀⠀⠀⠀⠀⠀⡴⠃⠀⠀⠀⠀⠀⠀⠀⢸" << std::endl;
            std::cout << "⠀⠀⠀⠀⠀⠹⡇⠘⢧⡀⠈⠙⣿⠳⣟⠞⠓⠀⠀⠉⠛⠶⡦⠤⠤⠤⠖⠚⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠞⠁⠀⠀⠀⠀⠀⠀⠀⠀⠈" << std::endl;
            std::cout << "⠀⠀⠀⠀⠀⠀⠈⠲⣄⣁⠀⢀⡼⢦⣈⠓⠀⠀⢀⠀⠀⠀⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⡴⠛⠙⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
            std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠓⠒⠛⠛⠓⠒⠤⠭⠤⣞⣁⣀⣀⣀⣀⣀⣀⣀⣀⡤⢴⣖⣛⡇⠀⠀⠀⠷⠖⠒⠒⠒⠒⠒⠲⠦⢤⣀" << std::endl;
            std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠉⠁⠀⠀⠀⠀⡏⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << std::endl;
            std::cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡇⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⡀⠀⠀⠀" << std::endl;
            break;
        }
        
        
    }

    return 0;
}