// Fill out your copyright notice in the Description page of Project Settings.


#include "Chain.h"
#include "PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"


// Sets default values
AChain::AChain(const class FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	chainCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
	chainCollision->SetBoxExtent(FVector(5.0f, 5.0f, 5.0f));
	RootComponent = chainCollision;

	chainMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("WeaponMesh"));
	chainMesh->SetupAttachment(chainCollision);
	chainMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	chainCollision->AttachTo(chainMesh, "HitBox");

	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	// movement 컴포넌트가 갱신시킬 컴포넌트 지정
	movementComp->SetUpdatedComponent(chainCollision);
	// 초기 속도
	movementComp->InitialSpeed = speed;
	// 최대속도
	movementComp->MaxSpeed = speed;
	// 반동여부
	movementComp->bShouldBounce = false;
	movementComp->bRotationFollowsVelocity = true;

	InitialLifeSpan = 2.0f;
}

// Called when the game starts or when spawned
void AChain::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle deathTimer;
	GetWorld()->GetTimerManager().SetTimer(deathTimer, FTimerDelegate::CreateLambda([this]()->void {
		Destroy();
		}), 2.0f, false);
	
}

// Called every frame
void AChain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AChain::FireInDirection(const FVector& shootDirection)
{
	movementComp->Velocity = shootDirection * speed;
}

void AChain::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.GetPropertyName() == TEXT("speed")) {
		// 프로젝타일 무브먼트 컴포넌트에 speed값 적용
		movementComp->InitialSpeed = speed;
		movementComp->MaxSpeed = speed;
	}
}
