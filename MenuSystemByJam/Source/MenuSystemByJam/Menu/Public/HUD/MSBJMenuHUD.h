/*
 * By Mark Veligod
 * Company Name: VeligodStudio
 * GitHub: https://github.com/markveligod
 * Itch: https://veligodstudio.itch.io/
 * Contact: markveligod@yandex.ru
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Menu/Public/MSBJDataTypes.h"
#include "MSBJMenuHUD.generated.h"

class UMSBJBaseWidget;
/**
 * 
 */
UCLASS()
class MENUSYSTEMBYJAM_API AMSBJMenuHUD : public AHUD
{
	GENERATED_BODY()

public:

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UMSBJBaseWidget> WelcomeHudWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UMSBJBaseWidget> MenuHudWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UMSBJBaseWidget> OptionsHudWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UMSBJBaseWidget> CreditsHudWidgetClass;

	virtual void BeginPlay() override;
private:
	UPROPERTY()
		TMap<EMSBJGameMenuState, UMSBJBaseWidget*> GameWidgets;

	UPROPERTY()
		UMSBJBaseWidget* CurrentWidget = nullptr;

	void OnGameStateChanged(EMSBJGameMenuState NewState);
};
