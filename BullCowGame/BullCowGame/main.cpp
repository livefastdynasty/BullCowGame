/*
This is the console excutable, that makes use of the BullCow class
This acts as the view in the MVC pattern, and is responsible for all
user interaction. For game logic see
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"


// to make syntax unreal friendly

using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game, which we re-use across plays

// the entry proint of our application
int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
		
	} 
	while (bPlayAgain);
	return 0; //exit the game
}

void PrintIntro()
{
	std::cout << "Welcome to Cows and Bulls, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

//plays a single game to completion 
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << "Your Max Tries: " << MaxTries << std::endl;

	// loop asking for guesses while the game hasn't been won
	//and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <=MaxTries)
	{
		FText Guess = GetValidGuess(); 
		
		//submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

	
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
		
		std::cout << std::endl;
	}
	PrintGameSummary();
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess()

{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
	// get a guess from the player
	int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Current Try " << CurrentTry <<  " of " << BCGame.GetMaxTries() << std::endl;

		std::cout << "Enter your guess: ";
		
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
			{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;

		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without any repeating letters.\n\n";
			break;

		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a word in all lowercase letters.\n\n";
			break;

		default:
			//assuming the guess is valid
			break;
			}
		

	} while (Status != EGuessStatus::OK); //keep looping until we get no erros
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Well done, you win!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}
