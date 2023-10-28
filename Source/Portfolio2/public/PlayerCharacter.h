// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class PORTFOLIO2_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	virtual void PostInitializeComponents() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true))
		class USpringArmComponent* sprintAramComp;

protected:
	UPROPERTY(EditAnywhere, Category = MyState)
		float dashDistance = 6000;
	bool dash;
	void Dashing();

	void SprintStart();
	void SprintEnd();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true))
		class UCameraComponent* cameraComp;

	UPROPERTY(EditDefaultsOnly, Category = Montage)
		UAnimMontage* dashMontage;

	UPROPERTY(EditAnywhere, Category = MyState)
		float walkSpeed = 600.0f;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	FTimerHandle playerTimer;

	void Stop();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float myHPnum;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString myHPbar_Text;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float mpNum;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString myMPbar_Text;

	void MpUpdate();

	UPROPERTY(EditAnywhere, Category = MyState)
		float mpUpdateRate;
};
