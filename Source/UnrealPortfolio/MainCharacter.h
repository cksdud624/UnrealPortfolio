// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"

#include "MainCharacterMediator.h"

#include "MainCharacter.generated.h"

class UMainAnimInstance;

UCLASS()
class UNREALPORTFOLIO_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//입력---------------------------------------------------
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* PlayerContext;
	
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* RotateAction;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* MouseLeftAction;

	//------------------------------------------------------
	
	UPROPERTY()
	bool bCanMove = true;



protected:
	UPROPERTY()
	UCameraComponent* MainCamera;

	UPROPERTY()
	USkeletalMeshComponent* MainMesh;

	UPROPERTY()
	UMainCharacterMediator* Mediator;
	
	TSharedPtr<TFunctionFrame<bool>> AttackEvent;
	
	void Init();
	void InitPlayerController();
	void BindEvent();
	
	void MovePlayer(const FInputActionValue& Value);
	void RotatePlayer(const FInputActionValue& Value);
	void JumpPlayer(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	
	void RotateMesh(const int Forward, const int Right);
	
	void SetCanMove(bool bMove);
};
