// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "LearnCppGameModeBase.h"
#include "Particles/particleSystem.h"
#include "Sound/SoundWave.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	rotateSpeed = 3;
	accelerate = 0.5f;
	speed = FVector::ZeroVector;
	gameover = false;
	invinciTime = 3.0f;
	invincible = invinciTime;

	RootComponent = Root = CreateDefaultSubobject<USceneComponent>("Root");
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	Aim = CreateAbstractDefaultSubobject<USceneComponent>("Aim");
	Aim->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	gameMode = Cast<ALearnCppGameModeBase>(UGameplayStatics::GetGameMode(this));
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!gameover) Movement();
	if (invincible > 0) invincible -= DeltaTime;
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	InputComponent->BindAxis("MoveX", this, &AMyPawn::Move_X);
	InputComponent->BindAxis("MoveY", this, &AMyPawn::Move_Y);
	InputComponent->BindAction("Fire", IE_Pressed, this, &AMyPawn::Fire);
	
}

//====================================================
//					Player Control
//====================================================

//----------------- Movement ---------------
void AMyPawn::Move_X(float axis) {
	FRotator rotation = GetActorRotation();
	rotation.Yaw += rotateSpeed * axis;
	SetActorRotation(rotation);
}

void AMyPawn::Move_Y(float axis) {
	speed += GetActorForwardVector()*axis* accelerate;
}

void AMyPawn::Movement() {
	if (invincible > 0) {
		if ((int)(invincible * 5) % 2 == 0) Mesh->SetVisibility(false);
		else Mesh->SetVisibility(true);
	}
	else {
		Mesh->SetVisibility(true);
	}

	FVector position = GetActorLocation();
	if ((position.X < -3600 && speed.X < 0) || (position.X > 3600 && speed.X > 0)) position.X = -position.X;
	if ((position.Y < -2000 && speed.Y < 0) || (position.Y > 2000 && speed.Y > 0)) position.Y = -position.Y;
	SetActorLocation(position + speed);
}

//----------------- Fire ---------------
void AMyPawn::Fire() {
	if (Bullet) {
		UGameplayStatics::PlaySoundAtLocation(this, Fire_Sound, GetActorLocation());
		FActorSpawnParameters param;
		GetWorld()->SpawnActor<ABullet>(Bullet, Aim->GetComponentLocation(), Aim->GetComponentRotation(), param);
	}
}

//===================================================
//					  Collision
//===================================================
void AMyPawn::NotifyActorBeginOverlap(AActor* other) {
	Super::NotifyActorBeginOverlap(other);

	if (invincible > 0 || gameover) return;

	AAsteroid* theAsteroid = Cast<AAsteroid>(other);
	if (theAsteroid) {
		//theAsteroid->BeHit();
		invincible = invinciTime;
		speed = FVector::ZeroVector;
		if (Explode_PS) UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explode_PS, GetActorLocation(), FRotator::ZeroRotator, true);
		if (Explode_Sound) UGameplayStatics::PlaySoundAtLocation(this, Explode_Sound, GetActorLocation());
		if (gameMode) {
			gameMode->ReduceChance();
			if (gameMode->GetChance() < 0) {
				gameover = true;
				SetActorLocation(FVector(12345,0,0));
			}
			else {
				SetActorLocation(FVector::ZeroVector);
			}
		}
		
		SetActorRotation(FRotator(0,-90,0));
	}
}
