// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWeapon.h"
#include "Monster.h"
#include "UObject/ConstructorHelpers.h"
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
	
	FindSpawnPoint();

}

// Called every frame
void APlayerWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerWeapon::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (MyPawn) {
		if (OtherActor->IsA(AMonster::StaticClass()) && MyPawn->isDuringAttack) {
			UGameplayStatics::ApplyDamage(OtherActor, weaponDamage, NULL, this, UDamageType::StaticClass());
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "ApplyDamage!");

			AMonster* boss = Cast<AMonster>(OtherActor);

			if (boss->MName == "Boss")
			{
				int random = FMath::RandRange(0, spawnPoint.Num() - 1);
				boss->SetActorRelativeLocation(spawnPoint[random]->GetActorLocation());
			}
			
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFX, GetActorLocation());
		}
	}
}

void APlayerWeapon::FindSpawnPoint()
{
	TArray<AActor*> allActors;
	// 원하는 타입의 액터 모두 찾아오기
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), allActors);
	// 찾은 결과가 있을 경우 반복적으로
	for (auto spawn : allActors) {
		// 찾은 액터의 이름에 해당 문자열을 포함하고 있다면
		if (spawn->GetName().Contains(TEXT("BP_SpawnPoint"))) {
			// 스폰 목록에 추가
			spawnPoint.Add(spawn);
		}
	}
}


