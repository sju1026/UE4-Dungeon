// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "PlayerWeapon.h"
#include <Engine.h>
#include <Kismet/GameplayStatics.h>
#include <Engine/World.h>
#include <GameFramework/Actor.h>

// Sets default values
ABaseCharacter::ABaseCharacter()
	:health(maxHealth)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	isDuringAttack = false;

	health = 0.f;
	maxHealth = 100.0f;

	mp = 0.0f;
	maxMp = 100.0f;
}

// ==================================Weapon==================================
USkeletalMeshComponent* ABaseCharacter::GetSpesificPawnMesh() const
{
	return GetMesh();
}

FName ABaseCharacter::GetWeaponAttachPoint() const
{
	return WeaponAttachPoint;
}

void ABaseCharacter::AddWeapon(APlayerWeapon* Weapon)
{
	if (Weapon)
	{
		Inventory.AddUnique(Weapon);
	}
}

void ABaseCharacter::SetCurrentWeapon(APlayerWeapon* NewWeapon, APlayerWeapon* LastWeapon)
{
	APlayerWeapon* LocalLastWeapon = NULL;
	if (LastWeapon != NULL)
	{
		LocalLastWeapon = LastWeapon;
	}
	else if (NewWeapon != CurrentWeapon) {
		LocalLastWeapon = CurrentWeapon;
	}

	if (LocalLastWeapon) {
		LocalLastWeapon->OnUnEqip();
	}

	CurrentWeapon = NewWeapon;

	if (NewWeapon)
	{
		NewWeapon->SetOwningPawn(this);
		NewWeapon->OnEquip(LastWeapon);
	}
}

void ABaseCharacter::EquipWeapon(APlayerWeapon* Weapon)
{
	if (Weapon)
	{
		SetCurrentWeapon(Weapon, CurrentWeapon);
	}
}

void ABaseCharacter::SpawnDefaultInventory()
{
	int32 NumWeaponClasses = DefaultInventoryClasses.Num();

	/*if (DefaultInventoryClasses[0])
	{
		FActorSpawnParameters SpawnInfo;
		UWorld* WRLD = GetWorld();
		AMyTestWeapon* NewWeapon = WRLD->SpawnActor<AMyTestWeapon>(DefaultInventoryClasses[0], SpawnInfo);
		AddWeapon(NewWeapon);
	}*/

	for (int32 i = 0; i < NumWeaponClasses; i++)
	{
		if (DefaultInventoryClasses[i]) {
			FActorSpawnParameters SpawnInfo;

			UWorld* WRLD = GetWorld();
			APlayerWeapon* NewWeapon = WRLD->SpawnActor<APlayerWeapon>(DefaultInventoryClasses[i], SpawnInfo);
			AddWeapon(NewWeapon);
		}
	}

	if (Inventory.Num() > 0)
	{
		EquipWeapon(Inventory[0]);
	}
}

void ABaseCharacter::OnChangeWeapon()
{
	const int32 CurrentWeaponIndex = Inventory.IndexOfByKey(CurrentWeapon);

	APlayerWeapon* NextWeapon = Inventory[(CurrentWeaponIndex + 1) % Inventory.Num()];

	EquipWeapon(NextWeapon);

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, "change!");
}

// ==========================================================================

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	health = maxHealth;
	mp = maxMp;
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::Attack_Melee_Q()
{
	if (!isDuringAttack)
	{
		FString PlaySection = "Attack01";
		PlayAnimMontage(Attack_AnimMontage, 1.f, FName(*PlaySection));

		isDuringAttack = true;
	}
}
void ABaseCharacter::Attack_Melee_W()
{
	if (!isDuringAttack)
	{
		FString PlaySection = "Attack02";
		PlayAnimMontage(Attack_AnimMontage, 1.f, FName(*PlaySection));

		isDuringAttack = true;
	}
}
void ABaseCharacter::Attack_Melee_E()
{
	if (!isDuringAttack)
	{
		FString PlaySection = "Attack03";
		PlayAnimMontage(Attack_AnimMontage, 1.f, FName(*PlaySection));

		isDuringAttack = true;
	}
}

void ABaseCharacter::Attack_Melee_End()
{
	isDuringAttack = false;
}

void ABaseCharacter::OnHit(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	PlayAnimMontage(BeHit_AnimMontage, 1.0f, FName("GetHit"));
	if (DamageTaken > 0.f)
	{
		ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser);
	}
}

void ABaseCharacter::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	health = FMath::Min(0.f, health);

	UDamageType const* const DamageType = DamageEvent.DamageTypeClass ? Cast<const UDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject()) : GetDefault<UDamageType>();

	Killer = GetDamageInstigator(Killer, *DamageType);

	GetWorldTimerManager().ClearAllTimersForObject(this);

	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Ignore);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
	}

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->DisableMovement();
	}

	if (Controller) {
		Controller->Destroy();
	}

	GetMesh()->SetCollisionProfileName("Ragdoll");
	GetMesh()->SetSimulatePhysics(true);

	float DeathAnimDuration = PlayAnimMontage(Death_AnimMontage);

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseCharacter::OnDieAnimationEnd, DeathAnimDuration, false);
}

void ABaseCharacter::OnDieAnimationEnd()
{
	this->SetActorHiddenInGame(true);
	SetLifeSpan(0.1f);
}

float ABaseCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (health <= 0.0f)
	{
		return 0.0f;
	}

	const float myGetDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (myGetDamage > 0.f)
	{
		health -= myGetDamage;
	}

	if (health <= 0)
	{
		PlayAnimMontage(Death_AnimMontage, 1.0f);
		Die(myGetDamage, DamageEvent, EventInstigator, DamageCauser);
	}
	else
	{
		OnHit(myGetDamage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("HP is : %f"), health));
	}
	return myGetDamage;
}

