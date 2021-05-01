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

	EWindowMode::Type GetCurrentWindowMode() const;
	void SetCurrentWindowMode(EWindowMode::Type NewType);
	
	FIntPoint GetScreenViewport() const;
	void SetScreenViewport(FIntPoint NewScreen);

	void RunCurrentUserSettings();

private:
	EWindowMode::Type CurrentWindowMode = EWindowMode::Fullscreen;
	FIntPoint CurrentScreen;
	FString CurrentLanguage;
	TArray <FIntPoint> ArrayScreenSize;

	UGameUserSettings* UserSettings;

	void StartDefaultWindowMode();
	void StartDefaultLanguage();
	void StartDefaultScreenSize();

	void RunCurrentWindow();
	void RunCurrentLanguage();
	void RunCurrentScreenSize();
};
