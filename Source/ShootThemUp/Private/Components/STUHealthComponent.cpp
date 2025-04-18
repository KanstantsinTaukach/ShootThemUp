// Shoot them Up Game. All Rights Reserved.

#include "Components/STUHealthComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "TimerManager.h"
#include "Camera/CameraShakeBase.h"
#include "STUGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(HealthComponentLog, All, All);

USTUHealthComponent::USTUHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    check(MaxHealth > 0);

    SetHealth(MaxHealth);

    AActor *ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamageHandle);
    }
}

void USTUHealthComponent::OnTakeAnyDamageHandle(AActor *DamagedActor, float Damage, const UDamageType *DamageType,
                                                AController *InstigatedBy, AActor *DamageCauser)
{
    if (Damage <= 0.0f || IsDead() || !GetWorld())
    {
        return;
    }

    SetHealth(Health - Damage);
    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

    if (IsDead())
    {
        Killed(InstigatedBy);
        OnDeath.Broadcast();
    }
    else if (AutoHeal)
    {
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USTUHealthComponent::HealUpdate, HealUpdateTime,
                                               true, HealDelay);
    }

    PlayCameraShake();
}

void USTUHealthComponent::HealUpdate()
{
    SetHealth(Health + HealModifier);

    if (IsHealthFull() && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    }
}

void USTUHealthComponent::SetHealth(float NewHealth)
{
    const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    const auto HealthDelta = NextHealth - Health;
    Health = NextHealth;
    OnHealthChanged.Broadcast(Health, HealthDelta);
}

bool USTUHealthComponent::IsHealthFull() const
{
    return FMath::IsNearlyEqual(Health, MaxHealth);
}

bool USTUHealthComponent::TryToAddHealth(float HealthAmount)
{
    if (IsDead() || IsHealthFull() || HealthAmount <= 0)
    {
        return false;
    }
    else
    {
        SetHealth(Health + HealthAmount);
    }

    return true;
}

void USTUHealthComponent::PlayCameraShake()
{
    if (IsDead())
    {
        return;
    }

    const auto Pawn = Cast<APawn>(GetOwner());
    if (!Pawn)
    {
        return;
    }

    const auto Controller = Pawn->GetController<APlayerController>();
    if (!Controller || !Controller->PlayerCameraManager)
    {
        return;
    }

    Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

void USTUHealthComponent::Killed(AController *KillerController)
{
    if (!GetWorld()) return;

    const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
    if (!GameMode) return;

    const auto Player = Cast<APawn>(GetOwner());
    const auto VictimController = Player ? Player->Controller : nullptr;

    GameMode->Killed(KillerController, VictimController);
}
