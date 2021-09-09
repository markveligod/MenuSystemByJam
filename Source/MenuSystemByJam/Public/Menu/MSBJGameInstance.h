/*
 * By Mark Veligod
 * Company Name: VeligodStudio
 * GitHub: https://github.com/markveligod
 * Itch: https://veligodstudio.itch.io/
 * Contact: markveligod@yandex.ru
 */

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MSBJGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MENUSYSTEMBYJAM_API UMSBJGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	/* level names for interaction from other classes */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Levels Editor")
		FName NameStartLevel = NAME_None;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Levels Editor")
		FName NameMenuLevel = NAME_None;

	/* Volume editor for sound classes */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Volume Editor")
		USoundClass* MusicMenuClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Volume Editor", meta = (ClampMin = "0.0", ClampMax = "100.0"))
		float DefaultMusicVolumeValue = 50.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Volume Editor")
		USoundClass* SoundMenuClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Volume Editor", meta = (ClampMin = "0.0", ClampMax = "100.0"))
		float DefaultSoundVolumeValue = 50.f;

	/* Get and Set for CurrentWindowMode */
	EWindowMode::Type GetCurrentWindowMode() const { return (this->CurrentWindowMode); }
	void SetCurrentWindowMode(EWindowMode::Type NewType) { this->CurrentWindowMode = NewType; }

	/* Get and Set for CurrentScreen */
	FIntPoint GetScreenViewport() const { return (this->CurrentScreen); }
	void SetScreenViewport(FIntPoint NewScreen) { this->CurrentScreen = NewScreen; }

	/* Get and Set for CurrentLanguage */
	FString GetCurrentLanguage() const { return (this->CurrentLanguage); }
	void SetCurrentLanguage(FString NewLang) { this->CurrentLanguage = NewLang; }

	/* Get for CurrentArrayScreenSize */
	TArray <FIntPoint> GetArrayCurrentScreenSize() const { return (this->CurrentArrayScreenSize); }

	void ChangeArrayScreenSize(bool State) { this->CurrentArrayScreenSize = (State == true) ? this->ArrayFullScreenSize : this->ArrayWindowedScreenSize; this->CurrentScreen = this->CurrentArrayScreenSize[this->CurrentArrayScreenSize.Num() - 1]; }

	/* Get and Set MusicVolumeValue */
	void SetMusicVolumeValue(float NewValue) { this->MusicVolumeValue = NewValue; }
	float GetMusicVolumeValue() const { return (this->MusicVolumeValue); }

	/* Get and Set for SoundVolumeValue */
	void SetSoundVolumeValue(float NewValue) { this->SoundVolumeValue = NewValue; }
	float GetSoundVolumeValue() const { return (this->SoundVolumeValue); }

	void SetMusicVolumeText(FText NewText) { this->MusicVolumeText = NewText; }
	FText GetMusicVolumeText() const { return (this->MusicVolumeText); }

	/* Get and Set for SoundVolumeText */
	void SetSoundVolumeText(FText NewText) { this->SoundVolumeText = NewText; }
	FText GetSoundVolumeText() const { return (this->SoundVolumeText); }

	/* Get for CurrentQualityValue */
	int32 GetCurrentQualityValue() const { return (this->CurrentQualityValue); }
	
	/**
	 * Increment and Decrement for ScreenSize
	 * @param IsLeft - Defines the walking direction
	 * @return screen size in FIntPoint
	 */
	FIntPoint FindScreenSizeToLeftOnRight(bool IsLeft);

	/**
	 * Increment and Decrement for Quality
	 * @param IsLeft - Defines the walking direction
	 * @return Quality in int32
	 */
	int32 ChangeQualityToLeftOnRight(bool IsLeft);

protected:

	virtual void OnStart() override;
	virtual void Init() override;
	
private:
	EWindowMode::Type CurrentWindowMode;
	FIntPoint CurrentScreen;
	FString CurrentLanguage;
	int32 CurrentQualityValue;
	TArray <FIntPoint> ArrayWindowedScreenSize;
	TArray <FIntPoint> ArrayFullScreenSize;
	TArray<FIntPoint> CurrentArrayScreenSize;

	//Music and Sound classes
	float MusicVolumeValue;
	float SoundVolumeValue;
	FText MusicVolumeText;
	FText SoundVolumeText;


};
