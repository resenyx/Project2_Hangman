/* 
 * File:   main.cpp
 * Author: Ma. Lana Theresa B. Silvestre
 * Created on June 4, 2023, 10:06 PM
 * Purpose: Hangman Game
 */

//System Libraries
#include <iostream>  //Input - Output Library
#include <cstdlib>   //Srand to set the seed
#include <ctime>     //Time for rand
#include <fstream>   //File I/O
#include <string>    //String Library
#include <vector>    //Vector Library
using namespace std;

//User Libraries
//Global Constants

//Function Prototypes
void welcome();
void hangman();
void savescr(const string& plyrNm, int score);
void scores();
bool ckGuess(char guess, const string& word, string& gssdWrd);
bool winLose(const string& gssdWrd);
string chsnwrd();

//Execution Begins Here!
int main(int argc, char** argv) {
    welcome();
    hangman();

    return 0;
}

void welcome() {
    cout << "Welcome to Hangman!" << endl;
    cout << "Guess the word before the hangman is complete." << endl;
    cout << "Good luck!" << endl << endl;
}

void hangman() {
    string word = chsnwrd();
    string gssdWrd(word.length() * 2 - 1, '_');
    int xguess = 0, //Number of wrong guesses
        mxguess = 7;    //Maximum number of guess
    vector<char> gssdLtr;
    
    while (xguess < 7 && !winLose(gssdWrd)) {
        cout << "Word: ";
        for (int i = 0; i < gssdWrd.length(); i += 2) {
            cout << gssdWrd[i] << " ";
        }
        cout << endl;
        
        cout << "Guessed letters: ";
        for (char letter : gssdLtr) {
            cout << letter << " ";
        }
        cout << endl;
        
        cout << "Enter your guess: ";
        char guess;
        cin >> guess;
        guess = tolower(guess);
        
        if (isalpha(guess)) {
            if (ckGuess (guess, word, gssdWrd)) {
            cout << "Correct guess!\n";
            } else { 
            cout << "Wrong guess!\n";
            xguess++;
            }
            gssdLtr.push_back(guess);
            
            
        } else { 
                cout << "Invalid input./ Please enter a letter:";
            }
            cout << "Remaining guesses: " << mxguess - xguess << endl;
            cout << endl;
        }
  
        if (winLose(gssdWrd)) {
        cout << "Congratulations! You guessed the word: ";
        for (int i = 0; i < gssdWrd.length(); i += 2) {
            cout << gssdWrd[i] << " ";
        }
        cout << endl;
        cout << "You win!" << endl;
        cout << "Enter your name: ";
        string plyrNm;
        cin >> plyrNm;
        savescr(plyrNm, mxguess - xguess);
        scores();
        
    } else {
        cout << "Sorry, you lost! The word was: " << word << endl;
    }
    
}
    string chsnwrd() {
    vector<string> wrdList;
    ifstream file("wordlist.txt");
    if (!file) {
        cerr << "Error opening file." << endl;
        exit(1);
    }
    string word;
    while (file >> word) {
        wrdList.push_back(word);
    }
    file.close();
    srand(static_cast<unsigned int>(time(0)));
    int rdmIndx = rand() % wrdList.size();
    return wrdList[rdmIndx];
   }
    
    bool ckGuess(char guess, const string& word, string& gssdWrd) {
    bool rghtGss = false;
    for (int i = 0; i < word.length(); i++) {
        if (tolower(word[i]) == guess) {
            gssdWrd[i * 2] = word[i];
            rghtGss = true;
        }
    }
    return rghtGss;
   }
    
    bool winLose(const string& gssdWrd) {
    for (int i = 0; i < gssdWrd.length(); i += 2) {
        if (gssdWrd[i] == '_') {
            return false;
        }
    }
    return true;
}
    
 void savescr(const string& plyrNm, int score) {
    string scrFile = "scores.txt";
    ofstream file(scrFile, ios::app);
    if (!file) {
        cerr << "Error opening file." << endl;
        exit(1);
    }

    file << plyrNm << " " << score << endl;
    file.close();
}

void scores() {
    string scrFile = "scores.txt";
    ifstream file(scrFile);
    if (!file) {
        cerr << "Error opening file." << endl;
        exit(1);
    }

    string plyrNm;
    int score;
    cout << "High Scores:" << endl;
    while (file >> plyrNm >> score) {
        cout << plyrNm << " - " << score << endl;
    }

    file.close();
}