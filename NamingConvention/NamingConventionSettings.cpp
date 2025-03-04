// Fill out your copyright notice in the Description page of Project Settings.


#include "NamingConvention/NamingConventionSettings.h"

UNamingConventionSettings const* UNamingConventionSettings::Settings = nullptr;

UNamingConventionSettings::UNamingConventionSettings()
{
	ResetToDefault();
}

void UNamingConventionSettings::ResetToDefault()
{
	ClassNamesSettings = TArray<FClassNameSettings>();

	// Basic blueprint actors
	ClassNamesSettings.Add({ "Blueprint", "BP_", "" });
	ClassNamesSettings.Add({"Pawn", "", "_Pawn"});
	ClassNamesSettings.Add({"Character", "", "_Char"});
	ClassNamesSettings.Add({"GameModeBase", "", "_GM"});
	ClassNamesSettings.Add({"PlayerController", "", "_PC"});
	ClassNamesSettings.Add({"ActorComponent", "BPComp", ""});

	// Basics
	ClassNamesSettings.Add({ "BlueprintInterface", "BPI_", "" });
	ClassNamesSettings.Add({ "BlueprintFunctionLibrary", "BPL_", "" });
	ClassNamesSettings.Add({ "BlueprintMacroLibrary", "BPM_", "" });
	ClassNamesSettings.Add({ "UserDefinedStruct", "F", "" });
	ClassNamesSettings.Add({ "UserDefinedEnum", "E", "" });

	// Materials and textures
	ClassNamesSettings.Add({ "Texture", "T_", "" });
	ClassNamesSettings.Add({ "Material", "M_", "" });
	ClassNamesSettings.Add({ "MaterialInstanceConstant", "MIC_", "" });
	ClassNamesSettings.Add({ "MaterialFunction", "MF_", "" });
	ClassNamesSettings.Add({ "MaterialParameterCollection", "MPC_", "" });
	ClassNamesSettings.Add({ "PhysicalMaterial", "PhysMat_", "" });

	// Meshes
	ClassNamesSettings.Add({ "SkeletalMesh", "SK_", "" });
	ClassNamesSettings.Add({ "StaticMesh", "SM_", "" });
	ClassNamesSettings.Add({ "Skeleton", "SKEL_", "" });
	ClassNamesSettings.Add({ "PhysicsAsset", "PHYS_", "" });

	// AI
	ClassNamesSettings.Add({ "BehaviorTree", "BT_", "" });
	ClassNamesSettings.Add({ "BlackboardData", "BB_", "" });

	// Animation
	ClassNamesSettings.Add({ "AnimBlueprint", "ABP_", "" });
	ClassNamesSettings.Add({ "AnimSequence", "A_", "" });
	ClassNamesSettings.Add({ "BlendSpace", "BS_", "" });
	ClassNamesSettings.Add({ "AnimMontage", "AM_", "" });

	// Audio
	ClassNamesSettings.Add({ "SoundCue", "SC_", "" });
	ClassNamesSettings.Add({ "SoundWave", "S_", "" });
	ClassNamesSettings.Add({ "SoundClass", "S_", "" });

	// UI
	ClassNamesSettings.Add({ "WidgetBlueprint", "WBP_", "" });
	ClassNamesSettings.Add({ "UserWidget", "UW_", "" });

	// Particles
	ClassNamesSettings.Add({ "ParticleSystem", "P_", "" });
	ClassNamesSettings.Add({ "NiagaraEmitter", "NE_", "" });
	ClassNamesSettings.Add({ "NiagaraSystem", "NS_", "" });


	// Data
	ClassNamesSettings.Add({ "DataTable", "DT_", "" });
	ClassNamesSettings.Add({ "CurveFloat", "Curve_", "" });

	// Input
	ClassNamesSettings.Add({ "InputAction", "IA_", "" });
	ClassNamesSettings.Add({ "InputMappingContext", "IMC_", "" });

	// Media
	ClassNamesSettings.Add({ "ImgMediaSource", "MS_", "" });
	ClassNamesSettings.Add({ "MediaTexture", "MT_", "" });
	ClassNamesSettings.Add({ "MediaPlayer", "MP_", "" });
	
	
}

