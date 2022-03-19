/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://markveligod.itch.io/
 **/

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "JamMSGameInstance.generated.h"

/**
 * @class The main class for storing intermediate data between levels
 */
UCLASS()
class JAMMENUSYSTEM_API UJamMSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

    // Singleton
    UFUNCTION(BlueprintCallable, Category = "UJamMSGameInstance|Singleton")
    static UJamMSGameInstance* Get(UWorld* World) { return (World) ? Cast<UJamMSGameInstance>(World->GetGameInstance()) : nullptr; }
    
#pragma region GetData
    
    /**
     * @public Getting name menu level
     * @return FName
     **/
    UFUNCTION(BlueprintPure, Category = "UJamMSGameInstance|GetData")
    FORCEINLINE FName GetNameMenuLevel() const { return this->NameMenuLevel; }

    /**
     * @public Getting name start level
     * @return FName
     **/
    UFUNCTION(BlueprintPure, Category = "UJamMSGameInstance|GetData")
    FORCEINLINE FName GetNameStartLevel() const { return this->NameStartLevel; }

    /**
     * @public Getting Music Menu Class
     * @return USoundClass*
     **/
    UFUNCTION(BlueprintPure, Category = "UJamMSGameInstance|GetData")
    FORCEINLINE USoundClass* GetMusicMenuClass() const { return this->MusicMenuClass; }

    /**
     * @public Getting Sound Menu Class
     * @return USoundClass*
     **/
    UFUNCTION(BlueprintPure, Category = "UJamMSGameInstance|GetData")
    FORCEINLINE USoundClass* GetSoundMenuClass() const { return this->SoundMenuClass; }

    /**
     * @public Getting Default Music Volume Value
     * @return float
     **/
    UFUNCTION(BlueprintPure, Category = "UJamMSGameInstance|GetData")
    FORCEINLINE float GetDefaultMusicVolumeValue() const { return this->DefaultMusicVolumeValue; }

    /**
     * @public Getting Default Sound Volume Value
     * @return float
     **/
    UFUNCTION(BlueprintPure, Category = "UJamMSGameInstance|GetData")
    FORCEINLINE float GetDefaultSoundVolumeValue() const { return this->DefaultSoundVolumeValue; }
    
#pragma endregion

#pragma region SetData
#pragma endregion

protected:
    /** Called when the game instance is started either normally or through PIE. */
    virtual void OnStart() override;
    /** virtual function to allow custom GameInstances an opportunity to set up what it needs */
    virtual void Init() override;
    
private:
    /* level names for interaction from other classes */
    
    UPROPERTY(EditDefaultsOnly, Category = "Levels Editor")
    FName NameStartLevel = NAME_None;
    UPROPERTY(EditDefaultsOnly, Category = "Levels Editor")
    FName NameMenuLevel = NAME_None;

    /* Volume editor for sound classes */
    
    UPROPERTY(EditDefaultsOnly, Category = "Volume Editor")
    USoundClass* MusicMenuClass;
    UPROPERTY(EditDefaultsOnly, Category = "Volume Editor", meta = (ClampMin = "0.0", ClampMax = "100.0"))
    float DefaultMusicVolumeValue = 50.f;
    UPROPERTY(EditDefaultsOnly, Category = "Volume Editor")
    USoundClass* SoundMenuClass;
    UPROPERTY(EditDefaultsOnly, Category = "Volume Editor", meta = (ClampMin = "0.0", ClampMax = "100.0"))
    float DefaultSoundVolumeValue = 50.f;
};
