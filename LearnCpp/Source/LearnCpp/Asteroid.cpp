// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "LearnCppGameModeBase.h"
#include "Particles/particleSystem.h"
#include "Sound/SoundWave.h"

// Sets default values
AAsteroid::AAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = Collider = CreateDefaultSubobject<USphereComponent>("Collider");
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	FVector volocity = FVector(rand() % 101 - 50, rand() % 101 - 50, 0);
	volocity.Normalize();
	speed = volocity * (rand() % 18 + 3);
	rotateSpeed = FRotator(rand() % 101 - 50, rand() % 101 - 50, rand() % 101 - 50) * 0.02f;
}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();
	gameMode = Cast<ALearnCppGameModeBase>(UGameplayStatics::GetGameMode(this));
}

// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Movement();
}

//=============================================
//					Fuction
//=============================================

void AAsteroid::Movement() {
	FVector position = GetActorLocation();
	if ((position.X < -3600 && speed.X < 0) || (position.X > 3600 && speed.X > 0)) position.X = -position.X;
	if ((position.Y < -2000 && speed.Y < 0) || (position.Y > 2000 && speed.Y > 0)) position.Y = -position.Y;
	SetActorLocation(position + speed);

	SetActorRotation(GetActorRotation() + rotateSpeed);
}

void AAsteroid::BeHit() {
	if(gameMode) gameMode -> IncreaseScore();
	if(Explode) UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explode, GetActorLocation(),FRotator::ZeroRotator, true);
	if(Explode_Sound) UGameplayStatics::PlaySoundAtLocation(this, Explode_Sound, GetActorLocation());
	if (sizeLevel > 1) {
		SetSizeLevle(sizeLevel - 1);
		FVector volocity = FVector(rand() % 101 - 50, rand() % 101 - 50, 0);
		volocity.Normalize();
		speed = volocity * (rand() % 18 + 3);
		rotateSpeed = FRotator(rand() % 101 - 50, rand() % 101 - 50, rand() % 101 - 50) * 0.02f;
		if (Asteroid) {
			FActorSpawnParameters param;
			AAsteroid* theAsteroid = GetWorld()->SpawnActor<AAsteroid>(Asteroid, GetActorLocation(), FRotator::ZeroRotator, param);
			theAsteroid->SetSizeLevle(sizeLevel);
		}
	}
	else {
		Destroy();
	}
}

void AAsteroid::SetSizeLevle(int size) {
	sizeLevel = size;
	//Mesh -> SetRelativeScale3D(FVector(1,1,1)*SizeLevel);
	SetActorScale3D(FVector(1, 1, 1) * sizeLevel * 2);
}

