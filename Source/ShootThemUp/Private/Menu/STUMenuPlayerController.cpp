// Shoot them Up Game. All Rights Reserved.

#include "Menu/STUMenuPlayerController.h"
#include "CV/CVWidget.h"

void ASTUMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor = true;
}
