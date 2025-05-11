#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

Dictionary::Dictionary() {
    rng.seed(random_device{}());
}

void Dictionary::displayMenu() {
    string userSearch;
    while (true) {
        cout << "-------------------" << endl;
        cout << "Menu" << endl;
        cout << "-------------------" << endl;
        cout << "1) Load the dictionary." << endl;
        cout << "2) Search a word." << endl;
        cout << "3) Show a random word." << endl;
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
            if (words.empty()) {
                cout << "Error – dictionary empty" << endl;
                continue;
            }
            wordSearch(userWordSearch);
        }
    }
    cout << "\nGoodbye!" << endl;
}

int Dictionary::loadDictionary(string dictName) {
    ifstream dictFile(dictName);
    if (!dictFile.is_open()) {
        return 0;
    }

    words.clear();
    string temp, name, type, definition;

    getline(dictFile, temp);
    getline(dictFile, temp);

    while (getline(dictFile, name)) {
        if (!getline(dictFile, type)) break;
        if (!getline(dictFile, definition)) break;
        getline(dictFile, temp); // skip blank line

        name.erase(name.find_last_not_of("; \t\r\n") + 1);
        type.erase(type.find_last_not_of("; \t\r\n") + 1);
        definition.erase(definition.find_last_not_of("; \t\r\n") + 1);

        type = extractType(type);

        Word word;
        word.setWord(name, type, definition);
        words.push_back(word);
    }

    dictFile.close();
    return 1;
}

void Dictionary::printRandWord() {
    if (words.empty()) {
        cout << "Error – dictionary empty" << endl;
        return;
    }

    uniform_int_distribution<> dist(0, words.size() - 1);
    int randomNum = dist(rng);
    cout << "Your random word is:" << endl;
    words[randomNum].printWord();
}

int Dictionary::wordSearch(string userWordSearch) {
    for (const Word& word : words) {
        string wordName = word.getName();
        transform(wordName.begin(), wordName.end(), wordName.begin(), ::tolower);
        if (wordName == userWordSearch) {
            word.printWord();
            return 0;
        }
    }
    cout << "Word not found.\n" << endl;
    return 1;
}

string Dictionary::extractType(string S) {
    if (S == "v") return "(v.)";
    if (S == "n") return "(n.)";
    if (S == "adv") return "(adv.)";
    if (S == "adj") return "(adj.)";
    if (S == "prep") return "(prep.)";
    if (S == "pn") return "(pn.)";
    if (S == "n_and_v") return "(n.v.)";
    if (S == "misc") return "(misc.)";
    return "(unknown)";
}