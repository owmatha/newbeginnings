#include "Word.h"

// Constructor
Word::Word() {
    name = "Not Set";
    type = "Undefined";
    definition = "Undefined";
}

// Sets the word attributes
void Word::setWord(string nameInput, string typeInput, string definitionInput) {
    name = nameInput;
    type = typeInput;
    definition = definitionInput;
}

// Gets the word name
string Word::getName() const {
    return name;
}

// Outputs the word's name, type, and definition(s)
void Word::printWord() const {
    cout << "Word: " << name << endl;
    cout << "Type: " << type << endl;

    size_t start = 0, end;
    string def = definition;
    string delimiter = ";  ";
    while ((end = def.find(delimiter, start)) != string::npos) {
        cout << "Definition: " << def.substr(start, end - start) << endl;
        start = end + delimiter.length();
    }
    cout << "Definition: " << def.substr(start) << endl;
    cout << endl;
}
