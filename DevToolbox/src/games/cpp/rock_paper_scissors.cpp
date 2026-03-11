#include <iostream>
#include <string>
#include <random>
#include <limits>
#include <algorithm>

static std::mt19937& rng() {
    static std::mt19937 gen(std::random_device{}());
    return gen;
}

static std::string choiceName(int c) {
    switch (c) {
        case 0: return "Rock";
        case 1: return "Paper";
        case 2: return "Scissors";
        default: return "?";
    }
}

// Returns: 0 = tie, 1 = player wins, 2 = computer wins
static int judge(int player, int computer) {
    if (player == computer) return 0;
    // Rock beats Scissors, Scissors beats Paper, Paper beats Rock
    if ((player == 0 && computer == 2) ||
        (player == 1 && computer == 0) ||
        (player == 2 && computer == 1))
        return 1;
    return 2;
}

void run_rock_paper_scissors() {
    int playerScore = 0;
    int computerScore = 0;
    int ties = 0;
    int rounds = 0;

    std::cout << "\n  === ROCK  PAPER  SCISSORS ===\n";
    std::cout << "  First to 3 wins! (or type 'quit' to stop)\n";

    std::uniform_int_distribution<int> dist(0, 2);

    while (playerScore < 3 && computerScore < 3) {
        std::cout << "\n  Round " << (rounds + 1) << "  |  You: " << playerScore
                  << "  Computer: " << computerScore << "  Ties: " << ties << "\n";
        std::cout << "  Pick (r)ock, (p)aper, or (s)cissors: ";

        std::string input;
        if (!std::getline(std::cin, input) || input.empty()) continue;

        // Trim and lowercase
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);

        if (input == "quit" || input == "q") {
            std::cout << "  Game ended early.\n";
            break;
        }

        int playerChoice;
        if (input == "r" || input == "rock")          playerChoice = 0;
        else if (input == "p" || input == "paper")    playerChoice = 1;
        else if (input == "s" || input == "scissors") playerChoice = 2;
        else {
            std::cout << "  Invalid choice. Use r/p/s or rock/paper/scissors.\n";
            continue;
        }

        int compChoice = dist(rng());
        ++rounds;

        std::cout << "  You chose:      " << choiceName(playerChoice) << "\n";
        std::cout << "  Computer chose: " << choiceName(compChoice) << "\n";

        int result = judge(playerChoice, compChoice);
        if (result == 0) {
            ++ties;
            std::cout << "  It's a tie!\n";
        } else if (result == 1) {
            ++playerScore;
            std::cout << "  You win this round!\n";
        } else {
            ++computerScore;
            std::cout << "  Computer wins this round!\n";
        }
    }

    // Final scoreboard
    std::cout << "\n  ====== FINAL SCORE ======\n";
    std::cout << "  You:      " << playerScore << "\n";
    std::cout << "  Computer: " << computerScore << "\n";
    std::cout << "  Ties:     " << ties << "\n";
    std::cout << "  Rounds:   " << rounds << "\n";

    if (playerScore >= 3)
        std::cout << "\n  Congratulations — you win the match!\n";
    else if (computerScore >= 3)
        std::cout << "\n  The computer wins the match. Better luck next time!\n";
    std::cout << std::endl;
}