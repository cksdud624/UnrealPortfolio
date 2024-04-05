// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "vector"

#include "MainCharacterMediator.generated.h"

using namespace std;

template<typename T>
class TFunctionFrame;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPORTFOLIO_API UMainCharacterMediator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMainCharacterMediator();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	TArray<TFunctionFrame<bool>*> AttackFrames;
public:
	void AttachEvent(TFunctionFrame<bool>* Event);
	void PlayEvent(const TFunctionFrame<bool>* Event, const bool Data);
	
};

template<typename T>
class TFunctionFrame
{
public:

	DECLARE_EVENT_OneParam(TFunctionFrame, FEvent, T);
	FEvent MainEvent;

	void PlayEvent(T Parameter)
	{
		MainEvent.Broadcast(Parameter);
	}
};
