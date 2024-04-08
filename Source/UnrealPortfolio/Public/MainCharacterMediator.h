// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

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
	TArray<TSharedRef<TFunctionFrame<bool>>> AttackFrames;
public:
	void AttachEvent(TSharedPtr<TFunctionFrame<bool>> Event);
	void SendEvent(TSharedPtr<TFunctionFrame<bool>> Address, bool bData);
};

template<typename T>
class TFunctionFrame
{
public:
	DECLARE_EVENT_TwoParams(TFunctionFrame, FSendEvent, TSharedPtr<TFunctionFrame<T>>, T);
	FSendEvent SendEvent;

	DECLARE_EVENT_OneParam(TFuncionFrame, FReceiveEvent, T);
	FReceiveEvent ReceiveEvent;

	void PlaySendEvent(TSharedPtr<TFunctionFrame<bool>> Address, T Data)
	{
		SendEvent.Broadcast(Address, Data);
	}

	void PlayReceiveEvent(T Data)
	{
		ReceiveEvent.Broadcast(Data);
	}
};
