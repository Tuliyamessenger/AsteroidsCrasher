// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class LEARNCPP_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

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

	UPROPERTY(EditAnywhere, Category = "SpeedControl")
		float speed;

	//------------ Function ------------
	void Movement();
	
	//=====
	//======================================

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* Other) override;
};
