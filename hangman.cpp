/*
hangman.cpp by Dan Poumakis
10/22/2015
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

void gameMenu();
void displayHelp();
void getChoiceFromUser(int*);
void printChoiceMenu();
void playGame();
void selectWordFromFile(string&);
void initializeDisplayedWord(string&, string);
void displayWelcomeMessage();
void displayWord(string);
void displayHangMan(int);
void getGuess(char*, string*, int*);
bool guessIsValid(char, string);
void displayLettersGuessed(string);
void checkForGuessInWord(char, string, int*, string&);
void checkIfUserWins(string, string, bool&);
void checkNumberOfWrongGuesses(int, bool&);
void checkNumberOfGuesses(int, string, bool&, string);
void checkIfGameOver(bool, string);
bool guessInWord(char, string);
void clearOutput();
string updateDisplayedWord(string, string, char);

int main()
{
	// Go to game menu
	gameMenu();

	// Progam is complete, no errors
	return 0;
}

void gameMenu()
{
	// Variable to store users choice
	int choice;
	// Variable to loop menu until user quits
	bool keepPlaying = true;
	do
	{
		// Prompt user for choice, verify it, and store it
		getChoiceFromUser(&choice);
		switch (choice)
		{
			case 1:
				// Play Game
				playGame();
				keepPlaying = true;
				break;
			case 2:
				// Display Help
				displayHelp();
				keepPlaying = true;
				break;
			case 3:
				// Quit
				cout << "Goodbye!" << endl;
				keepPlaying = false;
				break;
		}
	} while (keepPlaying);
}

/*
Print a how to play menu for user
*/
void displayHelp()
{
	cout << "How to play Dan's Hangman:" << endl;
	cout << "First, enter a guess." << endl;
	cout << "The computer will evaluate each guess." << endl; 
	cout << "The computer will reveal your guess if its correct." << endl;
	cout << "Guess incorrectly, piece of the \"hanged man\" will be added." << endl;
	cout << "You have 6 lives and total number of letters in the word + 2 guesses." << endl;
	cout << "Happy guessing :)" << endl;
}

/*
Get choice from user
*/
void getChoiceFromUser(int* choice)
{
	// Flag to verify valid choice
	bool validChoice = true;
	do
	{
		// User entered invalid choice
		if (!validChoice)
		{
			cout << "Choice is not valid." << endl;
		}
		// Display choice menu and store choice
		printChoiceMenu();
		// This while loop will verify input is an int
		while(!(cin >> *choice))
		{
			// User didn't enter an int, clear the cin
	        cin.clear();
	        // Ignore everything till a new input
	       	cin.ignore(10000,'\n');
	       	// Tell user input was invalid
	       	cout << "Input invalid. Enter again: ";
	    }
		// Verify choice
		if (*choice == 1 || *choice == 2 || *choice == 3)
		{
			validChoice = true; 
		}
		else
		{
			validChoice = false;
		}
	} while (!validChoice);
}

/*
Display choices to user
*/
void printChoiceMenu()
{
	// Send new lines to make it easier to read
	cout << endl << endl;

	cout << "Hangman! by Dan Poumakis" << endl;
	cout << "Enter one of the following choices:" << endl;
	cout << "1.) Play the game." << endl;
	cout << "2.) Display how to play." << endl;
	cout << "3.) Quit." << endl;
	cout << "Enter choice: ";
}

/*
Main game function
Designed this function to not need comments
Each function call is well-documented as well
*/
void playGame()
{
	char guess;
	bool notGameOver = true;
	int numberOfWrongGuesses = 0;
	int numberOfGuesses = 0;
	string word;
	string displayedWord = "";
	string lettersGuessed = "";
	string wrongLetters = "";
	
	selectWordFromFile(word);
	initializeDisplayedWord(displayedWord, word);
	displayWelcomeMessage();
	while (notGameOver)
	{
		displayWord(displayedWord);
		getGuess(&guess, &lettersGuessed, &numberOfGuesses);
		checkForGuessInWord(guess, word, &numberOfWrongGuesses, displayedWord);
		checkIfUserWins(displayedWord, word, notGameOver);
		clearOutput();
		displayHangMan(numberOfWrongGuesses);
		displayLettersGuessed(lettersGuessed);
		checkNumberOfWrongGuesses(numberOfWrongGuesses, notGameOver);
		checkNumberOfGuesses(numberOfGuesses, word, notGameOver, displayedWord);
		checkIfGameOver(notGameOver, word);
	}
}

