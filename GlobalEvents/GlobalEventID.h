// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GlobalEventID.generated.h"

/**
 * 
 */
UCLASS()
class TOOLSCOLLECTION_API UGlobalEventID : public UDataAsset
{
	GENERATED_BODY()

public:
	FString GetHash()
	{
		return GetName();
	}
};
