//
//  main.cpp
//  BullcowGame
//
//  Created by Nicco on 11/10/2016.
//  Copyright © 2016 Nicco. All rights reserved.
//

/* This is the console executable, hat makes use of the BullCow class
 This acts as the view in a MVC pattern, and is responsible for all
 user interaction. For game logic see the FBullCowGame class.
 */

#include <iostream> // "pre processor" directive.
#include <string>
#include "FBullCowGame.hpp"
using FText = std::string;
using int32 = int; //using UNREAL int32 notation.

//using namespace std; // "name spaces"
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //instantiate a new game - defining a new game called BCGame


int main(int32 argc, const char * argv[]) {

    // Do - While loop
    bool bPlayAgain = false;
    do
    {
        BCGame.Reset();
        PrintIntro(); // form of abstraction
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    } while(bPlayAgain);
    return 0;
    //TODO: Hello world
}



// --------------------
// form of encapsulation
// --------------------

// Introduce the game
void PrintIntro(){
    std::cout << ("\n\nHELLO\n");
    std::cout << ("This is using namespace identifiers\n");
    std::cout << ("Welcome to Bull and Cows a Fun Game\n");
    std::cout << "Can you guess the "<< BCGame.GetHiddenWordLength() <<" letter isogram I'm thinking of?\n";
    return;
}

void PlayGame(){
    int32 MaxTries = BCGame.GetMaxTries();
    std::cout << MaxTries << std::endl;
    //BCGame() = FBullCowGame();
    // loop for the number of turns asking for entries
    //constexpr int NUMBER_OF_TURNS = 5;
    
    //TODO: Change from For to a While loop once we are validating tries

    while (BCGame.IsGameWon()==false && BCGame.GetCurrentTry() <= MaxTries) {
        //std::cout<< "Status of Game is : " <<BCGame.IsGameWon() << "\n\n";
        //for (int32 count = 1; count <= MaxTries; count++) {
            FText Guess = GetValidGuess();
            
            //TODO: Make check for valid guesses.
            // Submit valid guess to the game
            FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
            // Print number of bulls and cows
            std::cout << "Bulls = " << BullCowCount.Bulls << " \n";
            std::cout << "Cows = " << BullCowCount.Cows  << " \n";
            std::cout << "You entered >> " << Guess << " <<, thank you, let me check.\n";
            std::cout << std::endl;
            //std::cout<< "Status of Game is : inside FOR Loop " <<BCGame.IsGameWon() << "\n\n";
    }
    PrintGameSummary();
    return; //TODO: HELLO
}

// Get a guess from the player
FText GetValidGuess()
{
    EGuessStatus Status = EGuessStatus::Invalid;
    do
    {
        int32 CurrentTry = BCGame.GetCurrentTry();
        std::cout << "Try "<< CurrentTry << ": Enter your guess here: ";
        FText GetGuessVal="";
        std::getline(std::cin, GetGuessVal);
        //CurrentTry++;
        
        Status = BCGame.CheckGuessValidity(GetGuessVal);
        switch (Status)
        {
            case EGuessStatus::Wrong_Length:
                std::cout << "please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "please enter a word without repeating letters.\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "please enter a word in lower case.\n";
                break;
            default:
                return GetGuessVal;
        }

    } while (Status != EGuessStatus::OK); //Keep looping until we get a valid entry
    return 0;
}

bool AskToPlayAgain(){
    std::cout << "Do you want to play again ? ";
    FText Response = "";
    std::getline(std::cin, Response);
    return (toupper(Response[0])=='Y'); //get every value into UPPERCASE and compare it to a single output
    /*if (toupper(Response[0])=='Y') {
        std::cout << "YES";
        PlayGame();
        return 1;
    } else {
        return 0;
    }*/
}

void PrintGameSummary(){
    if (BCGame.IsGameWon()){
        std::cout << "Well Done - YOU WIN!\n";
    }
    else{
        std::cout << "Better luck next time !\n";
    }
}