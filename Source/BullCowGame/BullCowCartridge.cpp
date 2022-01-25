// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();                // Setting Up Game

    for (int32 Index = 0; Index < 5; Index++)
    {
        PrintLine(TEXT("%s"), *Words[Index]);
    }


    PrintLine(FString::Printf(TEXT("The HiddenWord is: %s"), *HiddenWord));// Debug Line
    PrintLine(FString::Printf(TEXT("Lives remaining: %i"), Lives));// Debug Line
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else //Checking PlayerGuess
    {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame()
{
    // Welcoming the Player
    PrintLine(TEXT("Welcome to Bull Cows!"));

	HiddenWord = TEXT("cakes");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives"), Lives);
    PrintLine(TEXT("Type in your guess and \nPress enter to continue...")); // Prompt Player for Guess

}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;

    PrintLine(TEXT("\nPress enter to play again."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You have Won!"));
        PrintLine(TEXT("You guessed the correct Hidden Word %s!"), *HiddenWord);
        EndGame();
        return;
    }

    if  (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The Hidden word is %i letters long"), HiddenWord.Len());
        PrintLine(TEXT("Sorry, try guessing again! \nYou have %i lives remaining."), Lives);

        return;
    }

    //Check if Isogram
    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters, guess again!"));
        return;
    }

    // Remove Life
    PrintLine(TEXT("Lost a life!"));
    --Lives;
    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
        EndGame();
        return;
    }
    // Show the player Bulls and Cows
    PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }

    return true;


    // int32 Index = 0;
    // int32 Comparison = Index + 1;

    // for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
    // {
    //     if (Word[Index] == Word[Comparison])
    //     {
    //         return false;
    //     }
    // }


    // For each letter
    // Start at element [0].
    // Comparison against the next letter.
    // Until we reach [Word.Len() - 1].
    // If nay are the same return false.

}