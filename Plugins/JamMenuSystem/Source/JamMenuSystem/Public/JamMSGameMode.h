/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://veligodstudio.itch.io/
 **/

#pragma once

#include "CoreMinimal.h"
#include "JamMSDataTypes.h"
#include "GameFramework/GameModeBase.h"
#include "JamMSGameMode.generated.h"

// Forward declare
class UJamMSGameInstance;

/**
 * @class Game mode for system menu and level menu
 */
UCLASS()
class JAMMENUSYSTEM_API AJamMSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

    // Construct default
    AJamMSGameMode();
    
    // Signature on change Menu State
    FOnMenuStateChangedSignature OnMenuStateChanged;

    /**
     * @public Change current menu state on new state
     * @param1 EJamMSMenuState
     **/
    UFUNCTION(BlueprintCallable, Category = "AJamMSGameMode|Action")
    void ChangeMenuState(EJamMSMenuState NewState);
    
protected:
    
    /** Overridable native event for when play begins for this actor. */
    virtual void BeginPlay() override;
    
private:
    // Current pointer on UJamMSGameInstance class
    UPROPERTY()
    UJamMSGameInstance* GameInstance;
    
    // Current pointer on UGameUserSettings class
    UPROPERTY()
    UGameUserSettings* UserSettings;

    // Current menu state in Menu Level
    EJamMSMenuState MenuState = EJamMSMenuState::WaitToStart;
};
