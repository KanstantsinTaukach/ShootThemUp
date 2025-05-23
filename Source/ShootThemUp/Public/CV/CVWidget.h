// Shoot them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "CVWidget.generated.h"

class AKanstantsinTaukach;

UCLASS()
class SHOOTTHEMUP_API UCVWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Category = "Data")
    AKanstantsinTaukach* CVActor;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Text_Name;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Text_Location;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Text_Contacts;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Text_Education;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Text_Courses;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Text_Skills;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* Text_About;

    virtual void NativeOnInitialized() override;

protected:
    AKanstantsinTaukach* FindCVActorInWorld();

    void UpdateTextBlocks();
};
