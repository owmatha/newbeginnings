#ifndef NOTGPT_H
#define NOTGPT_H

#include <string>
#include <map>
#include <random>

using namespace std;

// Class: notGPT
// Purpose: Generates 4-8 English-like sentence paragraphs with 5-10 words each
// Author: Owen Mather (10592925)
// Date: 23/04/2025
class notGPT {
public:
    notGPT();
    void generateMyText();
    string getGeneratedText();
    void returnProbabilities(const string& letters);

private:
    void loadText(const string& fileName);
    string generateStartingLetters();
    string generateWord(int lengMin = 3, int lengMax = 15);
    string generateSentence(int lengMin = 5, int lengMax = 10);
    void generateText();

    map<string, map<char, int>> letterPairs;
    mt19937 rng;
    string outputText, myText;
};

#endif
