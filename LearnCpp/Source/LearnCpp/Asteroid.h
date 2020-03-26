// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Asteroid.generated.h"

class USphereComponent;
class ALearnCppGameModeBase;
class USoundWave;

UCLASS()
class LEARNCPP_API AAsteroid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//========================================
	//				Default Data
	//========================================
	//---------- Property ---------
	
	//UPROPERTY(VisibleAnywhere, Category = "Component")
		//USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, Category = "Component")
		UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, Category = "Component")
		USphereComponent* Collider;
	

	UPROPERTY(EditAnywhere, Category = "Asteroid")
		TSubclassOf<AAsteroid> Asteroid;

	UPROPERTY(EditAnywhere, Category = "Effect")
		UParticleSystem* Explode;
	UPROPERTY(EditAnywhere, Category = "Effect")
		USoundWave* Explode_Sound;
	

	ALearnCppGameModeBase* gameMode;
	FVector speed;
	FRotator rotateSpeed;
	int sizeLevel;

	//---------- Function -----------
	void Movement();
	
	//=====
	//======================================
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//========================================
	//			Default Data Public
	//========================================

	
	//---------- Function ---------
	void BeHit();
	void SetSizeLevle(int size);

	//=======
	//====================================
};
