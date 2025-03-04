// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GlobalEventSubsystem.h"
#include "GlobalEventsFunctionsLib.generated.h"

/**
 * 
 */
UCLASS()
class TOOLSCOLLECTION_API UGlobalEventsFunctionsLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Bind a listener Object to a Global Event
	UFUNCTION(BlueprintCallable, Category = "Global Events", meta = (DefaultToSelf = "Listener", HidePin = "Listener"))
	static void BindGlobalEvent(UObject* Listener, UGlobalEventID* EventIdentifier, const FGlobalEventCallback& Callback);

	UFUNCTION(BlueprintCallable, Category = "Global Events")
	static TArray<UObject*> GetGlobalEventListeners(UGlobalEventID* EventIdentifier);

	// Unbind a Global Event
	UFUNCTION(BlueprintCallable, Category = "Global Events")
	static void UnbindGlobalEvent(const FGlobalEventCallback& Event, UGlobalEventID* EventIdentifier);

	// Unbind all Global Events of a listener Object
	UFUNCTION(BlueprintCallable, Category = "Global Events")
	static void UnbindAllGlobalEvents(UObject* Listener, UGlobalEventID* EventIdentifier);

	// Try to call a Global Event from a listener Object
	UFUNCTION(BlueprintCallable, Category = "Global Events", meta = (DefaultToSelf = "Dispatcher", HidePin = "Dispatcher"))
	static void CallGlobalEvent(UObject* Dispatcher, UGlobalEventID* EventIdentifier, FDynamicData DynamicData);

protected:
	static UGlobalEventSubsystem* GlobalEventsSubsystem()
	{
		if (
			GEngine->GameViewport
			&&
			GEngine->GameViewport->GetWorld()
			&&
			GEngine->GameViewport->GetWorld()->GetGameInstance()
			&&
			GEngine->GameViewport->GetWorld()->GetGameInstance()->GetSubsystem<UGlobalEventSubsystem>()
		) {
			return GEngine->GameViewport->GetWorld()->GetGameInstance()->GetSubsystem<UGlobalEventSubsystem>();
		}
		
		return nullptr;
	}
	
};
