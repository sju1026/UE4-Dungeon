// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "GameFramework/Actor.h"
#include "PlayerCharacter.h"
#include "PlayerWeapon.h"
#include "Monster.h"
#include "GameFramework/SpringArmComponent.h"
#include "Teleport.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO2_API ATeleport : public ATriggerBox
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	ATeleport();

	UFUNCTION()
		void EnterTeleporter(class AActor* overlappedActor, class AActor* otherActor);

	UFUNCTION()
		void ExitTeleporter(class AActor* overlappedActor, class AActor* otherActor);

	UPROPERTY(EditAnywhere, Category = Teleporter)
		ATeleport* otherTele;

	UPROPERTY()
		bool teleporting;

	UPROPERTY(VisibleAnywhere, Category = Monsters)
		TArray<TSubclassOf<class AMonster>> monsters1;

	UPROPERTY(VisibleAnywhere, Category = Monsters)
		TArray<TSubclassOf<class AMonster>> monsters2;

	UPROPERTY(VisibleAnywhere, Category = Monsters)
		TArray<TSubclassOf<class AMonster>> monsters3;

	UPROPERTY(EditAnywhere, Category = Mesh)
		int32 teleValue;

	UPROPERTY(EditAnywhere, Category = Mesh)
		int32 teleCount;

	class APlayerWeapon* playerWeapon;
};
