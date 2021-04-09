// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MSBJBaseWidget.generated.h"

class AMenuSystemByJamGameModeBase;
/**
 * 
 */
UCLASS()
class MENUSYSTEMBYJAM_API UMSBJBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Show();

protected:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		UWidgetAnimation* ShowAnimation;

	AMenuSystemByJamGameModeBase* GetCurrentGameMode() const;
};
