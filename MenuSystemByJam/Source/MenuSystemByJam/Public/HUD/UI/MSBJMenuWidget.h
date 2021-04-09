// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/UI/MSBJBaseWidget.h"
#include "MSBJMenuWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class MENUSYSTEMBYJAM_API UMSBJMenuWidget : public UMSBJBaseWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
		UButton* OptionsButton;

	UPROPERTY(meta = (BindWidget))
		UButton* CreditsButton;

	UPROPERTY(meta = (BindWidget))
		UButton* QuitButton;

	virtual void NativeOnInitialized() override;
private:
	UFUNCTION()
		void OnStartGame();

	UFUNCTION()
		void OnOptionsGame();

	UFUNCTION()
		void OnCreditsGame();

	UFUNCTION()
		void OnQuitGame();
};
