// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealPortfolio/Public/MainAnimInstance.h"


void UMainAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Init();
}

void UMainAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	SyncAnimationData();
}

void UMainAnimInstance::Init()
{
	APawn* Owner = TryGetPawnOwner();

	if(Owner != nullptr)
	{
		MainCharacter = Cast<AMainCharacter>(Owner);

		if(MainCharacter != nullptr)
		{
			MainCharacterMovement = MainCharacter->GetCharacterMovement();
		}
	}

	BindEvent();
}

void UMainAnimInstance::BindEvent()
{
	if(MainCharacter != nullptr)
	{
		MainCharacter->AttackEvent.AddUObject(this, &UMainAnimInstance::Attack);
	}
}


void UMainAnimInstance::SyncAnimationData()
{
	if(MainCharacterMovement != nullptr)
	{
		Velocity = MainCharacterMovement->Velocity.Length();
		bFalling = MainCharacterMovement->IsFalling();
	}
}

void UMainAnimInstance::Attack()
{
	bAttacking = true;
}





