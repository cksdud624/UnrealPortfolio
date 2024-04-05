// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainCharacter::Init()
{
	InitPlayerController();

	MainCamera = GetComponentByClass<UCameraComponent>();
	MainMesh = GetMesh();
	Mediator = GetComponentByClass<UMainCharacterMediator>();
	
	bUseControllerRotationYaw = false;

	BindEvent();
}


void AMainCharacter::InitPlayerController()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			SubSystem->AddMappingContext(PlayerContext, 0);
	}
}

void AMainCharacter::BindEvent()
{
	if(Mediator != nullptr)
	{
		TFunctionFrame<bool>* Frame = NewObject<TFunctionFrame<bool>>();

		Frame->MainEvent.AddUObject(this, );
		
		Mediator->AttachEvent(Frame);
	}
}




// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::MovePlayer);
		Input->BindAction(RotateAction, ETriggerEvent::Triggered, this, &AMainCharacter::RotatePlayer);
		Input->BindAction(JumpAction, ETriggerEvent::Started, this, &AMainCharacter::JumpPlayer);
		
		Input->BindAction(MouseLeftAction, ETriggerEvent::Started, this, &AMainCharacter::Attack);
	}
}

void AMainCharacter::MovePlayer(const FInputActionValue& Value)
{
	if(bCanMove)
	{
		const FVector2D Vector2D = Value.Get<FVector2D>();
		const float DeltaTime = GetWorld()->GetDeltaSeconds();

		FRotator ControllerRotator = GetControlRotation();
		ControllerRotator.Pitch = 0;
		ControllerRotator.Roll = 0;
	
		FRotator ActorRotator = GetActorRotation();
	
		ActorRotator = FMath::Lerp(ActorRotator, ControllerRotator, DeltaTime * 10);
		SetActorRotation(ActorRotator);
	
		AddMovementInput(GetActorForwardVector() * Vector2D.Y * (DeltaTime * 120));
		AddMovementInput(GetActorRightVector() * Vector2D.X * (DeltaTime * 120));

		RotateMesh(Vector2D.Y, Vector2D.X);
	}
}

void AMainCharacter::RotatePlayer(const FInputActionValue& Value)
{
	const FVector2D Vector2D = Value.Get<FVector2D>();
	
	AddControllerPitchInput(Vector2D.Y);
	AddControllerYawInput(Vector2D.X);
}

void AMainCharacter::JumpPlayer(const FInputActionValue& Value)
{
	if(bCanMove)
	{
		Jump();
	}
}

void AMainCharacter::Attack(const FInputActionValue& Value)
{
	AttackEvent.Broadcast();
}


void AMainCharacter::RotateMesh(const int Forward, const int Right)
{
	if(bCanMove)
	{
		const FRotator Rotator = (GetActorForwardVector() * Forward + GetActorRightVector() * Right).Rotation()
		+ FRotator(0, 270, 0);
	
		FRotator MeshRotator = MainMesh->GetComponentRotation();

		MeshRotator = FMath::Lerp(MeshRotator, Rotator, GetWorld()->GetDeltaSeconds() * 10);

		MainMesh->SetWorldRotation(MeshRotator);
	}
}

void AMainCharacter::SetCanMove(const bool bCanMove)
{
	this->bCanMove = bCanMove;
}

	
