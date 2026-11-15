#include <iostream>
#include <cstdlib>

int main()
{
    std::cout << R"(  ____               _____           _   ____               ____ _     ___
 |  _ \  _____   __ |_   _|__   ___ | | | __ )  _____  __  / ___| |   |_ _|
 | | | |/ _ \ \ / /   | |/ _ \ / _ \| | |  _ \ / _ \ \/ / | |   | |    | |
 | |_| |  __/\ V /    | | (_) | (_) | | | |_) | (_) >  <  | |___| |___ | |
 |____/ \___| \_/     |_|\___/ \___/|_| |____/ \___/_/\_\  \____|_____|___|
)";
    return 0;
}

int options()
{
    std::cout << "Please select an option:\n";
    std::cout << "1. Run Utilities\n";
    std::cout << "2. Run Game\n";

    int choice;
    std::cin >> choice;

    if (choice == 1) {
        runPythonUtilities();
    }
   
    else if (choice == 2) {
        runPythongame();
    }

    else{
        std::cerr << "Invalid choice. Please select 1 or 2.\n";
    }
}

int runPythonUtilities()
{
    int status = std::system("py -3 -m src.utils.python.utilsmain");

    if (status != 0) {
        std::cerr << "Python utilities exited with an error.\n";
    }

    return status;
}

int runPythongame()
{
    int status = std::system("py -3 -m src.games.python.game");

    if (status != 0){
        std::cerr << "Python game exited with an error.\n";
    }

    return status;
}
