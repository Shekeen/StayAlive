// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class STAYALIVE_API AEnemy : public ACharacter
{
	GENERATED_BODY()

protected:
    int32 HP;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    int32 MaxHP;

public:
	// Sets default values for this character's properties
	AEnemy();

    void Damage(int32 damage);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

    UFUNCTION(BlueprintPure, Category = Gameplay)
    int32 GetHP();

    UFUNCTION(BlueprintNativeEvent, Category = Gameplay)
    void OnAimedAt();
};
