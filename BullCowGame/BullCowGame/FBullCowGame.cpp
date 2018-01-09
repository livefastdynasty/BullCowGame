#pragma once
#include "FBullCowGame.h"
#include <map>

//to make syntax more unreal friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{
	
	const FString HIDDEN_WORD = "planet"; //this must be an isogram
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

//recieves a valid guess, increments turn, and returns count 
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess
	// loop through all letters in the hidden word
	
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// compare letters against the guess word
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			//if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) 
			{
				if (MHWChar == GChar) ////if they're in the same place
				{
					BullCowCount.Bulls++; //increment bulls
				}
				else 
				{
					BullCowCount.Cows++; // increment cows
				}
			}		
		}

		if (BullCowCount.Bulls == WordLength)
		{
			bGameIsWon = true;
		}
		else 
		{
			bGameIsWon = false;
		}
	}
		
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1)
	{
		return true;
	}
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) //for all letters of the word
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])
		{
			return false; //we do not have an isogram
		}
		else
		{
			LetterSeen[Letter] = true;
		}
		//loop through all the letters of the word
		//if the letter is in the map
			//we do not have an isogram
		// otherwise
			//add the letter to the map as seen
	}

	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
		// if not a lowercase letter
			// return false
	}
	return true; //otherwise return true
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap <int32, int32> WordLengthToMaxTries{ {3, 4}, {4, 7}, {5, 10}, {6, 15}, {7, 20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}



bool FBullCowGame::IsGameWon() const
{

	return bGameIsWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{ 
	if (!IsIsogram(Guess)) //If the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess)) // if the guess isn't all lowercase 
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) //if guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
	
}
