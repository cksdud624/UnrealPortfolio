// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterWeaponSword.h"

// Sets default values
ACharacterWeaponSword::ACharacterWeaponSword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterWeaponSword::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterWeaponSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacterWeaponSword::NotifyActorBeginOverlap(AActor* OtherActor)
{
	UE_LOG(LogTemp, Log, TEXT("이벤트"));
	if(OtherActor->ActorHasTag("Enemy"))
		UE_LOG(LogTemp, Log, TEXT("히트"));
}


