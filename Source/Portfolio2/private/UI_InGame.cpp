// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_InGame.h"

void UUI_InGame::set_HUDbar_value_percent(float const value) {
	HUD_HPbar_value->SetPercent(value);
	HUD_MPbar_value->SetPercent(value);
}