
/* 
 * File:   main.cpp
 * Author: Ma. Lana Theresa B. Silvestre
 * Created on June 4, 2023, 8:31 PM
 * Purpose: Hangman Game
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function prototypes
void printWelcome();
void playHangman();
string chooseWord();
bool checkGuess(char guess, const string& word, string& guessedWord);
bool isGameWon(const string& guessedWord);
void saveScore(const string& playerName, int score);
void displayScores();

// Global variables
const int MAX_WRONG_GUESSES = 7;
const string SCORES_FILE = "scores.txt";

int main() {
    printWelcome();
    playHangman();

    return 0;
}

void printWelcome() {
    cout << "Welcome to Hangman!" << endl;
    cout << "Guess the word before the hangman is complete." << endl;
    cout << "Good luck!" << endl << endl;
}

void playHangman() {
    string word = chooseWord();
    string guessedWord(word.length(), '_');
    int wrongGuesses = 0;
    vector<char> guessedLetters;

    while (wrongGuesses < MAX_WRONG_GUESSES && !isGameWon(guessedWord)) {
        cout << "Word: " << guessedWord << endl;
        cout << "Guessed letters: ";
        for (char letter : guessedLetters) {
            cout << letter << " ";
        }
        cout << endl;

        cout << "Enter your guess: ";
        char guess;
        cin >> guess;
        guess = tolower(guess);

        if (isalpha(guess)) {
            if (checkGuess(guess, word, guessedWord)) {
                cout << "Correct guess!" << endl;
            } else {
                cout << "Wrong guess!" << endl;
                wrongGuesses++;
            }
            guessedLetters.push_back(guess);
        } else {
            cout << "Invalid input. Please enter a letter." << endl;
        }
        cout << endl;
    }

    if (isGameWon(guessedWord)) {
        cout << "Congratulations! You guessed the word: " << word << endl;
        cout << "You win!" << endl;
        cout << "Enter your name: ";
        string playerName;
        cin >> playerName;
        saveScore(playerName, MAX_WRONG_GUESSES - wrongGuesses);
        displayScores();
    } else {
        cout << "Sorry, you lost! The word was: " << word << endl;
    }
}

string chooseWord() {
    vector<string> wordList;
    ifstream file("wordlist.txt");
    if (!file) {
        cerr << "Error opening file." << endl;
        exit(1);
    }

    string word;
    while (file >> word) {
        wordList.push_back(word);
    }

    file.close();

    srand(static_cast<unsigned int>(time(0)));
    int randomIndex = rand() % wordList.size();

    return wordList[randomIndex];
}

bool checkGuess(char guess, const string& word, string& guessedWord) {
    bool correctGuess = false;
    for (int i = 0; i < word.length(); i++) {
        if (tolower(word[i]) == guess) {
            guessedWord[i] = word[i];
            correctGuess = true;
        }
    }
    return correctGuess;
}

bool isGameWon(const string& guessedWord) {
    return guessedWord.find('_') == string::npos;
}

void saveScore(const string& playerName, int score) {
    ofstream file(SCORES_FILE, ios::app);
    if (!file) {
        cerr << "Error opening file." << endl;
        exit(1);
    }

    file << playerName << " " << score << endl;
    file.close();
}

void displayScores() {
    ifstream file(SCORES_FILE);
    if (!file) {
        cerr << "Error opening file." << endl;
        exit(1);
    }

    string playerName;
    int score;
    cout << "High Scores:" << endl;
    while (file >> playerName >> score) {
        cout << playerName << " - " << score << endl;
    }

    file.close();
}
