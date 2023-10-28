// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "BaseCharacter.h"
#include <Animation/AnimMontage.h>
#include "CombatInterface.h"
// #include "PlayerWeapon.h"
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

	virtual void PostInitializeComponents() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor)override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime)override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
		class USphereComponent* WeaponCollisionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
		class USphereComponent* spawnpoint;

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
		FName spawnpointAttach;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
		FName MName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
		class UBehaviorTree* BotBehavior;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State)
		int32 spawnTime;

	UPROPERTY(EditDefaultsOnly, Category = SpawnSetting)
		TArray<TSubclassOf<class AChain>> chainFactory;

	virtual int melee_attack_Implementation()override;

	UAnimMontage* get_montage() const;

	UAnimMontage* get_finalMontage() const;

	class AMonster* monster;

	class APlayerCharacter* player;

	float get_Health() const;

	float get_maxHealth() const;

	void set_health(float const new_health);

	void Chain();

	void ChainThrow();

	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		APlayerWeapon* weapon;*/
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* finalMontage;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget)
		class UWidgetComponent* widget_Component;

	FTimerHandle spawnChainHandle;
};
