// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileRocket.h"
#include "Kismet/GameplayStatics.h"

AProjectileRocket::AProjectileRocket()
{
	//create rocket static subobject mesh component
	RocketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rocket Mesh"));
	//attach to the rootcomponent
	RocketMesh->SetupAttachment(RootComponent);
	//make the rocket mesh have no collision as it is purely cosmetic
	RocketMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AProjectileRocket::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                              FVector NormalImpulse, const FHitResult& Hit)
{
	//returns the pawn that owns the weapon that fired the rocket
	APawn* FiringPawn = GetInstigator();
	if (FiringPawn)
	{
		AController* FiringController = FiringPawn->GetController();
		if (FiringController)
		{
			UGameplayStatics::ApplyRadialDamageWithFalloff(
			    this, //world context object
			    Damage,//BaseDamage / amount of damage
				10.f,//Minimum damage /radius damage
				GetActorLocation(), //radius damage centered around the rocket / origin
				200.f,//inner radius damage
				500.f, //outer radius damage
				1.f,//damage fallof which is exponential, 1.f for linear damage falloff for actors the farther away they are from the inner radius and that damage decrease will be linear
				UDamageType::StaticClass(), //damage type class
				TArray<AActor*>(),//ignore damage to any actor
				this, // damage causer which is the rocket
				FiringController //InstigatorController
			);
		}
	}
	
	Super::OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
}
