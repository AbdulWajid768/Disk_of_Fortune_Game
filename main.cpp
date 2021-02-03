/*
 * Name: YOUR NAME
 * Project 1: Disk of Fortune
 * Course: CSI218 (Fall 2020)
 * Date: THE DATE
 * Description: Play game in which 3 players try to solve a puzzle
 *				by guessing letters in a phrase.  Virtual money is
 *				allotted for correct letter guesses.
 * BONUS: Record used letters done.
 */

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include "obscuredentries.cpp"
#include <set>
using namespace std;

// Definitions for functions that help game proceed.
// Show any punctuation (non-letters) in puzzle.
// Returns copy of puzzle with punctuation revealed.
ObscuredEntries<char> showPunct(ObscuredEntries<char> puzzle);

// Show a letter (passed) that user guessed in puzzle.
// Return a count of how many of such letter found.
int findLetter(ObscuredEntries<char>& puzzle, char letter);

// Return whether puzzle is solved (all letters revealed).
bool solved(const ObscuredEntries<char>& puzzle);

//Return whether letter is already guessed
bool isLetterAlreadyGuessed(set<char> guessedLetters, char letter);

int main()
{
	// Values of each item on "disk" (see writeup) that is spun.
	const int NUM_ITEMS = 24;
	const string ITEMS[NUM_ITEMS] = {
		"450",
		"700",
		"300",
		"600",
		"1000",
		"200",
		"600",
		"BANKRUPT",
		"500",
		"200",
		"LOSE TURN",
		"400",
		"200",
		"900",
		"250",
		"300",
		"900",
		"BANKRUPT",
		"500",
		"400",
		"250",
		"LOSE TURN",
		"800",
		"150"
	};

	// 2D vector that holds phrase to solve as puzzle.
	vector<vector<char>> phrase;


	// Allow user to enter words in phrase.
	cout << "Enter phrase to solve (each word 1 line, blank line when done):" << endl;
	string word;

	getline(cin, word);  // read first word

	while (word != "")  // done entering?
	{
		// Add word as vector of characters (use anonymous object
		// with constructor that extracts characters from string
		// using iterators).
		phrase.push_back(vector<char>(word.begin(), word.end()));

		// Read another word.
		getline(cin, word);
	}



	// Seed random number generator (for determining player spin).
	// COMMENT OUT IF WISH TO TEST WITH SAME SPINS EACH TIME.
	srand((unsigned int)time(NULL));

	// Create puzzle with all letters hidden.
	const char HIDDEN = '*';
	ObscuredEntries<char> puzzle(phrase, HIDDEN);

	//To show the punctuation marks
	puzzle = showPunct(puzzle);
	
	const int NUM_PLAYERS = 3;

	//To hold character guessed by player
	set<char>  guessedLetters;
	
	// Track prize money accumulated by each player.
	int prizeMoney[NUM_PLAYERS] = { 0, 0, 0 };

	int currPlayer = 0;  // start with first player

	// Display puzzle and give each player turns.  Advance to next
	// player if they guess a missing letter, spin a BANKRUPT or
	// spin a LOSE TURN.  Stop when all letters in puzzle are revealed.
	
	cout << "Disk of Fortune!" << endl;
	while (true)
	{
		// Wrap around from last to first player (if necessary).
		currPlayer %= NUM_PLAYERS;

		// Display current (one-based) player # with their money.
		cout << "\nPlayer #" << (currPlayer + 1)
			<< ": $" << prizeMoney[currPlayer] << endl;

		// Display current puzzle (some parts may be revealed based on
		// previous turns).
		puzzle.display();

		// Generate a random spin of the disk.
		int spin = rand() % NUM_ITEMS;
		string item = ITEMS[spin];
		cout << "\nSpin: "
			<< (isdigit(item[0]) ? "$" : "")  // "$" if monetary amount
			<< item << endl;

		// Process result of spin.

		if (item == "BANKRUPT")
		{
			cout << "Sorry, you lost your money!" << endl;
			prizeMoney[currPlayer] = 0;
			currPlayer++;
		}
		else if (item == "LOSE TURN")
		{
			cout << "Sorry, you lost your turn!" << endl;
			currPlayer++;
		}
		else
		{
			// Allow user to guess a letter.
			cout << "Guess a letter: ";
			char letter;
			cin >> letter;
			if (isLetterAlreadyGuessed(guessedLetters, letter) == true) {
				cout << "\nLetter '" << letter << "' is already guessed.\nYou losed you turn." << endl;
				currPlayer++;
				continue;
			}
			else {
				// Count how many of that letter found in puzzle.
				int numFound = findLetter(puzzle, letter);

				if (numFound == 0)
				{
					cout << "Sorry, there is no '" << letter << "'" << endl;
					currPlayer++;
				}
				else
				{
					// Give player amount of money spun for each such letter in puzzle.
					guessedLetters.insert(letter);
					int spinMoney = stoi(item);  // string => int (e.g., "450" => 450)
					prizeMoney[currPlayer] += numFound * spinMoney;
				}
			}
		}
		if (solved(puzzle) == true) { //Break loop if puzzle is solved
			break;
		}
	}
	cout << "----Game Over----\n";
	for (int i = 0; i < NUM_PLAYERS; i++) {
		cout << "Player " << (i + 1) << " won " << prizeMoney[i] << "$\n";
	}
	return 0;
}

// Definitions for functions that help game proceed.
// Show any punctuation (non-letters) in puzzle.
// Returns copy of puzzle with punctuation revealed.
ObscuredEntries<char> showPunct(ObscuredEntries<char> puzzle) {
	char entry;
	for (int i = 0; i < puzzle.getNumRows(); i++) {
		for (int j = 0; j < puzzle.getNumCols(i); j++) {
			entry = puzzle.getEntry(i, j);
			if ((entry >= 'a' && entry <= 'z') || (entry >= 'A' && entry <= 'Z')) {
				continue;
			}
			else {
				puzzle.unhide(i, j);
			}
		}
	}
	return puzzle;
}

// Show a letter (passed) that user guessed in puzzle.
// Return a count of how many of such letter found.
int findLetter(ObscuredEntries<char>& puzzle, char letter) {
	int count = 0;
	for (int i = 0; i < puzzle.getNumRows(); i++) {
		for (int j = 0; j < puzzle.getNumCols(i); j++) {
			if (puzzle.getEntry(i, j) == letter) {
				puzzle.unhide(i, j);
				count = count + 1;
			}
		}
	}
	return count;
}

// Return whether puzzle is solved (all letters revealed).
bool solved(const ObscuredEntries<char>& puzzle) {
	for (int i = 0; i < puzzle.getNumRows(); i++) {
		for (int j = 0; j < puzzle.getNumCols(i); j++) {
			if (puzzle.isHidden(i, j) == true) {
				return false;
			}
		}
		cout << endl;
	}
	return true;
}

//Tell whether the letter is already guessed by player or not.
bool isLetterAlreadyGuessed(set<char> guessedLetters, char letter) {
	for (auto ch = guessedLetters.begin(); ch != guessedLetters.end(); ch++) {
		if (*ch == letter) {
			return true;
		}
	}
	return false;
}
