// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LearnCppGameModeBase.generated.h"


/**
 * 
 */
UCLASS()
class LEARNCPP_API ALearnCppGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	ALearnCppGameModeBase();

	UPROPERTY(BlueprintReadOnly)
		int score;
	UPROPERTY(BlueprintReadOnly)
		int chance;

	//TSubclassOf<class UUserWidget> PauseMenu;

public:
	UFUNCTION(BlueprintPure, Category = "PlayerData")
		FString GetScore();
	UFUNCTION(BlueprintPure, Category = "PlayerData")
		FString GetScore_fin();
	UFUNCTION(BlueprintPure, Category = "PlayerData")
		int GetChance();

	void ReduceChance();

	void IncreaseScore();
};
