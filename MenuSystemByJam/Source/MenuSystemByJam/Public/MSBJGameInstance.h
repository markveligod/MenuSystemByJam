// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MSBJGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MENUSYSTEMBYJAM_API UMSBJGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Levels Editor")
		FName NameStartLevel = NAME_None;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Levels Editor")
		FName NameMenuLevel = NAME_None;
};
