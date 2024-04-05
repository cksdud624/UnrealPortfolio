// ReSharper disable once UnrealHeaderToolError
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "UnrealPortfolio/Public/MainAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UnrealPortfolio/MainCharacter.h"

#include "MainAnimInstance.generated.h"

/**
 * 
 */
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
	bool bAttacking;

	DECLARE_EVENT_OneParam(UMainAnimInstance, FCanMove, bool);
	FCanMove SendCanMove;
	
protected:
	
	UPROPERTY()
	AMainCharacter* MainCharacter;
	UPROPERTY()
	UCharacterMovementComponent* MainCharacterMovement;
	UPROPERTY()
	bool bCanMove;
	
	void Init();
	void BindEvent();
	
	void SyncAnimationData();
	
	void Attack();
};
