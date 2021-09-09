/*
 * By Mark Veligod
 * Company Name: VeligodStudio
 * GitHub: https://github.com/markveligod
 * Itch: https://veligodstudio.itch.io/
 * Contact: markveligod@yandex.ru
 */

#include "Menu/MSBJGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogMSBJGameInstance, All, All);

void UMSBJGameInstance::OnStart()
{
    Super::OnStart();
    checkf(this->MusicMenuClass, TEXT("Music is null pointer"));
    checkf(this->SoundMenuClass, TEXT("Sound is null pointer"));
}

void UMSBJGameInstance::Init()
{
    Super::Init();
    this->CurrentQualityValue = 4;

    this->SetCurrentWindowMode(EWindowMode::Fullscreen);
    UE_LOG(LogMSBJGameInstance, Display, TEXT("Default Window Mode: Fullscreen type"))

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

    if (!UKismetSystemLibrary::GetConvenientWindowedResolutions(this->ArrayWindowedScreenSize))
        UE_LOG(LogMSBJGameInstance, Error, TEXT("Array Windowed screen size is null [system error]"));

    for (int32 i = 0; i < this->ArrayWindowedScreenSize.Num(); i++)
        UE_LOG(LogMSBJGameInstance, Display, TEXT("#%d Windowed Screen Size: %d - %d"), i, this->ArrayWindowedScreenSize[i].X,
            this->ArrayWindowedScreenSize[i].Y);

    if (!UKismetSystemLibrary::GetSupportedFullscreenResolutions(this->ArrayFullScreenSize))
        UE_LOG(LogMSBJGameInstance, Error, TEXT("Array Full screen size is null [system error]"));

    for (int32 i = 0; i < this->ArrayFullScreenSize.Num(); i++)
        UE_LOG(LogMSBJGameInstance, Display, TEXT("#%d Full Screen Size: %d - %d"), i, this->ArrayFullScreenSize[i].X,
            this->ArrayFullScreenSize[i].Y);

    this->CurrentArrayScreenSize = this->ArrayFullScreenSize;
    this->CurrentScreen = this->CurrentArrayScreenSize[this->CurrentArrayScreenSize.Num() - 1];
}

FIntPoint UMSBJGameInstance::FindScreenSizeToLeftOnRight(bool IsLeft)
{
    int32 TempIndex;
    FIntPoint ReturnRes;
    if (this->CurrentArrayScreenSize.Find(this->CurrentScreen, TempIndex))
    {
        if (IsLeft)
        {
            ReturnRes = (TempIndex == 0) ? this->CurrentArrayScreenSize[this->CurrentArrayScreenSize.Num() - 1]
                                         : this->CurrentArrayScreenSize[TempIndex - 1];
            this->CurrentScreen = ReturnRes;
        }
        else
        {
            ReturnRes = (TempIndex == (this->CurrentArrayScreenSize.Num() - 1)) ? this->CurrentArrayScreenSize[0]
                                                                                : this->CurrentArrayScreenSize[TempIndex + 1];
            this->CurrentScreen = ReturnRes;
        }
    }
    return (ReturnRes);
}

int32 UMSBJGameInstance::ChangeQualityToLeftOnRight(bool IsLeft)
{
    int32 Result;
    if (IsLeft)
    {
        Result = (this->CurrentQualityValue == 0) ? this->CurrentQualityValue = 4 : --this->CurrentQualityValue;
    }
    else
    {
        Result = (this->CurrentQualityValue == 4) ? this->CurrentQualityValue = 0 : ++this->CurrentQualityValue;
    }
    return (Result);
}
