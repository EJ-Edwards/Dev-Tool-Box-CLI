#include <iostream>
#include <string>
#include <random>
#include <limits>
#include <algorithm>
#include <array>

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

// Returns the choice that beats the given choice
static int counterOf(int c) {
    return (c + 1) % 3; // Rock(0)->Paper(1), Paper(1)->Scissors(2), Scissors(2)->Rock(0)
}

// Returns the choice that loses to the given choice
static int loserTo(int c) {
    return (c + 2) % 3; // Rock(0)->Scissors(2), Paper(1)->Rock(0), Scissors(2)->Paper(1)
}

// Returns: 0 = tie, 1 = player wins, 2 = computer wins
static int judge(int player, int computer) {
    if (player == computer) return 0;
    if ((player == 0 && computer == 2) ||
        (player == 1 && computer == 0) ||
        (player == 2 && computer == 1))
        return 1;
    return 2;
}

enum Difficulty { EASY = 1, MODERATE = 2, HARD = 3 };

// Easy: 50% chance to pick the losing move, 25% tie move, 25% winning move
static int easyChoice(int /*unused*/) {
    std::uniform_int_distribution<int> dist(0, 3);
    return dist(rng()); // 0-3 mapped below is wrong, let's use weighted
}

static int computerPick(Difficulty diff, const std::array<int, 3>& playerHistory, int totalRounds) {
    std::uniform_int_distribution<int> dist(0, 2);

    switch (diff) {
        case EASY: {
            // Computer is weak: 50% random, 50% deliberately picks losing move based on most common player choice
            std::uniform_int_distribution<int> coin(0, 1);
            if (coin(rng()) == 0) {
                return dist(rng()); // pure random
            }
            // Pick the move that loses to the most common player choice
            int mostPlayed = 0;
            if (playerHistory[1] > playerHistory[mostPlayed]) mostPlayed = 1;
            if (playerHistory[2] > playerHistory[mostPlayed]) mostPlayed = 2;
            if (totalRounds == 0) return dist(rng());
            return loserTo(mostPlayed); // deliberately pick a weak move
        }
        case MODERATE: {
            // Purely random — fair play
            return dist(rng());
        }
        case HARD: {
            // Predicts player's most frequent choice and counters it
            if (totalRounds < 2) return dist(rng()); // not enough data yet

            // 70% strategic, 30% random to avoid being fully deterministic
            std::uniform_int_distribution<int> chance(1, 10);
            if (chance(rng()) <= 3) return dist(rng());

            // Counter the player's most common choice
            int mostPlayed = 0;
            if (playerHistory[1] > playerHistory[mostPlayed]) mostPlayed = 1;
            if (playerHistory[2] > playerHistory[mostPlayed]) mostPlayed = 2;
            return counterOf(mostPlayed);
        }
    }
    return dist(rng());
}

static std::string difficultyName(Difficulty d) {
    switch (d) {
        case EASY:     return "Easy";
        case MODERATE: return "Moderate";
        case HARD:     return "Hard";
    }
    return "Unknown";
}

void run_rock_paper_scissors() {
    int playerScore = 0;
    int computerScore = 0;
    int ties = 0;
    int rounds = 0;
    std::array<int, 3> playerHistory = {0, 0, 0}; // tracks Rock, Paper, Scissors counts

    std::cout << "\n  === ROCK  PAPER  SCISSORS ===\n\n";
    std::cout << "  Select difficulty:\n";
    std::cout << "    1. Easy\n";
    std::cout << "    2. Moderate\n";
    std::cout << "    3. Hard\n";
    std::cout << "  >> ";

    Difficulty diff = MODERATE;
    std::string diffInput;
    if (std::getline(std::cin, diffInput) && !diffInput.empty()) {
        if (diffInput == "1" || diffInput == "easy" || diffInput == "e")        diff = EASY;
        else if (diffInput == "2" || diffInput == "moderate" || diffInput == "m") diff = MODERATE;
        else if (diffInput == "3" || diffInput == "hard" || diffInput == "h")    diff = HARD;
    }

    std::cout << "\n  Difficulty: " << difficultyName(diff) << "\n";
    std::cout << "  First to 3 wins! (or type 'quit' to stop)\n";

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

        int compChoice = computerPick(diff, playerHistory, rounds);
        ++playerHistory[playerChoice];
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
    std::cout << "  Difficulty: " << difficultyName(diff) << "\n";
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