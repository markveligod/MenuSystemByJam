/*
 * By Mark Veligod
 * Company Name: VeligodStudio
 * GitHub: https://github.com/markveligod
 * Itch: https://veligodstudio.itch.io/
 * Contact: markveligod@yandex.ru
 */

#include "Menu/Public/MSBJGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogMSBJGameInstance, All, All);

void UMSBJGameInstance::OnStart()
{
	Super::OnStart();

	this->SetCurrentWindowMode(EWindowMode::Fullscreen);
	UE_LOG(LogMSBJGameInstance, Display, TEXT("Default Window Mode: Fullscreen type"))
	
	if (!UKismetSystemLibrary::GetConvenientWindowedResolutions(this->ArrayScreenSize))
		UE_LOG(LogMSBJGameInstance, Error, TEXT("Array screen size is null [system error]"));
	
	this->CurrentScreen = this->ArrayScreenSize[0];
	UE_LOG(LogMSBJGameInstance, Display, TEXT("Default Screen Size: %d - %d"), this->CurrentScreen.X, this->CurrentScreen.Y);

	this->CurrentLanguage = UKismetSystemLibrary::GetDefaultLanguage();
	UE_LOG(LogMSBJGameInstance, Display, TEXT("Default Language: %s"), *this->CurrentLanguage);
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

FString UMSBJGameInstance::GetCurrentLanguage() const
{
	return (this->CurrentLanguage);
}

void UMSBJGameInstance::SetCurrentLanguage(FString NewLang)
{
	this->CurrentLanguage = NewLang;
}

TArray<FIntPoint> UMSBJGameInstance::GetArrayScreenSize() const
{
	return (this->ArrayScreenSize);
}
