#ifndef NOTGPT_H
#define NOTGPT_H

#include <string>
#include <map>
#include <random>

using namespace std;

class LetterPair {
public:
    LetterPair(char l1, char l2);
    string getLetterPair() const;
    bool operator<(const LetterPair& other) const;

private:
    char letterOne, letterTwo;
};

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

    map<LetterPair, map<char, int>> letterPairs;
    mt19937 rng;
    string outputText, myText;
};

#endif