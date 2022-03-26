/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://markveligod.itch.io/
 **/

#include "JamMSGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Library/JamMSFunctionLibrary.h"

void UJamMSGameInstance::OnStart()
{
    Super::OnStart();
}

void UJamMSGameInstance::Init()
{
    Super::Init();

    this->MusicMenuClass->Properties.Volume = this->DefaultMusicVolumeValue / VALUE_PERCENT;
    LOGJAM(ELogVerb::Display, FString::Printf(TEXT("Setup default music volume: %f"),
        this->MusicMenuClass->Properties.Volume));
    this->SoundMenuClass->Properties.Volume = this->DefaultSoundVolumeValue / VALUE_PERCENT;
    LOGJAM(ELogVerb::Display, FString::Printf(TEXT("Setup default sound volume: %f"),
            this->SoundMenuClass->Properties.Volume));
    
    UKismetSystemLibrary::GetConvenientWindowedResolutions(this->ArrayWindowedScreenSize);
    LOGJAM(ELogVerb::Display, "---| Available screen resolutions |---");
    for (const auto Point : this->ArrayWindowedScreenSize)
    {
        LOGJAM(ELogVerb::Display, FString::Printf(TEXT("Screen: %s"), *Point.ToString()));
    }

    if (this->ArrayWindowedScreenSize.Num() > 0)
    {
        this->SelectedScreenSize = this->ArrayWindowedScreenSize[0];
        LOGJAM(ELogVerb::Display, FString::Printf(TEXT("Selected default screen size: %s"),
            *UJamMSFunctionLibrary::GetStringSizeScreen(this->SelectedScreenSize)));
    }

    
}
