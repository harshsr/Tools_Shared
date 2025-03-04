// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalEvents/GlobalEventsFunctionsLib.h"

void UGlobalEventsFunctionsLib::BindGlobalEvent(UObject* Listener, UGlobalEventID* EventIdentifier, const FGlobalEventCallback& Callback)
{
	if (GlobalEventsSubsystem())
	{
		GlobalEventsSubsystem()->BindGlobalEvent(Listener, EventIdentifier, Callback);
	}
}

TArray<UObject*> UGlobalEventsFunctionsLib::GetGlobalEventListeners(UGlobalEventID* EventIdentifier)
{
	if (GlobalEventsSubsystem())
	{
		return GlobalEventsSubsystem()->GetGlobalEventListeners(EventIdentifier);
	}

	return TArray<UObject*>();
}

void UGlobalEventsFunctionsLib::UnbindGlobalEvent(const FGlobalEventCallback& Event, UGlobalEventID* EventIdentifier)
{
	if (GlobalEventsSubsystem())
	{
		GlobalEventsSubsystem()->UnbindGlobalEvent(Event, EventIdentifier);
	}
}

void UGlobalEventsFunctionsLib::UnbindAllGlobalEvents(UObject* Listener, UGlobalEventID* EventIdentifier)
{
	if (GlobalEventsSubsystem())
	{
		GlobalEventsSubsystem()->UnbindAllGlobalEvents(Listener, EventIdentifier);
	}
}

void UGlobalEventsFunctionsLib::CallGlobalEvent(UObject* Dispatcher, UGlobalEventID* EventIdentifier, FDynamicData DynamicData)
{
	if (GlobalEventsSubsystem())
	{
		GlobalEventsSubsystem()->CallGlobalEvent(Dispatcher, EventIdentifier, DynamicData);
	}
}