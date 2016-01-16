// Fill out your copyright notice in the Description page of Project Settings.

#include "StayAlive.h"
#include "Enemy.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    MaxHP = 10;
    HP = MaxHP;
}

void AEnemy::Damage(int32 damage)
{
    HP -= damage;
    if (HP <= 0)
        Destroy();
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

int32 AEnemy::GetHP()
{
    return HP;
}

void AEnemy::OnAimedAt_Implementation()
{}
