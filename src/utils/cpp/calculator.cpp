#include <iostream>

int main()
{

    char number;
    // Double creates a variable that can hold decimal values

    // Bool is a variable that can hold true or false values
    bool isValidOperator;

    double num1, num2;

    // Std::cout is what gets printed to the console that ask user to enter an operator
    std::cout << "Please enter an operator (+, -, *, /): ";

    // Std::cin is what gets the input from the user and stores it in the variable op
    std::cin >> number;

    // Std::cout is what gets printed to the console that ask user to enter two numbers
    std::cout << "Please enter two numbers: ";

    // Std::cin is what gets the input from the user and stores it in the variables num1 and num2
    std::cin >> num1 >> num2;

    double result;

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

    isValidOperator = number == '+' || number == '-' ||
                      number == '*' || number == '/';

    if (isValidOperator)
    {
        return 0;
    }
    else
    {
        std::cout << "Invalid operator. Please try again." << std::endl;
        return 1;
    }
}