/*
Use input file stream to select word from text file
*/
void selectWordFromFile(string& word)
{
	// Initialize ifstream
	ifstream words;
	// Open text file
	words.open("words.txt");
	// Set seed
	srand(time(0));
	// Loop till random number
	for (int i = 0; i < rand() % 10; i++)
	{
		// Grab word
		words >> word;
	}
	// Close ifstream
	words.close();
}

/*
Initialize a display word by turning a blank string to same length of word with '_' chars
*/
void initializeDisplayedWord(string& displayedWord, string word)
{
	// Loop length of word
	for (int i = 0; i < word.length(); i++)
	{
		// Add '_' to display word
		displayedWord += "_";
	}
}

/*
Welcome message for user
*/
void displayWelcomeMessage()
{
	cout << "Welcome to Dan's Hangman game!" << endl;	
}

/*
Output the underscore word to user, seperated by spaces for neatness
*/
void displayWord(string displayedWord)
{
	// Loop length of word
	for (int i = 0; i < displayedWord.length(); i++)
	{
		// Output char with space
		cout << displayedWord[i] << " ";
	}
	// End line for neatness
	cout << endl;
}

/*
Prompt the user for a guess, verify it, and store it
*/
void getGuess(char* guess, string* lettersGuessed, int* numberOfGuesses)
{
	do
	{
		// Flag for verify input is a letter
		bool isLetter = true;
		do
		{
			// User didn't enter a letter
			if(!isLetter)
			{
				cout << "Not a letter." << endl;
			}
			// Prompt user for guess and store it
			cout << "Enter a guess (letter): ";
			cin >> *guess;
			// Convert guess to lowercase
			*guess = tolower(*guess);
			// If letter set flag true, else flag is false
			if (islower(*guess) || isupper(*guess))
			{
				isLetter = true;
			}
			else
			{
				isLetter = false;
			}
		} while (!isLetter);
		// Letter has been guesses already
		if (!guessIsValid(*guess, *lettersGuessed))
		{
			cout << "You already guessed that letter." << endl;
		}
	} while (!guessIsValid(*guess, *lettersGuessed)); // Keep loop till valid letter that hasn't been guesses
	// Add valid guess to lettersGuessed and increment number of guesses
	if (guessIsValid(*guess, *lettersGuessed))
	{
		*lettersGuessed += *guess;	
		*numberOfGuesses += 1;
	}
}

/*
Check to see if guess is valid but search for it in letters that have been already guessed
*/
bool guessIsValid(char guess, string lettersGuessed)
{
	// Flag for valid guess
	bool guessIsValid = true;

	// Loop through each letter guessed
	for (int i = 0; i < lettersGuessed.length(); i++)
	{
		// If guess has been guessed... Set flag to false
		if (lettersGuessed[i] == guess)
		{
			guessIsValid = false;
		}
	}
	// Return flag
	return guessIsValid;
}

/*
Display letters that have been guessed already so user has an idea of what to guess next
*/
void displayLettersGuessed(string lettersGuessed)
{
	// Sort the letters guessed alphabetically, for neatness
	for (int i = 0; i < lettersGuessed.length(); i++)
	{
		for (int j = 0; j < lettersGuessed.length(); j++)
		{
			if (lettersGuessed[i] < lettersGuessed[j])
			{
				int temp = lettersGuessed[i];
				lettersGuessed[i] = lettersGuessed[j];
				lettersGuessed[j] = temp;
			}
		}
	}
	// Display letters guessed to users
	cout << "Letters guessed: " << lettersGuessed << endl;
}

/*
Take guess from user, compare it to each char of word, if it matches... Reveal char in the display word
*/
string updateDisplayedWord(string displayedWord, string word, char guess)
{
	// Loop through each char of word
	for (int i = 0; i < word.length(); i++)
	{
		// If char == guess
		if (word[i] == guess)
		{
			// Reveal char on display
			displayedWord[i] = word[i];
		}
	}
	// Return display word
	return displayedWord;
}

/*
Take guess and check if its in the word
*/
void checkForGuessInWord(char guess, string word, int* numberOfWrongGuesses, string& displayedWord)
{
	// If guess is in the word... Update the display word for user 
	if (guessInWord(guess, word))
	{
		displayedWord = updateDisplayedWord(displayedWord, word, guess);
	}
	else // Increment wrong guesses
	{
		*numberOfWrongGuesses += 1;
	}
}

/*
Checks for char in string
*/
bool guessInWord(char guess, string word)
{
	// Flag for guess being in word
	bool validGuess = false;

	// Loop through each element of word
	for (int i = 0; i < word.length(); i++)
	{
		// Letter found, set flag to true
		if (word[i] == guess)
		{
			validGuess = true;
		}
	}

	// Return flag
	return validGuess;
}

