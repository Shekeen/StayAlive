// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "EnemySpawner.generated.h"

UCLASS()
class STAYALIVE_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    TArray<AActor*> SpawnPoints;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    TSubclassOf<AEnemy> SpawnClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    float MinSpawnCooldown;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    float MaxSpawnCooldown;

protected:
    float CurSpawnCooldown;
    bool bCanSpawn;

protected:
    float GetRandomSpawnCooldown();
    AActor* GetRandomSpawnPoint();
    void SpawnNewEnemy();

public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    UFUNCTION(BlueprintCallable, Category = Gameplay)
    void EnableSpawning();

    UFUNCTION(BlueprintCallable, Category = Gameplay)
    void DisableSpawning();
};
