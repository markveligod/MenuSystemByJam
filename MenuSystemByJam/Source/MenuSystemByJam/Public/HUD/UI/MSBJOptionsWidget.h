// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/UI/MSBJBaseWidget.h"
#include "MSBJOptionsWidget.generated.h"

class USlider;
class UTextBlock;
class UButton;
class UCheckBox;
class UComboBox;

/**
 * 
 */
UCLASS()
class MENUSYSTEMBYJAM_API UMSBJOptionsWidget : public UMSBJBaseWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void SetNewScreenSize(int32 X, int32 Y);
	
protected:
	UPROPERTY(meta = (BindWidget))
		USlider* MusicSlider;
	UPROPERTY(meta = (BindWidget))
		USlider* SoundSlider;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* SoundValueTextBlock;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* MusicValueTextBlock;

	UPROPERTY(meta = (BindWidget))
		UButton* BackButton;

	UPROPERTY(meta = (BindWidget))
		UCheckBox* FullScreenCheckBox;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
		void OnChangedMusicSlider(float Value);

	UFUNCTION()
		void OnChangedSoundSlider(float Value);

	UFUNCTION()
		void OnComeBack();

	UFUNCTION()
		void OnFullScreenCheck(bool bIsChecked);

};
