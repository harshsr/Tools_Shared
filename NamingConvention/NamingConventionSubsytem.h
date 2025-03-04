// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "NamingConventionSubsytem.generated.h"

UCLASS()
class TOOLSCOLLECTION_API UNamingConventionSubsytem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	TArray<FAssetData> CachedSelectedAssets;
	TArray<FString> CachedSelectedFolders; 

	bool IsPrefixSpecified(const FString& Prefix);
	FString GetSuffix(UObject* Asset);
	FString GetSuffixByClassName(FString ClassName);
	void ApplyNamingConvention();
	void AddContentBrowserExtension();
	TSharedRef<FExtender> OnExtendContentBrowserMenu(const TArray<FAssetData>& SelectedAssets);
	TSharedRef<FExtender> OnExtendPathViewMenu(const TArray<FString>& SelectedFolders);

	FString GetPrefixByClassName(FString ClassName);
	FString GetPrefix(UObject* Asset);
	
};
