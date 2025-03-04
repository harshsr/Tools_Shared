// Fill out your copyright notice in the Description page of Project Settings.


#include "NamingConvention/NamingConventionSubsytem.h"

#include "AssetToolsModule.h"
#include "ContentBrowserModule.h"
#include "IAssetTools.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "GameFramework/Character.h"
#include "GameFramework/GameModeBase.h"
#include "NamingConvention/NamingConventionSettings.h"

void UNamingConventionSubsytem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	AddContentBrowserExtension();

	// Retrieve settings
	UNamingConventionSettings::Settings = GetDefault<UNamingConventionSettings>();
}

void UNamingConventionSubsytem::Deinitialize()
{
	Super::Deinitialize();
}

void UNamingConventionSubsytem::AddContentBrowserExtension()
{
	if (FModuleManager::Get().IsModuleLoaded("ContentBrowser"))
	{
		FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(
			"ContentBrowser");

		// Extend the Asset View context menu (for assets)
		TArray<FContentBrowserMenuExtender_SelectedAssets>& AssetExtenders = ContentBrowserModule.
			GetAllAssetViewContextMenuExtenders();
		AssetExtenders.Add(
			FContentBrowserMenuExtender_SelectedAssets::CreateUObject(
				this, &UNamingConventionSubsytem::OnExtendContentBrowserMenu));

		// Extend the Path View context menu (for folders)
		TArray<FContentBrowserMenuExtender_SelectedPaths>& PathExtenders = ContentBrowserModule.
			GetAllPathViewContextMenuExtenders();
		PathExtenders.Add(
			FContentBrowserMenuExtender_SelectedPaths::CreateUObject(
				this, &UNamingConventionSubsytem::OnExtendPathViewMenu));
	}
}

TSharedRef<FExtender> UNamingConventionSubsytem::OnExtendContentBrowserMenu(const TArray<FAssetData>& SelectedAssets)
{
	CachedSelectedAssets = SelectedAssets; // Store the selected assets
	CachedSelectedFolders.Empty(); // Clear any previously stored folders

	TSharedRef<FExtender> Extender = MakeShareable(new FExtender());

	Extender->AddMenuExtension(
		"CommonAssetActions",
		EExtensionHook::After,
		nullptr,
		FMenuExtensionDelegate::CreateLambda([this](FMenuBuilder& MenuBuilder)
		{
			MenuBuilder.AddMenuEntry(
				FText::FromString("Apply Naming Convention"),
				FText::FromString("Apply the naming convention to selected assets."),
				FSlateIcon(),
				FUIAction(FExecuteAction::CreateUObject(this, &UNamingConventionSubsytem::ApplyNamingConvention))
			);
		})
	);

	return Extender;
}

// Extend Path View Menu (when folders are selected)
TSharedRef<FExtender> UNamingConventionSubsytem::OnExtendPathViewMenu(const TArray<FString>& SelectedFolders)
{
	CachedSelectedFolders = SelectedFolders; // Store folder paths
	CachedSelectedAssets.Empty();            // Clear any previously stored assets

	if (SelectedFolders.Num() > 0)
	{
		FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

		for (const FString& Folder : SelectedFolders)
		{
			FARFilter Filter;
			Filter.PackagePaths.Add(*Folder);
			Filter.bRecursivePaths = true; // Fetch assets recursively inside subfolders

			TArray<FAssetData> FoundAssets;
			AssetRegistryModule.Get().GetAssets(Filter, FoundAssets);

			// Add found assets to CachedSelectedAssets
			CachedSelectedAssets.Append(FoundAssets);
		}
	}


	TSharedRef<FExtender> Extender = MakeShareable(new FExtender());

	Extender->AddMenuExtension(
		"PathViewFolderOptions",
		EExtensionHook::After,
		nullptr,
		FMenuExtensionDelegate::CreateLambda([this](FMenuBuilder& MenuBuilder)
		{
			MenuBuilder.AddMenuEntry(
				FText::FromString("Apply Naming Convention"),
				FText::FromString("Apply the naming convention to assets in selected folders."),
				FSlateIcon(),
				FUIAction(FExecuteAction::CreateUObject(this, &UNamingConventionSubsytem::ApplyNamingConvention))
			);
		})
	);

	return Extender;
}



void UNamingConventionSubsytem::ApplyNamingConvention()
{
	TArray<FAssetRenameData> RenameDatas = TArray<FAssetRenameData>();
	for (FAssetData Asset : CachedSelectedAssets)
	{
		const FString PackagePath = FPackageName::GetLongPackagePath(Asset.GetSoftObjectPath().GetAssetPath().ToString());

		FString NewName;
		bool bRename = false;
		FString Prefix = GetPrefix(Asset.GetAsset());
		
		if (Prefix != "")
		{
			bool bExistingPrefix = false;
			FString NameRemainder;
			// If the asset name possibly contains a prefix ("_" character)
			if (Asset.AssetName.ToString().Contains("_"))
			{
				FString ExistingPrefix;
				Asset.AssetName.ToString().Split("_", &ExistingPrefix, &NameRemainder);
				
				NameRemainder[0] = FChar::ToUpper(NameRemainder[0]);
				
				// Make sure it's a prefix and not just a name with a "_" character
				bExistingPrefix = ExistingPrefix.Len() <= 5 || IsPrefixSpecified(ExistingPrefix + "_");	
			}

			// If the asset name contains a prefix
			if (bExistingPrefix)
			{
				// if it's not the same prefix
				if (!Asset.AssetName.ToString().StartsWith(Prefix))
				{
					NewName = Prefix + NameRemainder;
					bRename = true;
				}
			}
			
			else
			{
				NewName = Asset.AssetName.ToString();
				NewName[0] = FChar::ToUpper(NewName[0]);
				NewName = Prefix + NewName;
				bRename = true;
			}
		}

		// If no prefix was added, prepare for suffix
		if (!bRename)
		{
			NewName = Asset.AssetName.ToString();
			NewName[0] = FChar::ToUpper(NewName[0]);
		}

		FString Suffix = GetSuffix(Asset.GetAsset());
		if (Suffix != "")
		{
			// If the Asset does not have the same suffix already
			if (!Asset.AssetName.ToString().EndsWith(Suffix))
			{
				NewName = NewName + Suffix;
				bRename = true;
			}
		}

		// If a new name has been defined for the asset
		if (bRename)
		{
			// Add this asset to the array of assets to rename
			FAssetRenameData RenameData = FAssetRenameData(Asset.GetAsset(), PackagePath, NewName);
			RenameDatas.Add(RenameData);
		}
	}

	// Rename all the assets we changed the name of
	FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
	AssetToolsModule.Get().RenameAssets(RenameDatas);
}

