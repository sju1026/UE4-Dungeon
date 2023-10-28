// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class PORTFOLIO2_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		FName characterName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float maxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float mp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float maxMp;
	

	// ===========================Weapon[Inventory]=================================

	USkeletalMeshComponent* GetSpesificPawnMesh()const;

	FName GetWeaponAttachPoint()const;

	void EquipWeapon(class APlayerWeapon* Weapon);

	void OnChangeWeapon();
protected:
	UPROPERTY(EditDefaultsOnly, Category = Inventory)
		FName WeaponAttachPoint;

	TArray<class APlayerWeapon*>Inventory;

	class APlayerWeapon* CurrentWeapon;

	void AddWeapon(class APlayerWeapon* Weapon);

	void SetCurrentWeapon(class APlayerWeapon* NewWeapon, class APlayerWeapon* LastWeapon);

	void SpawnDefaultInventory();

public:
	UPROPERTY(EditAnywhere, Category = Invetory)
		TArray<TSubclassOf<class APlayerWeapon>>DefaultInventoryClasses;

	// =============================================================================
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);

	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);

	void OnDieAnimationEnd();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = Montage)
		UAnimMontage* Attack_AnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montage)
		UAnimMontage* BeHit_AnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montage)
		UAnimMontage* Death_AnimMontage;

	void Attack_Melee_Q();
	void Attack_Melee_W();
	void Attack_Melee_E();
	void Attack_Melee_End();

	bool isDuringAttack = true;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)override;
};
