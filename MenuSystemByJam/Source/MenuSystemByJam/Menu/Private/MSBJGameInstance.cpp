/*
 * By Mark Veligod
 * Company Name: VeligodStudio
 * GitHub: https://github.com/markveligod
 * Itch: https://veligodstudio.itch.io/
 * Contact: markveligod@yandex.ru
 */

#include "Menu/Public/MSBJGameInstance.h"
#include "Kismet/KismetInternationalizationLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/GameUserSettings.h"

DEFINE_LOG_CATEGORY_STATIC(LogMSBJGameInstance, All, All);

void UMSBJGameInstance::OnStart()
{
	Super::OnStart();

	this->UserSettings = UGameUserSettings::GetGameUserSettings();
	checkf(this->UserSettings, TEXT("User Settings is nullptr"));
	
	this->StartDefaultLanguage();
	this->StartDefaultWindowMode();
	this->StartDefaultScreenSize();
}

EWindowMode::Type UMSBJGameInstance::GetCurrentWindowMode() const
{
	return (this->CurrentWindowMode);
}

void UMSBJGameInstance::SetCurrentWindowMode(EWindowMode::Type NewType)
{
	this->CurrentWindowMode = NewType;
}

FIntPoint UMSBJGameInstance::GetScreenViewport() const
{
	return (this->CurrentScreen);
}

void UMSBJGameInstance::SetScreenViewport(FIntPoint NewScreen)
{
	this->CurrentScreen = NewScreen;
}

void UMSBJGameInstance::RunCurrentUserSettings()
{
	UE_LOG(LogMSBJGameInstance, Display, TEXT("X: %d = Y: %d"), this->CurrentScreen.X, this->CurrentScreen.Y);
	this->RunCurrentLanguage();
	//this->RunCurrentWindow();
	//this->RunCurrentScreenSize();
}

void UMSBJGameInstance::StartDefaultWindowMode()
{
	this->SetCurrentWindowMode(EWindowMode::Fullscreen);
}

void UMSBJGameInstance::StartDefaultLanguage()
{
	this->CurrentLanguage = UKismetSystemLibrary::GetDefaultLanguage();
}

void UMSBJGameInstance::StartDefaultScreenSize()
{
	if (!UKismetSystemLibrary::GetConvenientWindowedResolutions(this->ArrayScreenSize))
		UE_LOG(LogMSBJGameInstance, Error, TEXT("Array screen size is null [system error]"));

	this->CurrentScreen = this->ArrayScreenSize[0];
}

void UMSBJGameInstance::RunCurrentWindow()
{
	this->UserSettings->SetFullscreenMode(this->GetCurrentWindowMode());
	this->UserSettings->ApplySettings(false);
}

void UMSBJGameInstance::RunCurrentLanguage()
{
	if (this->CurrentLanguage == "ru-RU")
		UKismetInternationalizationLibrary::SetCurrentCulture(FString("ru-RU"), false);
	else
		UKismetInternationalizationLibrary::SetCurrentCulture(FString("en"), false);
}

void UMSBJGameInstance::RunCurrentScreenSize()
{
	this->UserSettings->SetScreenResolution(this->GetScreenViewport());
	this->UserSettings->ApplySettings(false);
}
