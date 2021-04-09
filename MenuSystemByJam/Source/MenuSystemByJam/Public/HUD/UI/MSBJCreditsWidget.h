// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/UI/MSBJBaseWidget.h"
#include "MSBJCreditsWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class MENUSYSTEMBYJAM_API UMSBJCreditsWidget : public UMSBJBaseWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
		UButton* BackButton;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
		void OnComeBack();
};
