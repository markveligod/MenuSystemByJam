// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/UI/MSBJBaseWidget.h"
#include "MenuSystemByJam/MenuSystemByJamGameModeBase.h"

void UMSBJBaseWidget::Show()
{
	PlayAnimation(this->ShowAnimation);
}

AMenuSystemByJamGameModeBase* UMSBJBaseWidget::GetCurrentGameMode() const
{
	return (GetWorld() ? Cast<AMenuSystemByJamGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr);
}
