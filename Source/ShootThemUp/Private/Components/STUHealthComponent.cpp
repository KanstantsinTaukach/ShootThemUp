// Shoot them Up Game. All Rights Reserved.

#include "Components/STUHealthComponent.h"
#include "Camera/CameraShakeBase.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "STUGameModeBase.h"
#include "TimerManager.h"

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
        ComponentOwner->OnTakePointDamage.AddDynamic(this, &USTUHealthComponent::OnTakePointDamageHandle);
        ComponentOwner->OnTakeRadialDamage.AddDynamic(this, &USTUHealthComponent::OnTakeRadialDamageHandle);
    }
}

void USTUHealthComponent::OnTakeAnyDamageHandle(AActor *DamagedActor, float Damage, const UDamageType *DamageType,
                                                AController *InstigatedBy, AActor *DamageCauser)
{
    UE_LOG(HealthComponentLog, Display, TEXT("On any damage: %f"), Damage);
}

void USTUHealthComponent::OnTakePointDamageHandle(AActor *DamagedActor, float Damage, AController *InstigatedBy,
                                                  FVector HitLocation, UPrimitiveComponent *FHitComponent,
                                                  FName BoneName, FVector ShotFromDirection,
                                                  const UDamageType *DamageType, AActor *DamageCauser)
{
    const float FinalDamage = Damage * GetPointDamageModifier(DamagedActor, BoneName);
    UE_LOG(HealthComponentLog, Display, TEXT("On point damage: %f, final damage: %f, bone: %s"), Damage, FinalDamage, *BoneName.ToString());
    ApplyDamage(FinalDamage, InstigatedBy);
}

void USTUHealthComponent::OnTakeRadialDamageHandle(AActor *DamagedActor, float Damage, const UDamageType *DamageType,
                                                   FVector Origin, FHitResult HitInfo, AController *InstigatedBy,
                                                   AActor *DamageCauser)
{
    UE_LOG(HealthComponentLog, Display, TEXT("On radial damage: %f"), Damage);
    ApplyDamage(Damage, InstigatedBy);
}

void USTUHealthComponent::ApplyDamage(float Damage, AController *InstigatedBy)
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

float USTUHealthComponent::GetPointDamageModifier(AActor *DamagedActor, const FName &BoneName)
{
    const auto Character = Cast<ACharacter>(DamagedActor);
    if (!Character || !Character->GetMesh() || !Character->GetMesh()->GetBodyInstance(BoneName)) return 1.0f;

    const auto PhysMaterial = Character->GetMesh()->GetBodyInstance(BoneName)->GetSimplePhysicalMaterial();
    if (!PhysMaterial || !DamageModifiers.Contains(PhysMaterial)) return 1.0f;

    return DamageModifiers[PhysMaterial];
}