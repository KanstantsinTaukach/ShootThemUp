// Shoot them Up Game. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "STUPlayerHUDWidget.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUDWidget : public UUserWidget
{
    GENERATED_BODY()

    public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPercent() const;
};
