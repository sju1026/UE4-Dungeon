// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO2_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds)override;

	// 플레이어가 공중에 떴는지 확인
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlyaerAnim)
		bool isInAir = false;
};
