//
//  FBullCowGame.cpp
//  BullcowGame
//
//  Created by Nicco on 13/10/2016.
//  Copyright © 2016 Nicco. All rights reserved.
//

#include "FBullCowGame.hpp"
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;


FBullCowGame:: FBullCowGame(){
    Reset(); //Call the Rest
}

int FBullCowGame::GetMaxTries() const {return MyMaxTries;}
int FBullCowGame::GetCurrentTry() const { return MyCurrentTry;}
bool FBullCowGame::IsGameWon() const {return bGameIsWon;}


void FBullCowGame::Reset(){
    constexpr int MAX_TRIES = 8;
    MyMaxTries=MAX_TRIES;

    const FString HIDEN_WORD = "rocking";
    MyHiddenWord = HIDEN_WORD;
    
    MyCurrentTry=1;
    bGameIsWon=false;
    return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess){
    if (!IsIsogram(Guess))
    {
        return EGuessStatus::Not_Isogram;
    }else if (!IsLowercase(Guess))
    {
        return EGuessStatus::Not_Lowercase;
    }else if (Guess.length() != GetHiddenWordLength())
    {
        return EGuessStatus::Wrong_Length;
    }else
    {
        return EGuessStatus::OK;
    }
}

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length();}

//recieves a valid guess and increments turn and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
    // increment the turn number
    MyCurrentTry++;
    FBullCowCount BullCowCount;
    int32 WordLength = MyHiddenWord.length();
    
    // loop through all letters in the hidden word
    for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
    {
        // compare letters against the guess
        for (int32 GChar = 0; GChar < WordLength; GChar++)
        {
            if (Guess[GChar] == MyHiddenWord[MHWChar])
            {
                if (MHWChar==GChar)
                {
                    BullCowCount.Bulls++;
                }
                else
                {
                    BullCowCount.Cows++;
                }
            }
        }
    }
    if (BullCowCount.Bulls == WordLength){
        bGameIsWon=true;
        //std::cout << "BULLS " << BullCowCount.Bulls;
    }
    else {
        bGameIsWon=false;
        //std::cout << "COWS " << BullCowCount.Cows;
    }
    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
    // treat 0 and 1 letter words as isograms
    if (Word.length() <2) {return true;}
    
    TMap<char, bool> LetterSeen;    // setup our map
    for (auto Letter : Word)        //for all letters of the word
    {
        Letter = tolower(Letter);
        if (LetterSeen[Letter]) {
            return false;
        } else {
            LetterSeen[Letter] = true;
        }// we do not have an isogram
        // setup our map
        // loop through all the letters of the word
         // if the letter is in the map
           // we do NOT have an isogram
         // otherwise
          // add the letter to the map as seen
        
    }
    
    return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase (FString Word) const
{
    for (auto Letter : Word)
    {
        if (!islower(Letter))
        {
            return false;
        }// if not a lowercase letter
    }
    return true;
}