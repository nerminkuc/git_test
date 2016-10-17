//
//  FBullCowGame.hpp
//  BullcowGame
//
//  Created by Nicco on 13/10/2016.
//  Copyright © 2016 Nicco. All rights reserved.
//

#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <stdio.h>
#include <string>
using FString = std::string;
using int32 = int;
#pragma once

struct FBullCowCount{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus{ // this is a strongly define Enumeration so we can share enumerations
    Invalid,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

class FBullCowGame{
public:
    FBullCowGame(); // constructor
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    int32 GetGuessWordLenth();
    bool IsGameWon() const;
    
    void Reset();
    EGuessStatus CheckGuessValidity(FString);
    FBullCowCount SubmitGuess(FString);
    
// Please try and ignore this focus on interface above
private:
    // see constructor for initialisation - only at compile time
    int32 MyCurrentTry;
    int32 MyMaxTries;
    FString MyHiddenWord;
    bool bGameIsWon;
    
    bool IsIsogram(FString) const;
    bool IsLowercase(FString) const;
};

#endif /* FBullCowGame_hpp */
