#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <cstdlib>

#include "utils/calculator.h"
#include "utils/directory_size_analyzer.h"
#include "utils/duplicate_file_finder.h"
#include "utils/file_explorer.h"
#include "utils/system_monitor.h"
#include "utils/unit_converter.h"

#include "games/blackjack.h"
#include "games/maze_solver.h"
#include "games/rock_paper_scissors.h"
#include "games/snake.h"
#include "games/sudoku.h"
#include "games/tic_tac_toe.h"



static void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

static void pauseScreen() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static void printBanner() {
    std::cout << R"(
  ____             _____           _ ____
 |  _ \  _____   _|_   _|__   ___ | | __ )  _____  __
 | | | |/ _ \ \ / / | |/ _ \ / _ \| |  _ \ / _ \ \/ /
 | |_| |  __/\ V /  | | (_) | (_) | | |_) | (_) >  <
 |____/ \___| \_/   |_|\___/ \___/|_|____/ \___/_/\_\
                                            CLI v1.0
    )" << "\n";
}

static int readChoice() {
    int choice = -1;
    std::cout << "  >> ";
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
}


static void showUtilitiesMenu() {
    while (true) {
        clearScreen();
        std::cout << "  ╔══════════════════════════════════╗\n";
        std::cout << "  ║        UTILITIES  MENU           ║\n";
        std::cout << "  ╠══════════════════════════════════╣\n";
        std::cout << "  ║  1. Calculator                   ║\n";
        std::cout << "  ║  2. Directory Size Analyzer      ║\n";
        std::cout << "  ║  3. Duplicate File Finder        ║\n";
        std::cout << "  ║  4. File Explorer                ║\n";
        std::cout << "  ║  5. System Monitor               ║\n";
        std::cout << "  ║  6. Unit Converter               ║\n";
        std::cout << "  ║  0. Back                         ║\n";
        std::cout << "  ╚══════════════════════════════════╝\n";

        int choice = readChoice();
        switch (choice) {
            case 1: run_calculator();              pauseScreen(); break;
            case 2: run_directory_size_analyzer();  pauseScreen(); break;
            case 3: run_duplicate_file_finder();    pauseScreen(); break;
            case 4: run_file_explorer();            pauseScreen(); break;
            case 5: run_system_monitor();           pauseScreen(); break;
            case 6: run_unit_converter();           pauseScreen(); break;
            case 0: return;
            default:
                std::cout << "  Invalid option.\n";
                pauseScreen();
        }
    }
}

static void showGamesMenu() {
    while (true) {
        clearScreen();
        std::cout << "  ╔══════════════════════════════════╗\n";
        std::cout << "  ║          GAMES  MENU             ║\n";
        std::cout << "  ╠══════════════════════════════════╣\n";
        std::cout << "  ║  1. Blackjack                    ║\n";
        std::cout << "  ║  2. Maze Solver                  ║\n";
        std::cout << "  ║  3. Rock Paper Scissors          ║\n";
        std::cout << "  ║  4. Snake                        ║\n";
        std::cout << "  ║  5. Sudoku                       ║\n";
        std::cout << "  ║  6. Tic Tac Toe                  ║\n";
        std::cout << "  ║  7. Timer/Stopwatch              ║\n";
        std::cout << "  ║  0. Back                         ║\n";
        std::cout << "  ╚══════════════════════════════════╝\n";

        int choice = readChoice();
        switch (choice) {
            case 1: run_blackjack();            pauseScreen(); break;
            case 2: run_maze_solver();           pauseScreen(); break;
            case 3: run_rock_paper_scissors();   pauseScreen(); break;
            case 4: run_snake();                 pauseScreen(); break;
            case 5: run_sudoku();                pauseScreen(); break;
            case 6: run_tic_tac_toe();           pauseScreen(); break;
            case 7: run_timer_stopwatch();       pauseScreen(); break;
            case 0: return;
            default:
                std::cout << "  Invalid option.\n";
                pauseScreen();
        }
    }
}



int main() {
    while (true) {
        clearScreen();
        printBanner();

        std::cout << "  ╔══════════════════════════════════╗\n";
        std::cout << "  ║          MAIN  MENU              ║\n";
        std::cout << "  ╠══════════════════════════════════╣\n";
        std::cout << "  ║  1. Utilities                    ║\n";
        std::cout << "  ║  2. Games                        ║\n";
        std::cout << "  ║  0. Exit                         ║\n";
        std::cout << "  ╚══════════════════════════════════╝\n";

        int choice = readChoice();
        switch (choice) {
            case 1: showUtilitiesMenu(); break;
            case 2: showGamesMenu();     break;
            case 0:
                clearScreen();
                std::cout << "  Goodbye!\n\n";
                return 0;
            default:
                std::cout << "  Invalid option.\n";
                pauseScreen();
        }
    }
}
