// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

class ABullet;
class ALearnCppGameModeBase;
//class USoundCue;
class USoundWave;

UCLASS()
class LEARNCPP_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//========================================
	//				Default Data
	//========================================
	//---------- Property ---------
	
	UPROPERTY(VisibleAnywhere, Category = "Component")
		USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, Category = "Component")
		UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, Category = "Component")
		USceneComponent* Aim;

	UPROPERTY(EditAnywhere, Category="Bullet")
		TSubclassOf<ABullet> Bullet;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
		float rotateSpeed;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float accelerate;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float invinciTime;

	UPROPERTY(EditAnywhere, Category = "Effect")
		UParticleSystem* Explode_PS;
	UPROPERTY(EditAnywhere, Category = "Effect")
		USoundWave* Fire_Sound;
	UPROPERTY(EditAnywhere, Category = "Effect")
		USoundWave* Explode_Sound;

	ALearnCppGameModeBase* gameMode;
	FVector speed;
	float invincible;
	bool gameover;

	//---------- Function -----------
	void Move_X(float axis);
	void Move_Y(float axis);
	void Movement();
	void Fire();
	
	//=====
	//======================================

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void NotifyActorBeginOverlap(AActor* Other) override;

};
