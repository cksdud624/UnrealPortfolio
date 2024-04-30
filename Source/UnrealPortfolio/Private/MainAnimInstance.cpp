// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealPortfolio/Public/MainAnimInstance.h"

#include "Engine/SkeletalMeshSocket.h"


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
	if(Weapon != nullptr)
	{
		Weapon->SetActorHiddenInGame(true);
		Weapon->SetActorEnableCollision(false);
	}
	
	if(AttackEvent != nullptr)
	{
		AttackEvent->PlaySendEvent(AttackEvent, true);
	}

	UE_LOG(LogTemp, Log, TEXT("어택 종료"));
}

void UMainAnimInstance::Init()
{
	APawn* Owner = TryGetPawnOwner();

	if(Owner != nullptr)
	{
		Mediator = Owner->GetComponentByClass<UMainCharacterMediator>();
		
		AMainCharacter* MainCharacter = Cast<AMainCharacter>(Owner);

		if(MainCharacter != nullptr)
		{
			MainCharacterMovement = MainCharacter->GetCharacterMovement();
		}

		MainMesh = GetSkelMeshComponent();


		TArray<AActor*> ChildActors;
		Owner->GetAllChildActors(ChildActors);

		for(AActor* ChildActor : ChildActors)
		{
			if(ACharacterWeaponSword* CheckActor = Cast<ACharacterWeaponSword>(ChildActor))
			{
				Weapon = CheckActor;
			}
		}

		if(Weapon != nullptr)
		{
			Weapon->SetActorHiddenInGame(true);
			Weapon->SetActorEnableCollision(false);
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

		AttackEvent = Frame;
		
		Mediator->AttachEvent(Frame);
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
	{
		bAttacking = bAttack;
		if(Weapon != nullptr)
		{
			Weapon->SetActorHiddenInGame(false);
			Weapon->SetActorEnableCollision(true);
		}
	}
}




