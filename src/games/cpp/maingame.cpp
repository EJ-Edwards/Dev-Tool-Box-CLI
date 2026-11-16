// This library lets the program show text and get the player's choice.
#include <iostream>
// This library helps clear the rest of the input when the player enters something invalid.
#include <limits>

// These headers let this menu call each game's function.
#include "blackjack.h"
#include "rock_paper_scissors.h"
#include "snake.h"
#include "maingame.h"

// This shows the C++ game menu and starts the game the player chooses.
void runCppGame()
{
    // This prints the choices the player can pick from.
    std::cout << "Select a game to play:\n";
    std::cout << "1. Blackjack\n";
    std::cout << "2. Snake\n";
    std::cout << "3. Rock Paper Scissors\n";

    // This gets the number the player enters.
    int choice;
    // This checks if the player entered something that is not a number.
    if (!(std::cin >> choice)) {
        // This lets cin work again after the invalid input.
        std::cin.clear();
        // This removes the rest of the invalid input from the input line.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Invalid input. Please enter a number.\n";
        // This leaves the game menu because the choice was not valid.
        return;
    }
    // This removes the Enter key from the input so the selected game can read input correctly.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // This checks the player's choice and calls the matching game.
    switch (choice) {
    case 1:
        // This starts Blackjack.
        run_blackjack();
        break;
    case 2:
        // This starts Snake.
        run_snake();
        break;
    case 3:
        // This starts Rock Paper Scissors.
        run_rock_paper_scissors();
        break;
    default:
        // This runs when the player enters a number that is not on the menu.
        std::cerr << "Invalid choice. Please select 1, 2, or 3.\n";
        break;
    }
}


