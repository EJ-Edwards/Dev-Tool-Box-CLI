#include <iostream>
#include "unit_converter.h"
using namespace std;


void convert_length(){
    double value;
    cout << "Enter the value to convert: ";
    cin >> value;
    cout << "Select the conversion type:\n";
    cout << "1. Meters to Feet\n";
    cout << "2. Feet to Meters\n";
    int choice;
    cin >> choice;

    switch (choice){
        case 1:
            cout << value << " meters is " << value * 3.28084 << " feet.\n";
            break;
        case 2:
            cout << value << " feet is " << value * 0.3048 << " meters.\n";
            break;
    }
}

void convert_weight(){
    double value;
    cout << "Enter the value to convert: ";
    cin >> value;
    cout << "Select the conversion type:\n";
    cout << "1. Kilograms to Pounds\n";
    cout << "2. Pounds to Kilograms\n";
    int choice;
    cin >> choice;

    switch (choice){
        case 1:
            cout << value << " kilograms is " << value * 2.20462 << " pounds.\n";
            break;
        case 2:
            cout << value << " pounds is " << value * 0.453592 << " kilograms.\n";
            break;
    }
}

void convert_temperature(){
    double value;
    cout << "Enter the value to convert: ";
    cin >> value;
    cout << "Select the conversion type:\n";
    cout << "1. Celsius to Fahrenheit\n";
    cout << "2. Fahrenheit to Celsius\n";
    int choice;
    cin >> choice;

    switch (choice){
        case 1:
            cout << value << " Celsius is " << (value * 9/5) + 32 << " Fahrenheit.\n";
            break;
        case 2:
            cout << value << " Fahrenheit is " << (value - 32) * 5/9 << " Celsius.\n";
            break;
    }
}
