// Fill out your copyright notice in the Description page of Project Settings.


#include "HitScanWeapon.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Blaster/Character/BlasterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "particles/ParticleSystemComponent.h"

void AHitScanWeapon::Fire(const FVector& HitTarget)
{
	Super::Fire(HitTarget);

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (Owner == nullptr) return;
	AController* InstigatorController = OwnerPawn->GetController();
	//check for networking something about not having authority n instigator
	//if (!HasAuthority()&& InstigatorController) UE_LOG(LogTemp, Warning, TEXT("Instigator valid"))
	
	//to get the skeletal mesh socket  N make a const use skeletal mesh socket
	const USkeletalMeshSocket* MuzzleFlashSocket = GetWeaponMesh()->GetSocketByName("MuzzleFlash");
	//check if muszzle flash socket is valid
	if (MuzzleFlashSocket)
	{
		//get transform of socket by passing in the weapon mesh
		FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(GetWeaponMesh());
		//get the socket transform for the start location
		FVector Start = SocketTransform.GetLocation();
		//end location multiplied by an extra 24% to garanteed a hit just slighly past the mesh object
		FVector End = Start + (HitTarget - Start) * 1.25f;

		FHitResult FireHit;
		UWorld* World = GetWorld();
		if (World)
		{
			World->LineTraceSingleByChannel(
				FireHit,
				Start,
				End,
				ECollisionChannel::ECC_Visibility
			);

			//Set at end of line trace
			FVector BeamEnd = End;
			
			//check if got blocking hit
			if (FireHit.bBlockingHit)
			{
				//set beam end tothe impact point of that blocking hit
				BeamEnd = FireHit.ImpactPoint;
				ABlasterCharacter* BlasterCharacter = Cast<ABlasterCharacter>(FireHit.GetActor());
				if (BlasterCharacter && HasAuthority() && InstigatorController)
				{
					//float Damage;
					UGameplayStatics::ApplyDamage(
						BlasterCharacter, //reqires a damage actor
						Damage, //base damage amount
						InstigatorController, //instigator
						this,//damage causer
						UDamageType::StaticClass()//damage type
					);
				}
				
				if (ImpactParticles)
				{
					UGameplayStatics::SpawnEmitterAtLocation(
						World, //need the world
						ImpactParticles, //particle system
						FireHit.ImpactPoint, //end location which is the linetrace
						FireHit.ImpactNormal.Rotation()//rotation
					);
				}

				//spawn particles
				if (BeamParticles)
				{
					UParticleSystemComponent* Beam = UGameplayStatics::SpawnEmitterAtLocation(
						World,
						BeamParticles,
						SocketTransform //determine starting point of the beam
					);
						//set endpoint
					if (Beam)
					{
						Beam->SetVectorParameter(FName("Target"), BeamEnd);
					}
				}
			}
		}
	}
}
