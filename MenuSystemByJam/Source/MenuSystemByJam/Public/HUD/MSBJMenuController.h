// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MSBJMenuController.generated.h"

/**
 * 
 */
UCLASS()
class MENUSYSTEMBYJAM_API AMSBJMenuController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
};
