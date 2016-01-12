// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "StayAlive.h"
#include "StayAliveProjectile.h"
#include "Enemy.h"
#include "GameFramework/ProjectileMovementComponent.h"

AStayAliveProjectile::AStayAliveProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AStayAliveProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;

    BaseDamage = 1;
    DamageMultiplier = 1;
}

int32 AStayAliveProjectile::GetDamage()
{
    return BaseDamage * DamageMultiplier;
}

void AStayAliveProjectile::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor == nullptr || OtherActor == this || OtherComp == nullptr)
        return;

    AEnemy* enemy = Cast<AEnemy>(OtherActor);
    if (enemy != nullptr) {
        enemy->Damage(GetDamage());
        Destroy();
    } else if (OtherActor->ActorHasTag("floor")) {
        DamageMultiplier = 2;
    } else if (OtherActor->ActorHasTag("wall")) {
        DamageMultiplier = 5;
    } else if (OtherComp->IsSimulatingPhysics()) {
        // Only add impulse and destroy projectile if we hit a physics
        OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		Destroy();
	}
}