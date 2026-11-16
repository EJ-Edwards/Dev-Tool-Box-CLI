#include <iostream>
#include "unit_converter.h"
using namespace std;




// Function to convert length
void convert_length(){
    // This stores the length the user wants to convert.
    double value;
    cout << "Enter the value to convert: ";
    cin >> value;
    cout << "Select the conversion type:\n";
    cout << "1. Meters to Feet\n";
    cout << "2. Feet to Meters\n";
    // This stores which direction the user wants to convert.
    int choice;
    cin >> choice;

    // This uses the selected option to choose the length conversion.
    switch (choice){
        case 1:
            // This changes meters into feet.
            cout << value << " meters is " << value * 3.28084 << " feet.\n";
            break;
        case 2:
            // This changes feet into meters.
            cout << value << " feet is " << value * 0.3048 << " meters.\n";
            break;
    }
}



// Function to convert weight
void convert_weight(){
    // This stores the weight the user wants to convert.
    double value;
    cout << "Enter the value to convert: ";
    cin >> value;
    cout << "Select the conversion type:\n";
    cout << "1. Kilograms to Pounds\n";
    cout << "2. Pounds to Kilograms\n";
    // This stores which direction the user wants to convert.
    int choice;
    cin >> choice;


    // This uses the selected option to choose the weight conversion.
    switch (choice){
        case 1:
            // This changes kilograms into pounds.
            cout << value << " kilograms is " << value * 2.20462 << " pounds.\n";
            break;
        case 2:
            // This changes pounds into kilograms.
            cout << value << " pounds is " << value * 0.453592 << " kilograms.\n";
            break;
    }
}



// Function to convert temperature
void convert_temperature(){
    // This stores the temperature the user wants to convert.
    double value;
    cout << "Enter the value to convert: ";
    cin >> value;
    cout << "Select the conversion type:\n";
    cout << "1. Celsius to Fahrenheit\n";
    cout << "2. Fahrenheit to Celsius\n";
    // This stores which direction the user wants to convert.
    int choice;
    cin >> choice;

    // This uses the selected option to choose the temperature conversion.

    switch (choice){
        case 1:
            // This changes Celsius into Fahrenheit.
            cout << value << " Celsius is " << (value * 9/5) + 32 << " Fahrenheit.\n";
            break;
        case 2:
            // This changes Fahrenheit into Celsius.
            cout << value << " Fahrenheit is " << (value - 32) * 5/9 << " Celsius.\n";
            break;
    }
}
