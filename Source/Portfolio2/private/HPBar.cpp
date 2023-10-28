// Fill out your copyright notice in the Description page of Project Settings.


#include "HPBar.h"

void UHPBar::NativeConstruct() {

}

void UHPBar::set_bar_value_percent(float const value)
{
	HP_value->SetPercent(value);
}
