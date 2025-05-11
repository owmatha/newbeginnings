#include "Word.h"

// Function: Word
// Purpose: Constructor that sets default values for the Word attributes
// Input: None
// Output: None
// Author: Owen Mather (10592925)
// Date: 24/04/2025
Word::Word() {
    name = "Not Set";
    type = "Undefined";
    definition = "Undefined";
}

// Function: setWord
// Purpose: Assigns values to name, type, and definition fields
// Input: Three strings – name, type, and definition
// Output: None
// Author: Owen Mather (10592925)
// Date: 25/04/2025
void Word::setWord(string nameInput, string typeInput, string definitionInput) {
    name = nameInput;
    type = typeInput;
    definition = definitionInput;
}

// Function: getName
// Purpose: Retrieves the name of the word
// Input: None
// Output: The word's name (string)
// Author: Owen Mather (10592925)
// Date: 25/04/2025
string Word::getName() const {
    return name;
}

// Function: printWord
// Purpose: Outputs the word's details in a formatted layout
// Input: None
// Output: Prints word, returns nothing
// Author: Owen Mather (10592925)
// Date: 25/04/2025
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
