/*
 * By Mark Veligod
 * Company Name: VeligodStudio
 * GitHub: https://github.com/markveligod
 * Itch: https://veligodstudio.itch.io/
 * Contact: markveligod@yandex.ru
 */

#pragma once

#include "CoreMinimal.h"
#include "HUD/UI/MSBJBaseWidget.h"
#include "MSBJOptionsWidget.generated.h"

class USlider;
class UTextBlock;
class UButton;
class UCheckBox;
class UComboBox;
class USoundClass;

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
	
	UFUNCTION(BlueprintCallable)
		void SetQualityGame(int32 NumQuality);

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
		UButton* LangRuButton;
	UPROPERTY(meta = (BindWidget))
		UButton* LangEnButton;

	UPROPERTY(meta = (BindWidget))
		UCheckBox* FullScreenCheckBox;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound classes Editor")
		USoundClass* MusicMenuClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound classes Editor")
		USoundClass* SoundMenuClass;

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

	UFUNCTION()
		void OnRuLangChanged();

	UFUNCTION()
		void OnEnLangChanged();

};
