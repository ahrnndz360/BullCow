/*
Console executable that makes use of the BullCow class

This acts as the view in a MVC pattern, and is repsonbile for
user interaction. For game logic see the FBullCowGame class
*/

#include "stdafx.h"
#include "FBullCowGame.h"

using namespace std;
using int32 = int;
using Ftext = std::string;
FBullCowGame game;

void PrintIntro() 
{
	cout << "Welcome to Bulls and Cow!\n";
	cout << "Try to guess the " << game.GetHiddenWordLength() << " letter isogram\n\n";
	return;
}

void PrintGameSummary() {
	if (game.IsGameWon()) { cout << "Congrats! You've WON!\n"; }
	else { cout << "Sorry, better luck next time!\n"; }
};

Ftext GetValidGuess() 
{
	Ftext guess = "";
	EGuessStatus status = EGuessStatus::Invalid_Status;
	do {
		cout << "Enter your guess: ";
		getline(cin, guess);

	   status = game.CheckGuessValidity(guess);
		switch (status)
		{
		case EGuessStatus::Wrong_Length:
			cout << "Guess is incorrect length. Please enter a " << game.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::NOT_Isogram:
			cout << "Guess is not an Isogram. Please try again.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			cout << "Guess is not all lowercase. Please try again.\n";
			break;

		default:
			break;
		}
		
	} while (status != EGuessStatus::OK);

	return guess;
}

void PlayGame() 
{
	game.Reset();
	int32 maxTries = game.GetMaxTries();
	while(!game.IsGameWon() && game.GetCurrentTries() <= game.GetMaxTries())
	{
		cout << "Guess: " << game.GetCurrentTries() << " out of " << maxTries << ".\n";
		Ftext guess = GetValidGuess(); //TODO validate guesses from users
		FBullCowCount bullCowCount = game.SubmitGuess(guess);
		cout << "Bulls: " << bullCowCount.bulls << " Cows: " << bullCowCount.cows << "\n\n";

	}
	PrintGameSummary();

	return;
}

bool AskPlayAgain() 
{
	cout << "Do you want to play again? (y/n)\n";
	Ftext response = "";
	getline(cin, response);
	
	return (response[0] == 'y' || response[0] == 'Y');
};

int main() 
{
	do
	{
		PrintIntro();
		PlayGame();
	} while (AskPlayAgain());
	return 0;
}