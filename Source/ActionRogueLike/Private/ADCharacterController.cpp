// Fill out your copyright notice in the Description page of Project Settings.


#include "ADCharacterController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "ADCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


void AADCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent
		= Cast<UEnhancedInputComponent>(this->InputComponent);

	if (EnhancedInputComponent) {
		//Move
		EnhancedInputComponent->BindAction(MoveAction.Get(),
			ETriggerEvent::Triggered, this, &AADCharacterController::Move);

		//Look
		EnhancedInputComponent->BindAction(LookAction.Get(),
			ETriggerEvent::Triggered, this, &AADCharacterController::Look);

		//Jump
		EnhancedInputComponent->BindAction(JumpAction.Get(),
			ETriggerEvent::Started, this, &AADCharacterController::JumpStart);

		
		EnhancedInputComponent->BindAction(JumpAction.Get(),
			ETriggerEvent::Completed, this, &AADCharacterController::JumpStop);

		//Run
		EnhancedInputComponent->BindAction(RunAction.Get(),
			ETriggerEvent::Started, this, &AADCharacterController::RunStart);


		EnhancedInputComponent->BindAction(RunAction.Get(),
			ETriggerEvent::Completed, this, &AADCharacterController::RunStop);
	}
}

void AADCharacterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	this->CurrentCharacter = Cast<AADCharacter>(InPawn);

	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputLocalPlayerSubsystem
		= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer());

	if (InputLocalPlayerSubsystem)
	{
		InputLocalPlayerSubsystem->AddMappingContext(this->CurrentMappingContext.Get(), 0);
	}
}

void AADCharacterController::Move(const FInputActionValue& Value)
{
	const FVector2d MovementVector = Value.Get<FVector2d>();

	const FRotator Rotation = this->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDiretcion = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	this->CurrentCharacter->AddMovementInput(ForwardDiretcion, MovementVector.Y);
	this->CurrentCharacter->AddMovementInput(RightDirection, MovementVector.X);

}

void AADCharacterController::Look(const FInputActionValue& Value)
{

	const FVector2d LookAxisVector = Value.Get<FVector2d>();

	this->CurrentCharacter->AddControllerYawInput(LookAxisVector.X);
	this->CurrentCharacter->AddControllerPitchInput(LookAxisVector.Y);

}

void AADCharacterController::JumpStart()
{
	this->CurrentCharacter->Jump();
}

void AADCharacterController::JumpStop()
{
	this->CurrentCharacter->StopJumping();
}

void AADCharacterController::RunStart()
{
	this->CurrentCharacter->GetCharacterMovement()->MaxWalkSpeed *= 2.0f;
}

void AADCharacterController::RunStop()
{
	this->CurrentCharacter->GetCharacterMovement()->MaxWalkSpeed /= 2.0f;
}
