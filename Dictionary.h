#include <vector>
#include <string>
#include <random>
#include "Word.h"

// Class: Dictionary
// Purpose: Loads and manages dictionary entries, and handles menu-based tasks
// Author: Owen Mather (10592925)
// Date: 23/04/2025
class Dictionary {
protected: // Change from private to protected
    mt19937 rng;

public:
    Dictionary();
    virtual void displayMenu();
    int loadDictionary(string dictName);
    void printRandWord();
    int wordSearch(string userWordSearch);

private:
    vector<Word> words;
    string extractType(string S);
};