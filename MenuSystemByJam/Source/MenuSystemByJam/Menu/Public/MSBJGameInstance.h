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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Levels Editor")
		FName NameStartLevel = NAME_None;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Levels Editor")
		FName NameMenuLevel = NAME_None;

	virtual void OnStart() override;

	EWindowMode::Type GetCurrentWindowMode() const { return (this->CurrentWindowMode); }
	void SetCurrentWindowMode(EWindowMode::Type NewType) { this->CurrentWindowMode = NewType; }
	
	FIntPoint GetScreenViewport() const { return (this->CurrentScreen); }
	void SetScreenViewport(FIntPoint NewScreen) { this->CurrentScreen = NewScreen; }

	FString GetCurrentLanguage() const { return (this->CurrentLanguage); }
	void SetCurrentLanguage(FString NewLang) { this->CurrentLanguage = NewLang; }

	TArray <FIntPoint> GetArrayCurrentScreenSize() const { return (this->CurrentArrayScreenSize); }

	void ChangeArrayScreenSize(bool State) { this->CurrentArrayScreenSize = (State == true) ? this->ArrayFullScreenSize : this->ArrayWindowedScreenSize; this->CurrentScreen = this->CurrentArrayScreenSize[this->CurrentArrayScreenSize.Num() - 1]; }
	
	void SetMusicVolumeValue(float NewValue) { this->MusicVolumeValue = NewValue; }
	float GetMusicVolumeValue() const { return (this->MusicVolumeValue); }

	void SetSoundVolumeValue(float NewValue) { this->SoundVolumeValue = NewValue; }
	float GetSoundVolumeValue() const { return (this->SoundVolumeValue); }

	void SetMusicVolumeText(FText NewText) { this->MusicVolumeText = NewText; }
	FText GetMusicVolumeText() const { return (this->MusicVolumeText); }
	
	void SetSoundVolumeText(FText NewText) { this->SoundVolumeText = NewText; }
	FText GetSoundVolumeText() const { return (this->SoundVolumeText); }

	FIntPoint FindScreenSizeToLeftOnRight(bool IsLeft);

	int32 ChangeQualityToLeftOnRight(bool IsLeft);

	int32 GetCurrentQualityValue() const { return (this->CurrentQualityValue); }
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Volume Editor", meta = (ClampMin = "0.0", ClampMax = "100.0"))
		float DefaultMusicVolumeValue = 50.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Volume Editor", meta = (ClampMin = "0.0", ClampMax = "100.0"))
		float DefaultSoundVolumeValue = 50.f;
	
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
