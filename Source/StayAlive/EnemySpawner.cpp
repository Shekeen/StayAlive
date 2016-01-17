// Fill out your copyright notice in the Description page of Project Settings.

#include "StayAlive.h"
#include "EnemySpawner.h"


// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SpawnClass = AEnemy::StaticClass();
    MaxSpawnedEnemies = 5;
    MinSpawnCooldown = 1.f;
    MaxSpawnCooldown = 4.f;

    CurSpawnCooldown = GetRandomSpawnCooldown();
    bCanSpawn = true;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

    if (!bCanSpawn)
        return;

    TArray<AActor*> enemies;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), enemies);
    if (enemies.Num() >= MaxSpawnedEnemies)
        return;

    CurSpawnCooldown -= DeltaTime;
    if (CurSpawnCooldown < 0.f) {
        SpawnNewEnemy();
        CurSpawnCooldown += GetRandomSpawnCooldown();
    }
}

void AEnemySpawner::EnableSpawning()
{
    bCanSpawn = true;
    CurSpawnCooldown = GetRandomSpawnCooldown();
}

void AEnemySpawner::DisableSpawning()
{
    bCanSpawn = false;
}

float AEnemySpawner::GetRandomSpawnCooldown()
{
    return FMath::FRandRange(MinSpawnCooldown, MaxSpawnCooldown);
}

AActor* AEnemySpawner::GetRandomSpawnPoint()
{
    int32 spawnPointsNum = SpawnPoints.Num();
    if (spawnPointsNum == 0)
        return nullptr;
    return SpawnPoints[FMath::RandRange(0, spawnPointsNum - 1)];
}

void AEnemySpawner::SpawnNewEnemy()
{
    AActor* spawnPoint = GetRandomSpawnPoint();
    if (spawnPoint == nullptr)
        return;

    UWorld* world = GetWorld();
    if (world == nullptr)
        return;

    AEnemy* enemy = world->SpawnActor<AEnemy>(SpawnClass, 
                                              spawnPoint->GetActorLocation(), 
                                              spawnPoint->GetActorRotation());
    OnEnemySpawned(enemy);
}

void AEnemySpawner::OnEnemySpawned_Implementation(AEnemy* enemy)
{}
