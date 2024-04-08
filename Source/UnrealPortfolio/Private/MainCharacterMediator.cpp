// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterMediator.h"

// Sets default values for this component's properties
UMainCharacterMediator::UMainCharacterMediator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMainCharacterMediator::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UMainCharacterMediator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMainCharacterMediator::AttachEvent(TSharedPtr<TFunctionFrame<bool>> Event)
{
	TSharedRef<TFunctionFrame<bool>> Ref = Event.ToSharedRef();
	
	for(int i = 0; i < AttackFrames.Num(); i++)
	{
		if(AttackFrames[i] == Ref)
			return;
	}

	Ref->SendEvent.AddUObject(this, &UMainCharacterMediator::SendEvent);

	AttackFrames.Add(Ref);
}

void UMainCharacterMediator::SendEvent(TSharedPtr<TFunctionFrame<bool>> Address, bool bData)
{
	for(int i = 0; i < AttackFrames.Num(); i++)
	{
		if(AttackFrames[i] != Address)
		{
			AttackFrames[i]->PlayReceiveEvent(bData);
		}
	}
}

