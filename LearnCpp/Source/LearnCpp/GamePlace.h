// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GamePlace.generated.h"

class AAsteroid;

UCLASS()
class LEARNCPP_API AGamePlace : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGamePlace();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//========================================
	//				Default Data
	//========================================
	//---------- Property ---------
	
	UPROPERTY(EditAnywhere, Category = "Asteroid")
		TSubclassOf<AAsteroid> Asteroid;
	UPROPERTY(EditAnywhere, Category = "Asteriod")
		float SpawnDuring;

	float createCD;
	//----------- Function -----------
	void CreateAsteroid();
	
	//=====
	//==========================================
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
