// Shoot them Up Game. All Rights Reserved.

#pragma once

#include "UI/STUBaseWidget.h"
#include "CoreMinimal.h"
#include "STUPauseWidget.generated.h"

class UButton;

UCLASS()
class SHOOTTHEMUP_API USTUPauseWidget : public USTUBaseWidget
{
    GENERATED_BODY()

  protected:
    UPROPERTY(meta = (BindWidget))
    UButton *ClearPauseButton;

    virtual void NativeOnInitialized() override;

  private:
    UFUNCTION()
    void OnClearPause();
};
