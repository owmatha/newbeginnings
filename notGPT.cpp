#include "notGPT.h"
#include "ImprovedDictionary.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

// Implementation of LetterPair
LetterPair::LetterPair(char l1, char l2) : letterOne(l1), letterTwo(l2) {}

std::string LetterPair::getLetterPair() const {
    return std::string(1, letterOne) + std::string(1, letterTwo);
}

bool LetterPair::operator<(const LetterPair& other) const {
    return std::tie(letterOne, letterTwo) < std::tie(other.letterOne, other.letterTwo);
}

wordGenerator::wordGenerator() {
    rng.seed(std::random_device{}());
    loadText("littleprince.txt");
}

// Function: generateMyText
// Purpose: Accesses private functions to generate text
// Input: None
// Output: None (stores result internally)
// Author: Owen Mather (10592925)
// Date: 23/04/2025
void wordGenerator::generateMyText() {
    this->generateText();
}

// Function: getGeneratedText
// Purpose: Returns the generated paragraph
// Input: None
// Output: A string containing the final output text
// Author: Owen Mather (10592925)
// Date: 23/04/2025
std::string wordGenerator::getGeneratedText() {
    return outputText;
}

// Function: returnProbabilities
// Purpose: Displays the top 3 most likely next characters after a given 2-character input
// Input: 2-character string
// Output: Printed list of characters and probabilities
// Author: Owen Mather (10592925)
// Date: 23/04/2025
void wordGenerator::returnProbabilities(const std::string& letters) {
    std::vector<std::pair<char, int>> counts = {{'\0', 0}, {'\0', 0}, {'\0', 0}};
    int total = 0;

    for (auto& letter : letterPairs[LetterPair(letters[0], letters[1])]) {
        total += letter.second;
        if (letter.second > counts[0].second) {
            counts[2] = counts[1];
            counts[1] = counts[0];
            counts[0] = {letter.first, letter.second};
        } else if (letter.second > counts[1].second) {
            counts[2] = counts[1];
            counts[1] = {letter.first, letter.second};
        } else if (letter.second > counts[2].second) {
            counts[2] = {letter.first, letter.second};
        }
    }

    for (auto& countings : counts) {
        std::cout << "'" << countings.first << "' => " << countings.second << " = " << static_cast<double>(countings.second) / total * 100 << "%." << std::endl;
    }
    return;
}

// Function: loadText
// Purpose: Reads input file, filters characters, and records letter frequencies
// Input: File name (string)
// Output: None (updates private variables)
// Author: Owen Mather (10592925)
// Date: 23/04/2025
void wordGenerator::loadText(const std::string& fileName) {
    std::string allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ,' ";
    std::ifstream textFile{fileName};
    std::string rawText{std::istreambuf_iterator<char>(textFile), std::istreambuf_iterator<char>()};
    textFile.close();

    for (char& c : rawText) {
        if (allowedChars.find(c) != std::string::npos) {
            myText += std::tolower(c);
        }
    }

    for (int i = 0; i < myText.length() - 2; i++) {
        LetterPair key(myText[i], myText[i + 1]);
        letterPairs[key][myText[i + 2]] += 1;
    }
}

// Function: generateStartingLetters
// Purpose: Randomly selects a valid letter to start a word
// Input: None
// Output: String containing one starter letter
// Author: Owen Mather (10592925)
// Date: 23/04/2025
std::string wordGenerator::generateStartingLetters() {
    std::string approvedStarters = "bcdefghjklmnopgrstuvwyz";
    std::uniform_int_distribution<> dist(0, approvedStarters.length() - 1);
    char nextLetter = approvedStarters[dist(rng)];
    return " "s + nextLetter;
}

// Function: generateWord
// Purpose: Constructs a made-up word using trigram character prediction
// Input: Minimum and maximum length of the word (int)
// Output: An English-like word (string)
// Author: Owen Mather (10592925)
// Date: 21/04/2025
std::string wordGenerator::generateWord(int lengMin, int lengMax) {
    std::string randomWord = generateStartingLetters();

    std::uniform_int_distribution<> lengthDist(lengMin, lengMax);
    int targetLength = lengthDist(rng);

    while (randomWord.size() < targetLength) {
        int totalWeight = 0;
        char l1 = randomWord[randomWord.length() - 2], l2 = randomWord[randomWord.length() - 1];
        LetterPair key(l1, l2);

        for (const auto& letter : letterPairs[key]) {
            if (letter.first == ' ' || letter.first == ',') continue;
            totalWeight += letter.second;
        }

        if (totalWeight == 0) break;

        std::uniform_int_distribution<> dist(0, totalWeight - 1);
        int myWeight = dist(rng);

        for (const auto& myPair : letterPairs[key]) {
            char ch = myPair.first;
            int count = myPair.second;
            if (ch == ' ' or ch == ',') continue;
            myWeight -= count;
            if (myWeight <= 0) {
                randomWord += ch;
                break;
            }
        }
    }

    return randomWord;
}

// Function: generateSentence
// Purpose: Constructs a sentence made of multiple generated words, ending with a full stop
// Input: Minimum and maximum number of words (int) defaulted to assignment requirements
// Output: A sentence (edited for grammar)
// Author: Owen Mather (10592925)
// Date: 23/04/2025
std::string wordGenerator::generateSentence(int lengMin, int lengMax) {
    std::string mySentence = "";

    std::uniform_int_distribution<> wordCountDist(lengMin, lengMax);
    int wordCount = wordCountDist(rng);

    for (int i = 0; i < wordCount; i++) {
        mySentence += this->generateWord();
    }

    mySentence.erase(0, mySentence.find_first_not_of(' '));
    mySentence.erase(mySentence.find_last_not_of(' ') + 1);
    mySentence.erase(mySentence.find_last_not_of(',') + 1);
    mySentence += ". ";
    mySentence[0] = std::toupper(mySentence[0]);

    return mySentence;
}

// Function: generateText
// Purpose: Creates a paragraph by generating 4–8 randomised sentences
// Input: None
// Output: Stored internally in outputText
// Author: Owen Mather (10592925)
// Date: 23/04/2025
void wordGenerator::generateText() {
    this->outputText = ""; // Clear previous output
    std::uniform_int_distribution<> sentenceCountDist(4, 8);
    int sentenceCount = sentenceCountDist(rng);

    for (int i = 0; i < sentenceCount; ++i) {
        this->outputText += this->generateSentence();
    }
}
