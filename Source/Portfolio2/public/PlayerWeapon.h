// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "PlayerWeapon.generated.h"

UCLASS()
class PORTFOLIO2_API APlayerWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerWeapon(const class FObjectInitializer& ObjectInitializer);

	void SetOwningPawn(ABaseCharacter* NewOwner);
	void AttachMeshToPawn();
	void OnEquip(const APlayerWeapon* LastWeapon);
	void OnUnEqip();

private:
	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
		USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
		class UBoxComponent* WeaponCollision;

protected:

	class ABaseCharacter* MyPawn;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(EditDefaultsOnly, Category = "MyFX")
		UParticleSystem* HitFX;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon State")
		float weaponDamage;
};
