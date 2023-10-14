// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWeapon.h"
#include "Components/BoxComponent.h"
#include "Engine.h"

// Sets default values
APlayerWeapon::APlayerWeapon(const class FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("WeaponMesh"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = WeaponMesh;


	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
	WeaponCollision->SetBoxExtent(FVector(5.0f, 5.0f, 5.0f));
	WeaponCollision->AttachTo(WeaponMesh, "RightDamageSocket");

	static ConstructorHelpers::FObjectFinder<UParticleSystem>ParticleAsset(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	HitFX = ParticleAsset.Object;

	weaponDamage = 10.0f;
}

//=====================================================================================================
void APlayerWeapon::SetOwningPawn(ABaseCharacter* NewOwner)
{
	if (MyPawn != NewOwner) {
		MyPawn = NewOwner;
	}
}

void APlayerWeapon::AttachMeshToPawn()
{
	if (MyPawn)
	{
		USkeletalMeshComponent* PawnMesh = MyPawn->GetSpesificPawnMesh();

		FName AttachPoint = MyPawn->GetWeaponAttachPoint();


		WeaponMesh->AttachTo(PawnMesh, AttachPoint);
	}
}

void APlayerWeapon::OnEquip(const APlayerWeapon* LastWeapon)
{
	AttachMeshToPawn();
	WeaponMesh->SetHiddenInGame(false);
}

void APlayerWeapon::OnUnEqip()
{
	WeaponMesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);

	WeaponMesh->SetHiddenInGame(true);
}

//=====================================================================================================

// Called when the game starts or when spawned
void APlayerWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerWeapon::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (MyPawn) {
		if (OtherActor->IsA(AActor::StaticClass()) && MyPawn->isDuringAttack && OtherActor != MyPawn) {
			UGameplayStatics::ApplyDamage(OtherActor, weaponDamage, NULL, this, UDamageType::StaticClass());
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "ApplyDamage!");

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFX, GetActorLocation());
		}
	}
}


