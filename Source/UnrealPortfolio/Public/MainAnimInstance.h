// ReSharper disable once UnrealHeaderToolError
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MainCharacterMediator.h"
#include "UnrealPortfolio/MainCharacter.h"

#include "MainAnimInstance.generated.h"


UCLASS()
class UNREALPORTFOLIO_API UMainAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	float Velocity;

	UPROPERTY(BlueprintReadOnly)
	bool bFalling;

	UPROPERTY(BlueprintReadOnly)
	bool bAttacking = false;

	UFUNCTION(BlueprintCallable, Category = "MyFunctions")
	void CallAttackIsOver();
	
protected:
	
	UPROPERTY()
	AMainCharacter* MainCharacter;
	UPROPERTY()
	UCharacterMovementComponent* MainCharacterMovement;
	UPROPERTY()
	UMainCharacterMediator* Mediator;
	UPROPERTY()
	USkeletalMeshComponent* MainMesh;

	TSharedPtr<TFunctionFrame<bool>> AttackEvent;
	
	void Init();
	void BindEvent();
	
	void SyncAnimationData();
	
	void Attack(bool bAttack);
};
