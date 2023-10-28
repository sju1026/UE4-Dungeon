// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimNotifyState.h"
#include "BaseCharacter.h"
#include <Engine.h>

void UPlayerAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) {
	// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, __FUNCTION__);

	if (MeshComp != NULL && MeshComp->GetOwner() != NULL) {
		ABaseCharacter* Player = Cast<ABaseCharacter>(MeshComp->GetOwner());
		if (Player != NULL) {
			Player->Attack_Melee_Q();
			Player->mp -= 10.0f;
			Player->isDuringAttack = true;
		}
	}
}

void UPlayerAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, __FUNCTION__);

	if (MeshComp != NULL && MeshComp->GetOwner() != NULL) {
		ABaseCharacter* Player = Cast<ABaseCharacter>(MeshComp->GetOwner());
		if (Player != NULL) {
			Player->Attack_Melee_End();
			Player->isDuringAttack = false;
		}
	}
}