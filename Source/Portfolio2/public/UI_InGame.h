// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Runtime/UMG/Public/Components/ProgressBar.h>
#include "UI_InGame.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIO2_API UUI_InGame : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// void NativeConstruct() override;
	void set_HUDbar_value_percent(float const value);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UProgressBar* HUD_HPbar_value = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UProgressBar* HUD_MPbar_value = nullptr;

//protected:
//	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
//		UButton* Btn_GameMenu = nullptr;
//
//	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
//		UButton* Btn_Inventory = nullptr;
//
//	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
//		UButton* Btn_Attack = nullptr;
//
//	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
//		UButton* Btn_ChangeWeapon = nullptr;

};
