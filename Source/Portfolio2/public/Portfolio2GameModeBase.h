// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Portfolio2GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO2_API APortfolio2GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	APortfolio2GameModeBase();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget>HUDWidgetClass;

	UUserWidget* CurrentWidget;

public:
	// void ChaingeUI();
};