/*
Check if the display word is completly reveal by comparing it to word
*/
void checkIfUserWins(string displayedWord, string word, bool& notGameOver)
{
	// Display word matches word, user wins. Set game over
	if (displayedWord == word)
	{
		cout << "You win!" << endl;
		notGameOver = false;
	}
}

/*
Check if user has guessed incorrectly too many times
*/
void checkNumberOfWrongGuesses(int numberOfWrongGuesses, bool& notGameOver)
{
	// If gameOver flag isn't set by checkIfUserWins...
	if (notGameOver)
	{
		// Check if num of guesses wrong is lessthan= 6, if so game over
		if (numberOfWrongGuesses >= 6)
		{
			cout << "You guessed incorrectly too many times." << endl;
			notGameOver = false;
		}
	}
	
}

/*
Check if user has reached number of guesses (length of word + 2)
*/
void checkNumberOfGuesses(int numberOfGuesses, string word, bool& notGameOver, string displayedWord)
{
	// If gameOVer flag isn't set by checkIfUserWins nor checkNumberOfWrongGuesses...
	if (notGameOver)
	{
		// Check if num of total gueses lessthan= length of word + 2, if so game over and prompt for final guess
		if (numberOfGuesses >= (word.length() + 2))
		{
			// Variable to store final guess
			string finalGuess;
			// Tell user they ran outta guesses
			cout << "You ran out of guesses!" << endl;
			// Display underscore word for final time
			displayWord(displayedWord);
			// Cut off an remaining char in cin 
			cin.ignore(10000,'\n');
			// Prompt for and store finalGuess
			cout << "Guess the word: ";
			cin >> finalGuess;
			// If guess == word, you win! else you lose... 
			if (finalGuess == word)
			{
				cout << "You got it right, you win!";
			}
			else
			{
				cout << "Incorect.";
			}
			cout << endl; // neatness
			notGameOver = false; // game over
		}
	}
}

/*
If not game over flag is set to false, print the word and print thank you message
*/
void checkIfGameOver(bool notGameOver, string word)
{
	if (!notGameOver)
	{
		cout << "The word was: " << word << endl;
		cout << "Thanks for playing." << endl;
	}
}

/*
Clear output by sending 50 new lines, for neatness
*/
void clearOutput()
{
	for (int i = 0; i < 50; i++)
	{
		cout << endl;
	}
}

/*
Display the hangman based on number of wrong guesses
*/
void displayHangMan(int numberOfWrongGuesses)
{
	switch (numberOfWrongGuesses)
	{
		case 0:
			cout << "   +---+" << endl;
			cout <<	"   |   |" << endl;
			cout <<	"       |" << endl;
			cout <<	"       |" << endl;
			cout <<	"       |" << endl;
			cout <<	"       |" << endl;
			cout <<	"========="<< endl;
			break;
		case 1:
			cout << "   +---+" << endl;
			cout <<	"   |   |" << endl;
			cout <<	"   O   |" << endl;
			cout <<	"       |" << endl;
			cout <<	"       |" << endl;
			cout <<	"       |" << endl;
			cout <<	"========="<< endl;
			break;
		case 2:
			cout << "   +---+" << endl;
			cout <<	"   |   |" << endl;
			cout <<	"   O   |" << endl;
			cout <<	"   |   |" << endl;
			cout <<	"       |" << endl;
			cout <<	"       |" << endl;
			cout <<	"========="<< endl;
			break;
		case 3:
			cout << "   +---+" << endl;
			cout <<	"   |   |" << endl;
			cout <<	"   O   |" << endl;
			cout <<	"   |\\  |" << endl;
			cout <<	"       |" << endl;
			cout <<	"       |" << endl;
			cout <<	"========="<< endl;
			break;
		case 4:
			cout << "   +---+" << endl;
			cout <<	"   |   |" << endl;
			cout <<	"   O   |" << endl;
		    cout <<	"  /|\\  |" << endl;
			cout <<	"       |" << endl;
			cout <<	"       |" << endl;
			cout <<	"========="<< endl;
			break;
		case 5:
			cout << "   +---+" << endl;
			cout <<	"   |   |" << endl;
			cout <<	"   O   |" << endl;
		    cout <<	"  /|\\  |" << endl;
			cout <<	"  /    |" << endl;
			cout <<	"       |" << endl;
			cout <<	"========="<< endl;
			break;
		case 6:
			cout << "   +---+" << endl;
			cout <<	"   |   |" << endl;
			cout <<	"   O   |" << endl;
		    cout <<	"  /|\\  |" << endl;
			cout <<	"  / \\  |" << endl;
			cout <<	"       |" << endl;
			cout <<	"========="<< endl;
			break;
	}
}