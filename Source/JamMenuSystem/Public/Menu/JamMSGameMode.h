/**
  * Maintain: Mark Veligod
  * GitHub: https://github.com/markveligod
  * Itch: https://markveligod.itch.io/
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
    
    // Singleton
    UFUNCTION(BlueprintCallable, Category = "AJamMSGameMode|Singleton")
    static AJamMSGameMode* Get(UWorld* World) { return (World) ? Cast<AJamMSGameMode>(World->GetAuthGameMode()) : nullptr; }
    
    // Signature on change Menu State
    UPROPERTY(BlueprintAssignable)
    FOnMenuStateChangedSignature OnMenuStateChanged;

    /**
     * @public Change current menu state on new state
     * @param1 EJamMSMenuState
     **/
    UFUNCTION(BlueprintCallable, Category = "AJamMSGameMode|Action")
    void ChangeMenuState(EJamMSMenuState NewState);

    /**
     * @public Change current menu state on new state for Timer
     * @param1 EJamMSMenuState
     * @param2 float
     **/
    UFUNCTION(BlueprintCallable, Category = "AJamMSGameMode|Action")
    void ChangeMenuStateTimer(EJamMSMenuState NewState, float RateTime);
    
#pragma region ExecCheat
    
    /**
     * @public @exec Change the status of displaying logs on the screen
     * @param1 EStateShowLog
     **/
    UFUNCTION(Exec, Category = "AJamMSGameMode|Exec")
    static void ChangeStateShowLog(const EStateShowLog NewState);
    
#pragma endregion 
    
protected:
    
    /** Overridable native event for when play begins for this actor. */
    virtual void BeginPlay() override;
    
private:
    // Current pointer on UJamMSGameInstance class
    UPROPERTY()
    UJamMSGameInstance* GameInst;
    
    // Current pointer on UGameUserSettings class
    UPROPERTY()
    UGameUserSettings* UserSettings;

    // Current menu state in Menu Level
    EJamMSMenuState MenuState = EJamMSMenuState::WaitToStart;

    
};
