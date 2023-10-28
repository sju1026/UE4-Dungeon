// Copyright Epic Games, Inc. All Rights Reserved.


#include "Portfolio2GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "HUD_InGame.h"

APortfolio2GameModeBase::APortfolio2GameModeBase() {
	static ConstructorHelpers::FClassFinder<APawn> player(TEXT("Blueprint'/Game/_My/Blueprints/BP_PlayerCharacter.BP_PlayerCharacter_C'"));
	if (player.Succeeded())
	{
		DefaultPawnClass = player.Class;
	}

	HUDClass = AHUD_InGame::StaticClass();

}


void APortfolio2GameModeBase::BeginPlay() {
	Super::BeginPlay();


}

//void APortfolio2GameModeBase::ChaingeUI()
//{
//	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
//	CurrentWidget->AddToViewport();
//}
