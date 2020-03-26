// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Asteroid.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = Root = CreateDefaultSubobject<USceneComponent>("Root");
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	speed = 100;
	
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Movement();
}

void ABullet::Movement() {
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * speed);

	FVector position = GetActorLocation();
	if (position.X < -3600 || position.X > 3600 || position.Y < -2000 || position.Y > 2000) Destroy();
}

void ABullet::NotifyActorBeginOverlap(AActor* other) {
	Super::NotifyActorBeginOverlap(other);

	AAsteroid* theAsteroid = Cast<AAsteroid>(other);
	if (theAsteroid) {
		theAsteroid->BeHit();
		Destroy();
	}
}

