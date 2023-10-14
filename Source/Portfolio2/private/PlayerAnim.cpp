// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "PlayerCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// 플레이어의 이동 속도를 가져와 speed에 할당
	// 1. 소유 폰 얻어 오기
	auto ownerPawn = TryGetPawnOwner();
	// 2. 플레이어로 캐스팅
	auto player = Cast<APlayerCharacter>(ownerPawn);

	if (player) {

		// 플레이어가 현재 공중에 있는지 여부를 기억
		auto movement = player->GetCharacterMovement();
		isInAir = movement->IsFalling();
	}
}