FString UNamingConventionSubsytem::GetPrefix(UObject* Asset)
{
	FString ClassName = Asset->GetClass()->GetName();
	FString Prefix = "";

	for (FClassNameSettings ClassNameSettings : UNamingConventionSettings::Settings->ClassNamesSettings)
	{
		if (ClassNameSettings.ClassName == ClassName)
		{
			Prefix = ClassNameSettings.Prefix;
			break;
		}
	}

	FString SpecialPrefix = "";
	// Check special cases for Blueprints
	if (ClassName == "Blueprint")
	{
		// switch on the blueprint type
		UBlueprint* Blueprint = Cast<UBlueprint>(Asset);
		switch (Blueprint->BlueprintType)
		{
			case BPTYPE_Interface :
				SpecialPrefix = GetPrefixByClassName("BlueprintInterface");
				break;

			case  BPTYPE_MacroLibrary :
				SpecialPrefix = GetPrefixByClassName("BlueprintMacroLibrary");
				break;

			case BPTYPE_FunctionLibrary :
				SpecialPrefix = GetPrefixByClassName("BlueprintFunctionLibrary");
				break;
		}
	}

	if (SpecialPrefix != "")
	{
		return SpecialPrefix;
	}
	else if (Prefix != "")
	{
		return Prefix;
	}
	else
	{
		// for assets like textures, classnames are not the same as the asset name
		for (FClassNameSettings ClassNameSetting : UNamingConventionSettings::Settings->ClassNamesSettings)
		{
			if (ClassName.Contains(ClassNameSetting.ClassName))
			{
				return ClassNameSetting.Prefix;
			}
		}
		return "";
	}
}

FString UNamingConventionSubsytem::GetPrefixByClassName(FString ClassName)
{
	for (FClassNameSettings ClassNameToPrefix : UNamingConventionSettings::Settings->ClassNamesSettings)
	{
		if (ClassNameToPrefix.ClassName == ClassName)
		{
			return ClassNameToPrefix.Prefix;
		}
	}
	return "";
}

bool UNamingConventionSubsytem::IsPrefixSpecified(const FString& Prefix)
{
	for (FClassNameSettings ClassNameToPrefix : UNamingConventionSettings::Settings->ClassNamesSettings)
	{
		if (Prefix == ClassNameToPrefix.Prefix)
		{
			return true;
		}
	}
	return false;
}

FString UNamingConventionSubsytem::GetSuffix(UObject* Asset)
{
	FString ClassName = Asset->GetClass()->GetName();
	FString Suffix = "";

	for (FClassNameSettings ClassNameSettings : UNamingConventionSettings::Settings->ClassNamesSettings)
	{
		if (ClassNameSettings.ClassName == ClassName)
		{
			Suffix = ClassNameSettings.Suffix;
			if (Suffix != "")
			{
				break;
			}
		}

		if (ClassName == "Blueprint")
		{
			// sub-classes of Blueprints

			UBlueprint* BlueprintAsset = Cast<UBlueprint>(Asset);
			UClass* ParentClass = BlueprintAsset->GeneratedClass;

			// character
			if (ParentClass->IsChildOf(ACharacter::StaticClass()))
			{
				ClassName = "Character";
				Suffix = GetSuffixByClassName(ClassName);
				break;
			}
			
			// pawn
			if (ParentClass->IsChildOf(APawn::StaticClass()))
			{
				ClassName = "Pawn";
				Suffix = GetSuffixByClassName(ClassName);
				break;
			}

			// GameModeBase
			if (ParentClass->IsChildOf(AGameModeBase::StaticClass()))
			{
				ClassName = "GameModeBase";
				Suffix = GetSuffixByClassName(ClassName);
				break;
			}

			// PlayerController
			if (ParentClass->IsChildOf(APlayerController::StaticClass()))
			{
				ClassName = "PlayerController";
				Suffix = GetSuffixByClassName(ClassName);
				break;
			}
		}
	}

	return Suffix;
}

FString UNamingConventionSubsytem::GetSuffixByClassName(FString ClassName)
{
	for (FClassNameSettings ClassNameToPrefix : UNamingConventionSettings::Settings->ClassNamesSettings)
	{
		if (ClassNameToPrefix.ClassName == ClassName)
		{
			return ClassNameToPrefix.Suffix;
		}
	}
	return "";
}




