// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalEventID.h"
#include "StructUtils/InstancedStruct.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GlobalEventSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FDynamicData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UObject* Object;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Vector;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Value;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int IntValue;
};


// A delegate linked to a single event. Used to bind/unbind an event to a global multicast event.
DECLARE_DYNAMIC_DELEGATE_TwoParams(FGlobalEventCallback, UObject*, Listener, FDynamicData, DynamicData);

// A multicast delegate linked to many delegates. Used to call to every linked delegate associated to this multicast.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGlobalEventMulticast, UObject*, Dispatcher, FDynamicData, DynamicData);

UCLASS()
class TOOLSCOLLECTION_API UGlobalEventSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	// Map that stores the Global Events
	UPROPERTY()
	TMap<UGlobalEventID*, FGlobalEventMulticast> GlobalEventMap;

public:
	// Bind a listener Object to a Global Event
	UFUNCTION(BlueprintCallable, Category = "Global Events", meta = (DefaultToSelf = "Listener", HidePin = "Listener"))
	void BindGlobalEvent(UObject* Listener, UGlobalEventID* EventIdentifier, const FGlobalEventCallback& Callback);

	UFUNCTION(BlueprintCallable, Category = "Global Events")
	TArray<UObject*> GetGlobalEventListeners(UGlobalEventID* EventIdentifier) const;

	// Unbind a Global Event
	UFUNCTION(BlueprintCallable, Category = "Global Events")
	void UnbindGlobalEvent(const FGlobalEventCallback& Event, UGlobalEventID* EventIdentifier);

	// Unbind all Global Events of a listener Object
	UFUNCTION(BlueprintCallable, Category = "Global Events")
	void UnbindAllGlobalEvents(UObject* Listener, UGlobalEventID* EventIdentifier);

	// Try to call a Global Event from a listener Object
	UFUNCTION(BlueprintCallable, Category = "Global Events", meta = (DefaultToSelf = "Dispatcher", HidePin = "Dispatcher"))
	void CallGlobalEvent(UObject* Dispatcher, UGlobalEventID* EventIdentifier, FDynamicData DynamicData);
	
};
