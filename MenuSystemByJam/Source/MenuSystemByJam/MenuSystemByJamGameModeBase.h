// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MSBJDataTypes.h"
#include "MenuSystemByJamGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MENUSYSTEMBYJAM_API AMenuSystemByJamGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	FOnGameMenuStateChangedSignature OnGameMenuStateChangedSignature;

	AMenuSystemByJamGameModeBase();
	
	virtual void StartPlay() override;
	const EMSBJGameMenuState& GetCurrentState() const;
	void SetGameState(EMSBJGameMenuState NewState);

protected:
	
private:
	EMSBJGameMenuState CurrentState = EMSBJGameMenuState::InProgress;
};
