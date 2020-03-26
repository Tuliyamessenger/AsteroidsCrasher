// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "LearnCppGameModeBase.h"
//#include "UObject/ConstructorHelpers.h"
//#include "Blueprint/UserWidget.h"

ALearnCppGameModeBase::ALearnCppGameModeBase() {
	score = 0;
	chance = 2;

	/*
	ConstructorHelpers::FClassFinder<UUserWidget> MenuClassFinder(TEXT("/Game/BluePrint/Pause"));
	PauseMenu = MenuClassFinder.Class;
	UMainMenu* Menu = CreateWidget<UMainMenu>(this, PauseMenu);
	*/
}

FString ALearnCppGameModeBase::GetScore() {
	return FString("Score: " + FString::FromInt(score));
}

FString ALearnCppGameModeBase::GetScore_fin() {
	return FString(FString::FromInt(score) + " Points");
}

int ALearnCppGameModeBase::GetChance() {
	return chance;
}

void ALearnCppGameModeBase::ReduceChance() {
	chance -= 1;
}

void ALearnCppGameModeBase::IncreaseScore() {
	//UE_LOG(LogTemp,Warning,TEXT("asdfsdaf"));
	score += 1;
}
