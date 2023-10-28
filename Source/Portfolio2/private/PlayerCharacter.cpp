// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include <Engine/Classes/Components/CapsuleComponent.h>
#include <Engine/Classes/Camera/CameraComponent.h>
#include <Engine/Classes/GameFramework/CharacterMovementComponent.h>
#include <Engine/Classes/GameFramework/SpringArmComponent.h>
#include "Components/WidgetComponent.h"
#include "UI_InGame.h"
#include <Chain.h>


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	sprintAramComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	sprintAramComp->SetupAttachment(RootComponent);
	sprintAramComp->SetUsingAbsoluteRotation(true);
	sprintAramComp->TargetArmLength = 800.0f;
	sprintAramComp->SetRelativeRotation(FRotator(-60.0f, 45.0f, 0.0f));
	sprintAramComp->bDoCollisionTest = false;

	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cameraComp->SetupAttachment(sprintAramComp, USpringArmComponent::SocketName);
	cameraComp->bUsePawnControlRotation = false;

	dash = false;
	mpUpdateRate = 5.0f;
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SpawnDefaultInventory();
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	myHPnum = (health / maxHealth * 100) * 0.01f;

	myHPbar_Text = FString::SanitizeFloat(health) + "/" + FString::SanitizeFloat(maxHealth);

	mpNum = (mp / maxMp * 100) * 0.01f;

	myMPbar_Text = FString::SanitizeFloat(mp) + "/" + FString::SanitizeFloat(maxMp);

	FTimerHandle mpHandle;
	GetWorldTimerManager().SetTimer(mpHandle, this, &APlayerCharacter::MpUpdate, mpUpdateRate, false);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &APlayerCharacter::Dashing);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::SprintEnd);

	PlayerInputComponent->BindAction("QInput", IE_Pressed, this, &ABaseCharacter::Attack_Melee_Q);
	PlayerInputComponent->BindAction("WInput", IE_Pressed, this, &ABaseCharacter::Attack_Melee_W);
	PlayerInputComponent->BindAction("EInput", IE_Pressed, this, &ABaseCharacter::Attack_Melee_E);
}

void APlayerCharacter::Dashing()
{
	dash = true;
	if (dash == true)
	{
		const FVector forwardDir = this->GetActorRotation().Vector();
		LaunchCharacter(forwardDir * dashDistance, true, true);
		if (dashMontage)
		{
			PlayAnimMontage(dashMontage, 1, FName("Dash"));
		}
	}
	FTimerHandle dashTimer;
	GetWorld()->GetTimerManager().SetTimer(dashTimer, FTimerDelegate::CreateLambda([this]()->void {dash = false; }), 2.0f, false);
}

void APlayerCharacter::SprintStart()
{
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed + 400.0f;
}

void APlayerCharacter::SprintEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
}

void APlayerCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->IsA(AChain::StaticClass()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Hit!");
		GetCharacterMovement()->MaxWalkSpeed = 0.0f;
		GetWorldTimerManager().SetTimer(playerTimer, this, &APlayerCharacter::Stop, 1.5f);
	}
}

void APlayerCharacter::Stop()
{
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
}

void APlayerCharacter::MpUpdate()
{
	if (mp >= maxMp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Mp is Max!");
		mp = maxMp;
	}
	else if (mp < maxMp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Mp+10.0f!");
		mp += 10.0f;
	}

}

