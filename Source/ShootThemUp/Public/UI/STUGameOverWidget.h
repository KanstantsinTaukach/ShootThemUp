// Shoot them Up Game. All Rights Reserved.

#pragma once

#include "UI/STUBaseWidget.h"
#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "STUGameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class SHOOTTHEMUP_API USTUGameOverWidget : public USTUBaseWidget
{
    GENERATED_BODY()

  protected:
    UPROPERTY(meta = (BindWidget))
    UVerticalBox *PlayerStatBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

    UPROPERTY(meta = (BindWidget))
    UButton *ResetLevelButton;

    virtual void NativeOnInitialized() override;

  private:
    void OnMatchStateChanged(ESTUMatchState State);

    void UpdatePlayerStat();

    UFUNCTION()
    void OnResetLevel();
};
