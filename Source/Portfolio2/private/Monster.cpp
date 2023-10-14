// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <Engine/World.h>
#include <Kismet/GameplayStatics.h>
#include <Components/SphereComponent.h>
#include "blackboard_keys.h"


AMonster::AMonster() {
	WeaponCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("WeaponCollisionSphere"));
	WeaponCollisionSphere->InitSphereRadius(20.0f);
	WeaponCollisionSphere->AttachTo(GetMesh(), "WeaponPoint");

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void AMonster::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->IsA(AActor::StaticClass()) && PlayAnimMontage(montage) > 0.2f)
	{
		UGameplayStatics::ApplyDamage(OtherActor, 10.0f, NULL, this, UDamageType::StaticClass());
	}
}

int AMonster::melee_attack_Implementation()
{
	if (montage) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "Attack");
		PlayAnimMontage(montage);
	}

	return 0;
}

UAnimMontage* AMonster::get_montage() const
{
	return montage;
}
