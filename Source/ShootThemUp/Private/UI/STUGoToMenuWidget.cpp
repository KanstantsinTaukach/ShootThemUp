// Shoot them Up Game. All Rights Reserved.

#include "UI/STUGoToMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STUGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGoToMenuWidget, All, All);

void USTUGoToMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GoToMenuButton)
    {
        GoToMenuButton->OnClicked.AddDynamic(this, &USTUGoToMenuWidget::OnGoToMenu);
    }
}

void USTUGoToMenuWidget::OnGoToMenu()
{
    if (!GetWorld()) return;

    const auto GameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
    if (!GameInstance) return;

    if (GameInstance->GetMenuLevelName().IsNone())
    {
        UE_LOG(LogSTUGoToMenuWidget, Error, TEXT("Menu level name is NONE"));
        return;
    }

    UGameplayStatics::OpenLevel(this, GameInstance->GetMenuLevelName());
}