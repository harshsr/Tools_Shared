// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DeveloperSettings.h"
#include "NamingConventionSettings.generated.h"


USTRUCT()
struct FClassNameSettings
{
	GENERATED_BODY()

public:

	// The name of the class to apply naming convention
	UPROPERTY(config, EditAnywhere)
	FString ClassName;

	// The prefix to use
	UPROPERTY(config, EditAnywhere)
	FString Prefix;

	// The suffix to use
	UPROPERTY(config, EditAnywhere)
	FString Suffix;
	
};

UCLASS(Config = Engine, defaultconfig, meta = (DisplayName = "Naming Convention"))
class TOOLSCOLLECTION_API UNamingConventionSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	// List of class names and their prefixes and suffixes
	UPROPERTY(config, EditAnywhere)
	TArray<FClassNameSettings> ClassNamesSettings;

	// Settings retrieved from the project settings
	static UNamingConventionSettings const* Settings;

	void ResetToDefault();

	UNamingConventionSettings();
	
};
