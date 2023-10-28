// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleport.h"
#include "PlayerWeapon.h"
#include <Engine/Classes/Camera/CameraComponent.h>
#include "Kismet/GameplayStatics.h"

ATeleport::ATeleport()
{
	OnActorBeginOverlap.AddDynamic(this, &ATeleport::EnterTeleporter);
	OnActorEndOverlap.AddDynamic(this, &ATeleport::ExitTeleporter);

	teleporting = false;

	teleCount = 0;

	playerWeapon = nullptr;
}

void ATeleport::BeginPlay() {
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerWeapon::StaticClass(), FoundActors);

	if (FoundActors.Num() > 0)
	{
		playerWeapon = Cast<APlayerWeapon>(FoundActors[0]);
	}
}

void ATeleport::EnterTeleporter(AActor* overlappedActor, AActor* otherActor)
{
	if (otherActor && otherActor != this)
	{
		if (otherTele)
		{
			APlayerCharacter* character = Cast<APlayerCharacter>(otherActor);

			if (character && !otherTele->teleporting)
			{
				if (monsters1.Num() == 0 && teleValue == 1 && teleCount == 0)
				{
					teleporting = true;
					character->SetActorRotation(otherTele->GetActorRotation());
					character->GetController()->SetControlRotation(character->GetActorRotation());
					character->SetActorLocation(otherTele->GetActorLocation());

					if (playerWeapon)
					{
						playerWeapon->weaponDamage += 20.0f;
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("PlayerWeapon Damage : %f"), playerWeapon->weaponDamage));
					}

					
				}

				else if (monsters2.Num() == 0 && teleValue == 2 && teleCount == 1)
				{
					teleporting = true;
					character->SetActorRotation(otherTele->GetActorRotation());
					character->GetController()->SetControlRotation(character->GetActorRotation());
					character->SetActorLocation(otherTele->GetActorLocation());

					if (playerWeapon)
					{
						playerWeapon->weaponDamage += 20.0f;
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("PlayerWeapon Damage : %f"), playerWeapon->weaponDamage));
					}
				}

				else if (monsters3.Num() == 0 && teleValue == 3 && teleCount == 2)
				{
					teleporting = true;
					character->SetActorRotation(otherTele->GetActorRotation());
					character->GetController()->SetControlRotation(character->GetActorRotation());
					character->SetActorLocation(otherTele->GetActorLocation());
					character->cameraComp->SetRelativeLocation(FVector(-254, -0.000137, -0.000107));

					if (playerWeapon)
					{
						playerWeapon->weaponDamage += 20.0f;
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("PlayerWeapon Damage : %f"), playerWeapon->weaponDamage));
					}
				}

			}
		}
	}

}

void ATeleport::ExitTeleporter(AActor* overlappedActor, AActor* otherActor)
{
	if (otherActor && otherActor != this)
	{
		if (otherTele && !teleporting)
		{
			teleCount++;
			otherTele->teleporting = false;
		}
	}
}
