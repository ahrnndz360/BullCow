#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount 
{
	int32 bulls = 0;
	int32 cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	NOT_Isogram,
	Not_Lowercase,
	Wrong_Length
};

class FBullCowGame {
public:
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTries() const;
	int32 GetHiddenWordLength() const;
	EGuessStatus CheckGuessValidity(FString guess) const;
	bool IsGameWon() const;

	void Reset(); //TODO make a richer return value 
	FBullCowCount SubmitGuess(FString guess);

private:
	int32 myCurrentTries;
	FString myHiddenWord;
	bool bGameWon;

	bool IsIsogram(FString guess) const;
	bool IsLowerCase(FString guess) const;
};