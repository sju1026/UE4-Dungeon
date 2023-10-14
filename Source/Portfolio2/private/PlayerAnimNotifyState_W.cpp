// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimNotifyState_W.h"
#include "BaseCharacter.h"
#include <Engine.h>

void UPlayerAnimNotifyState_W::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) {
	// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, __FUNCTION__);

	if (MeshComp != NULL && MeshComp->GetOwner() != NULL) {
		ABaseCharacter* Player = Cast<ABaseCharacter>(MeshComp->GetOwner());
		if (Player != NULL) {
			Player->Attack_Melee_W();

			Player->isDuringAttack = true;
		}
	}
}

void UPlayerAnimNotifyState_W::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, __FUNCTION__);

	if (MeshComp != NULL && MeshComp->GetOwner() != NULL) {
		ABaseCharacter* Player = Cast<ABaseCharacter>(MeshComp->GetOwner());
		if (Player != NULL) {
			Player->Attack_Melee_End();
			Player->isDuringAttack = false;
		}
	}
}
