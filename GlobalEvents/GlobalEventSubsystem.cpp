// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalEvents/GlobalEventSubsystem.h"


void UGlobalEventSubsystem::BindGlobalEvent(UObject* Listener, UGlobalEventID* EventIdentifier, const FGlobalEventCallback& Callback)
{
	GlobalEventMap.FindOrAdd(EventIdentifier).AddUnique(Callback);
}

TArray<UObject*> UGlobalEventSubsystem::GetGlobalEventListeners(UGlobalEventID* EventIdentifier) const
{
	// Get all objects linked to the multicast
	if (GlobalEventMap.Contains(EventIdentifier))
	{
		return GlobalEventMap.Find(EventIdentifier)->GetAllObjects();
	}

	return TArray<UObject*>();
}

void UGlobalEventSubsystem::UnbindGlobalEvent(const FGlobalEventCallback& Event, UGlobalEventID* EventIdentifier)
{
	// Remove OnListenResponse from multicast linked to EventClass
	if (GlobalEventMap.Contains(EventIdentifier))
	{
		GlobalEventMap.Find(EventIdentifier)->Remove(Event);
	}
}

void UGlobalEventSubsystem::UnbindAllGlobalEvents(UObject* Listener, UGlobalEventID* EventIdentifier)
{
	// Remove all events linked to Unsubscriber from multicast linked to ClassToListen
	if (GlobalEventMap.Contains(EventIdentifier))
	{
		GlobalEventMap.Find(EventIdentifier)->RemoveAll(Listener);
	}
}

void UGlobalEventSubsystem::CallGlobalEvent(UObject* Dispatcher, UGlobalEventID* EventIdentifier, FDynamicData DynamicData)
{
	if (GlobalEventMap.Contains(EventIdentifier))
	{
		// Broadcast the multicast event found in the dictionary using the key
		GlobalEventMap.Find(EventIdentifier)->Broadcast(Dispatcher, DynamicData);
	}
}
