#include <string>
#include <iostream>

using namespace std;

// Class: Word
// Purpose: Represents a dictionary word with name, type, and definition
// Author: Owen Mather (10592925)
// Date: 23/04/2025
class Word {
public:
    Word();
    void setWord(string nameInput, string typeInput, string definitionInput);
    string getName() const;
    void printWord() const;

private:
    string name;
    string type;
    string definition;
};
