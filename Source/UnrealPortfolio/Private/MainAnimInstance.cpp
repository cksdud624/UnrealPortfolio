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


void UMainAnimInstance::CallAttackIsOver()
{
	bAttacking = false;
	if(AttackEvent != nullptr)
	{
		AttackEvent->PlaySendEvent(AttackEvent, true);
	}
}

void UMainAnimInstance::Init()
{
	APawn* Owner = TryGetPawnOwner();

	Mediator = Owner->GetComponentByClass<UMainCharacterMediator>();

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
	if(Mediator != nullptr)
	{
		TSharedPtr<TFunctionFrame<bool>> Frame = MakeShared<TFunctionFrame<bool>>();

		Frame->ReceiveEvent.AddUObject(this, &UMainAnimInstance::Attack);
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

void UMainAnimInstance::Attack(bool bAttack)
{
	if(!bAttacking)
		bAttacking = bAttack;
}




