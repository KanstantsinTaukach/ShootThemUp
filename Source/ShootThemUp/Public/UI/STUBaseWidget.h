// Shoot them Up Game. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "STUBaseWidget.generated.h"

class USoundCue;

UCLASS()
class SHOOTTHEMUP_API USTUBaseWidget : public UUserWidget
{
    GENERATED_BODY()

  public:
    void Show();

  protected:
    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation *ShowAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue *OpenSound;
};