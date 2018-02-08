#include "stdafx.h"
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTries() const { return myCurrentTries; }
int32 FBullCowGame::GetHiddenWordLength() const { return myHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }
bool FBullCowGame::IsIsogram(FString guess) const
{
	if (guess.length() <= 1) { return true; }

	TMap<char, bool>Letterseen;
	for (auto Letter : guess)
	{
		Letter = tolower(Letter);
		if (Letterseen[Letter] != true) { Letterseen[Letter] = true; }
		else { return false; }
	}
	return true;
}

bool FBullCowGame::IsLowerCase(FString guess) const
{
	for (auto Letter : guess)
	{
		if (!islower(Letter)) { return false; }
	}
	return true;
}

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap <int32, int32> WordLengthToMaxTries{ {3,5} , {4,5}, {5,5}, {6,5} };
	return WordLengthToMaxTries[myHiddenWord.length()]; 
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "bonie";
	constexpr int32 MAX_TRIES = 8;
	myHiddenWord = HIDDEN_WORD;
	myCurrentTries = 1;
	bGameWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) const
{	
	if (!IsIsogram(guess)) {
		return EGuessStatus::NOT_Isogram;
	}
	else if (!IsLowerCase(guess)) {
		return EGuessStatus::Not_Lowercase;
	}
	else if (guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Length;
	}
	else { return EGuessStatus::OK; }
}

FBullCowCount FBullCowGame::SubmitGuess(FString guess)
{
	myCurrentTries++;
	FBullCowCount bullCowCount;

	int32 wordLength = myHiddenWord.length();
	for (int32 i = 0; i < wordLength; i++)
	{ 
		for (int32 j = 0; j < wordLength; j++)
		{	
			if (guess[i] == myHiddenWord[j]) 
			{
				if (i == j) { bullCowCount.bulls++; }
				else { bullCowCount.cows++; }
			}
		}
	}
	
	if (bullCowCount.bulls == wordLength) { bGameWon = true; }
	else { bGameWon = false; }
	return bullCowCount;
}
