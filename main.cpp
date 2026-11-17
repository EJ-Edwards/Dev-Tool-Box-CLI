#include <iostream>
#include <cstdlib>
#include <limits>

// These declarations let the menu call functions that are defined later.
void options();
int runPythonUtilities();
int runCppUtilities();
int runCppGame();
int runCommand(const char* command, const char* programName);

// This starts the program by showing the logo and opening the main menu.
int main()
{
    // This prints the Dev Tool Box logo.
    std::cout << R"(  ____               _____           _   ____               ____ _     ___
 |  _ \  _____   __ |_   _|__   ___ | | | __ )  _____  __  / ___| |   |_ _|
 | | | |/ _ \ \ / /   | |/ _ \ / _ \| | |  _ \ / _ \ \/ / | |   | |    | |
 | |_| |  __/\ V /    | | (_) | (_) | | | |_) | (_) >  <  | |___| |___ | |
 |____/ \___| \_/     |_|\___/ \___/|_| |____/ \___/_/\_\  \____|_____|___|
)";
    // This opens the menu after the logo is shown.
    options();
    return 0;
}

// This shows the main choices and runs the program the player selects.
void options()
{
    // This keeps showing the main menu after a module closes.
    while (true) {
        std::cout << "\nPlease select an option:\n";
        std::cout << "1. Run Utilities Python\n";
        std::cout << "2. Run Utilities C++\n";
        std::cout << "3. Run Game C++\n";
        std::cout << "4. Exit\n";

        // This stores the number the player enters.
        int choice;
        // This checks that the player entered a number.
        if (!(std::cin >> choice)) {
            if (std::cin.eof()) {
                return;
            }
            // This clears invalid input so the menu can ask again.
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid input. Please enter a number.\n";
            continue;
        }

        // This calls the matching program based on the selected number.
        switch (choice) {
        case 1:
            runPythonUtilities();
            break;
        case 2:
            runCppUtilities();
            break;
        case 3:
            runCppGame();
            break;
        case 4:
            return;
        default:
            std::cerr << "Invalid choice. Please select 1, 2, 3, or 4.\n";
            break;
        }
    }
}

// This runs a command and reports if it exits with an error.
int runCommand(const char* command, const char* programName)
{
    const int status = std::system(command);
    if (status != 0) {
        std::cerr << programName << " exited with an error.\n";
    }
    return status;
}

// This starts the Python utilities menu.
int runPythonUtilities()
{
    return runCommand("python -m src.utils.python.utilsmain", "Python utilities");
}

// This starts the C++ utilities program.
int runCppUtilities()
{
    return runCommand("build-cmake\\bin\\cpp_utilities.exe", "C++ utilities");
}

// This starts the C++ games program.
int runCppGame()
{
    return runCommand("build-cmake\\bin\\cpp_games.exe", "C++ games");
}
