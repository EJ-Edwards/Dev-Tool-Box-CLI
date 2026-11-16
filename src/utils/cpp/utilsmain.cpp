#include <iostream>
#include <limits>

#include "calculator.h"
#include "unit_converter.h"

int main()
{
    // This keeps the utilities menu open until the user chooses to exit.
    while (true) {
        std::cout << "\nC++ Utilities Menu:\n";
        std::cout << "1. Calculator\n";
        std::cout << "2. Length converter\n";
        std::cout << "3. Weight converter\n";
        std::cout << "4. Temperature converter\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        if (!(std::cin >> choice)) {
            // This clears the invalid input so the menu can ask again.
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid input. Please enter a number.\n";
            continue;
        }

        // This starts the utility that matches the user's choice.
        switch (choice) {
        case 0:
            return 0;
        case 1:
            run_calculator();
            break;
        case 2:
            convert_length();
            break;
        case 3:
            convert_weight();
            break;
        case 4:
            convert_temperature();
            break;
        default:
            std::cerr << "Invalid choice. Please select 0, 1, 2, 3, or 4.\n";
            break;
        }
    }
}
