// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "Chain.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <Engine/World.h>
#include <Kismet/GameplayStatics.h>
#include <Components/SphereComponent.h>
#include <Blueprint/UserWidget.h>
#include <UObject/ConstructorHelpers.h>
#include "Components/WidgetComponent.h"
#include <Components/BoxComponent.h>
#include "HPBar.h"
#include "blackboard_keys.h"
#include <MonsterAIController.h>


AMonster::AMonster()
	: widget_Component(CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthValue")))
{
	WeaponCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("WeaponCollisionSphere"));
	WeaponCollisionSphere->InitSphereRadius(20.0f);
	WeaponCollisionSphere->AttachTo(GetMesh(), "WeaponPoint");

	spawnpoint = CreateDefaultSubobject<USphereComponent>(TEXT("SpawnPoint"));
	spawnpoint->InitSphereRadius(1.0f);
	spawnpoint->SetRelativeLocation(FVector(0, 0, 334));

	GetCharacterMovement()->bOrientRotationToMovement = true;

	if (widget_Component)
	{
		widget_Component->SetupAttachment(RootComponent);
		widget_Component->SetWidgetSpace(EWidgetSpace::Screen);
		widget_Component->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

		static ConstructorHelpers::FClassFinder<UUserWidget>widget_class(TEXT("WidgetBlueprint'/Game/_My/Blueprints/UI/WBP_HPBar.WBP_HPBar_C'"));

		if (widget_class.Succeeded())
		{
			// GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, __FUNCTION__);
			widget_Component->SetWidgetClass(widget_class.Class);
		}
	}

	/*if (MName == "Boss")
	{
		weapon = CreateDefaultSubobject<APlayerWeapon>(TEXT("Weapon"));
		static ConstructorHelpers::FObjectFinder<APlayerWeapon>weapon_object(TEXT("Blueprint'/Game/_My/Blueprints/Weapons/BP_BossWeapon.BP_BossWeapon'"));
		if (weapon_object.Succeeded())
		{
			weapon = weapon_object.Object;
		}

		WeaponCollisionSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		UBoxComponent* weaponcollision = weapon->WeaponCollision;
		weaponcollision->AttachTo(weapon->WeaponMesh, "WeaponPoint");
	}*/

	spawnTime = 3;
}

void AMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SpawnDefaultInventory();
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
}

void AMonster::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->IsA(APlayerCharacter::StaticClass()) && PlayAnimMontage(montage) > 0.2f)
	{
		UGameplayStatics::ApplyDamage(OtherActor, 10.0f, NULL, this, UDamageType::StaticClass());

		
	}
}



void AMonster::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto const uw = Cast<UHPBar>(widget_Component->GetUserWidgetObject());
	float myHPnum = (health / maxHealth * 100) * 0.01f;

	if (uw)
	{
		uw->set_bar_value_percent(myHPnum);
	}
}

int AMonster::melee_attack_Implementation()
{
	if (montage) 
	{
		if (MName == "Boss")
		{
			float healthPer = health / maxHealth;
			if (healthPer <= 0.4)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "Attack");
				PlayAnimMontage(montage);
				// Chain();
				FTimerHandle chainHandle;
				GetWorldTimerManager().SetTimer(chainHandle, this, &AMonster::Chain, 1.0f, false);
			}
			else if (healthPer <= 0.2) {
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "FinalAttack");
				PlayAnimMontage(finalMontage);
				//ChainThrow();
				FTimerHandle throwHandle;
				GetWorldTimerManager().SetTimer(throwHandle, this, &AMonster::ChainThrow, 3.0f, false);
			}
			else {
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "Normal Attack");
				PlayAnimMontage(montage);
			}

		}
	}

	return 0;
}

void AMonster::Chain()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	FVector PlayerLocation = PlayerController->GetPawn()->GetActorLocation();

	FVector fireVec = PlayerLocation - spawnpoint->GetComponentLocation();


	AChain* ChainActor = GetWorld()->SpawnActor<AChain>(
		chainFactory[0].Get(), spawnpoint->GetComponentLocation(), spawnpoint->GetComponentRotation());

	if (ChainActor)
	{
		ChainActor->FireInDirection(fireVec);
	}
	
}

void AMonster::ChainThrow()
{
	FVector socketLocationVec = GetMesh()->GetSocketLocation("ThrowPoint");

	FVector newsockVec = FVector(socketLocationVec.X, 0, 0);

	AChain* ChainActor = GetWorld()->SpawnActor<AChain>(
		chainFactory[1].Get(), socketLocationVec, GetMesh()->GetSocketRotation("ThrowPoint"));
	if (ChainActor)
	{
		ChainActor->FireInDirection(newsockVec);
	}
}

UAnimMontage* AMonster::get_montage() const
{
	return montage;
}

UAnimMontage* AMonster::get_finalMontage() const
{
	return finalMontage;
}

float AMonster::get_Health() const
{
	return health;
}

float AMonster::get_maxHealth() const
{
	return maxHealth;
}

void AMonster::set_health(float const new_health)
{
	health = maxHealth;
}