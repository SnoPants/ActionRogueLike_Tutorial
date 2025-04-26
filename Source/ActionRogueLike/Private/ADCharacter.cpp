// Fill out your copyright notice in the Description page of Project Settings.


#include "ADCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"


// Sets default values
AADCharacter::AADCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void AADCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AADCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

