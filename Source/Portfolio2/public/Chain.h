// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerCharacter.h"

#include "Chain.generated.h"

UCLASS()
class PORTFOLIO2_API AChain : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChain(const class FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
		USkeletalMeshComponent* chainMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
		class UBoxComponent* chainCollision;

	UPROPERTY(VisibleAnywhere, Category = Movement)
		class UProjectileMovementComponent* movementComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class APlayerCharacter* player;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Setting)
		float speed = 500;

	void FireInDirection(const FVector& shootDirection);

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)override;
};
