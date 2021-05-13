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
	
	if (!UKismetSystemLibrary::GetConvenientWindowedResolutions(this->ArrayWindowedScreenSize))
		UE_LOG(LogMSBJGameInstance, Error, TEXT("Array Windowed screen size is null [system error]"));
	
	for (int32 i = 0; i < this->ArrayWindowedScreenSize.Num(); i++)
		UE_LOG(LogMSBJGameInstance, Display, TEXT("#%d Windowed Screen Size: %d - %d"), i, this->ArrayWindowedScreenSize[i].X, this->ArrayWindowedScreenSize[i].Y);

	if (!UKismetSystemLibrary::GetSupportedFullscreenResolutions(this->ArrayFullScreenSize))
		UE_LOG(LogMSBJGameInstance, Error, TEXT("Array Full screen size is null [system error]"));

	for (int32 i = 0; i < this->ArrayFullScreenSize.Num(); i++)
		UE_LOG(LogMSBJGameInstance, Display, TEXT("#%d Full Screen Size: %d - %d"), i, this->ArrayFullScreenSize[i].X, this->ArrayFullScreenSize[i].Y);

	this->CurrentScreen = this->ArrayFullScreenSize[this->ArrayFullScreenSize.Num() - 1];
	
	this->CurrentLanguage = UKismetSystemLibrary::GetDefaultLanguage();
	UE_LOG(LogMSBJGameInstance, Display, TEXT("Default Language: %s"), *this->CurrentLanguage);

	this->SetMusicVolumeValue(this->DefaultMusicVolumeValue);
	UE_LOG(LogMSBJGameInstance, Display, TEXT("Music Value: %f "), this->MusicVolumeValue);
	
	this->SetSoundVolumeValue(this->DefaultSoundVolumeValue);
	UE_LOG(LogMSBJGameInstance, Display, TEXT("Sound Value: %f "), this->SoundVolumeValue);
	
	this->SetMusicVolumeText(FText::FromString(FString::FromInt(int32(this->DefaultMusicVolumeValue))));
	UE_LOG(LogMSBJGameInstance, Display, TEXT("Music Text: %s "), *this->MusicVolumeText.ToString());

	this->SetSoundVolumeText(FText::FromString(FString::FromInt(int32(this->DefaultSoundVolumeValue))));
	UE_LOG(LogMSBJGameInstance, Display, TEXT("Sound Text: %s "), *this->SoundVolumeText.ToString());

}
