// Shoot them Up Game. All Rights Reserved.


#include "Player/STUBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"

ASTUBaseCharacter::ASTUBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);
}

void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASTUBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::LookUp);
    PlayerInputComponent->BindAxis("TurnAround", this, &ASTUBaseCharacter::TurnAround);
}

void ASTUBaseCharacter::MoveForward(float Amount) 
{
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTUBaseCharacter::MoveRight(float Amount) 
{
    AddMovementInput(GetActorRightVector(), Amount);
}

void ASTUBaseCharacter::LookUp(float Amount) 
{
    AddControllerPitchInput(Amount);
}

void ASTUBaseCharacter::TurnAround(float Amount) 
{
    AddControllerYawInput(Amount);
}
