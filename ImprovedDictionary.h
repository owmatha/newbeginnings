// File: ImprovedDictionary.h
// Purpose: Header file for the ImprovedDictionary class with NotGPT functionality
// Author: Owen Mather (10592925)
// Date: 23/04/2025

#ifndef IMPROVEDDICTIONARY_H
#define IMPROVEDDICTIONARY_H

#include <iostream>
#include <string>
#include <algorithm>
#include "Dictionary.h"
#include "notGPT.h"

using namespace std;

class ImprovedDictionary : public Dictionary {
public:
    ImprovedDictionary(string fileName = "dictionary_2025S1.txt")
        : newGenerator() {
    }

    void displayMenu() override {
        string userSearch;
        while (true) {
            cout << "-------------------" << endl;
            cout << "Menu" << endl;
            cout << "-------------------" << endl;
            cout << "1) Load the dictionary." << endl;
            cout << "2) Search a word." << endl;
            cout << "3) Show a random word." << endl;
            cout << "4) Generate text." << endl;
            cout << "5) Show next letter probabilities." << endl;
            cout << "999 for exit\n" << endl;

            cin >> userSearch;
            if (userSearch == "999") {
                break;
            } else if (userSearch == "1") {
                cout << "Loading dictionary..." << endl;
                if (loadDictionary("dictionary_2025S1.txt") == 1) {
                    cout << "Dictionary loaded successfully." << endl;
                } else {
                    cout << "Error loading dictionary." << endl;
                }
            } else if (userSearch == "3") {
                printRandWord();
            } else if (userSearch == "2") {
                string userWordSearch;
                cout << "Enter the word to search: ";
                cin >> userWordSearch;
                transform(userWordSearch.begin(), userWordSearch.end(), userWordSearch.begin(), ::tolower);
                wordSearch(userWordSearch);
            } else if (userSearch == "4") {
                newGenerator.generateMyText();
                cout << newGenerator.getGeneratedText() << endl;
            }
            else if (userSearch == "5") {
                string userInput;
                cout << "Enter the two letters: ";
                cin >> userInput;
                transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);
                if (userInput.length() != 2) {
                    cout << "Error – please enter exactly two letters." << endl;
                    continue;
                }
                newGenerator.returnProbabilities(userInput);
            } else {
                cout << "Invalid option. Please try again." << endl;
            }
        }
        cout << "\nGoodbye!" << endl;
    }

private:
    notGPT newGenerator;
};

#endif
