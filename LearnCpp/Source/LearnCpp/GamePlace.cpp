// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlace.h"
#include "Asteroid.h"
#include "Engine/World.h"

// Sets default values
AGamePlace::AGamePlace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpawnDuring = 3.0f;

	//NEVER GetWorld() when awake the object, REMEMBER!
	//>>>>>>>>>>>>>>>>>>>>>>>createCD = GetWorld()->GetTimeSeconds();
	createCD = SpawnDuring;
	
}

// Called when the game starts or when spawned
void AGamePlace::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGamePlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CreateAsteroid();
	createCD -= DeltaTime;
}

void AGamePlace::CreateAsteroid() {
	if (createCD <= 0) {
		createCD += SpawnDuring;
		if (Asteroid) {
			FActorSpawnParameters param;
			float x = 0;
			float y = 0;
			if (rand() % 2 == 0) {
				x = rand() % 7200 - 3600;
				y = 2000 + 100;
			}
			else {
				x = 3600 + 100;
				y = rand() % 4000 - 2000;
			}
			AAsteroid* theAsteroid = GetWorld()->SpawnActor<AAsteroid>(Asteroid, FVector(x,y,0), FRotator::ZeroRotator, param);
			theAsteroid->SetSizeLevle(rand()%3+1);
		}
	}
}

