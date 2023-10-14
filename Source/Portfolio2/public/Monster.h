// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.h"
#include <Animation/AnimMontage.h>
#include "CombatInterface.h"
#include "Monster.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO2_API AMonster : public ABaseCharacter, public ICombatInterface
{
	GENERATED_BODY()
	
public:
	AMonster();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor)override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
		class USphereComponent* WeaponCollisionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
		FName MName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
		class UBehaviorTree* BotBehavior;

	virtual int melee_attack_Implementation()override;

	UAnimMontage* get_montage() const;

	class AMonster* me;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* montage;
};
