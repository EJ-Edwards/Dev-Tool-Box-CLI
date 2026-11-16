#include <iostream>
#include "calculator.h"

void run_calculator()
{

    // This stores the operator the user enters.
    char number;
    // This tracks whether the operator is one the calculator supports.
    bool isValidOperator;

    // These store the two numbers that the calculator will use.
    double num1, num2;

    // Std::cout is what gets printed to the console that ask user to enter an operator
    std::cout << "Please enter an operator (+, -, *, /): ";

    // Std::cin is what gets the input from the user and stores it in the variable op
    std::cin >> number;

    // Std::cout is what gets printed to the console that ask user to enter two numbers
    std::cout << "Please enter two numbers: ";

    // Std::cin is what gets the input from the user and stores it in the variables num1 and num2
    std::cin >> num1 >> num2;

    // This stores the answer from the selected math operation.
    double result;

    // This selects the math operation that matches the operator.
    switch (number)
    {

    case '+':
        result = num1 + num2;
        std::cout << "Result: " << result << std::endl;
        break;

    case '-':
        result = num1 - num2;
        std::cout << "Result: " << result << std::endl;
        break;

    case '*':
        result = num1 * num2;
        std::cout << "Result: " << result << std::endl;
        break;

    case '/':
        result = num1 / num2;
        std::cout << "Result: " << result << std::endl;
        break;
    }

    // This checks if the entered character is a supported operator.
    isValidOperator = number == '+' || number == '-' ||
                      number == '*' || number == '/';

    if (isValidOperator)
    {
        return;
    }
    else
    {
        std::cout << "Invalid operator. Please try again." << std::endl;
    }
}