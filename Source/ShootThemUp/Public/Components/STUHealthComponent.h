// Shoot them Up Game. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "STUHealthComponent.generated.h"

class UCameraShakeBase;
class UPhysicalMaterial;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
    GENERATED_BODY()

  public:
    USTUHealthComponent();

    FOnDeathSignature OnDeath;
    FOnHealthChangedSignature OnHealthChanged;

    UFUNCTION(BlueprintCallable, Category = "Health")
    bool IsDead() const
    {
        return FMath::IsNearlyZero(Health);
    };

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealthPercent() const
    {
        return Health / MaxHealth;
    }

    float GetHealth() const
    {
        return Health;
    };

    bool TryToAddHealth(float HealthAmount);

  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0", ClampMax = "300"))
    float MaxHealth = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
    bool AutoHeal = true;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealUpdateTime = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealDelay = 3.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealModifier = 5.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TSubclassOf<UCameraShakeBase> CameraShake;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
    TMap<UPhysicalMaterial *, float> DamageModifiers;

    virtual void BeginPlay() override;

  private:
    float Health = 0.0f;
    FTimerHandle HealTimerHandle;

    UFUNCTION()
    void OnTakeAnyDamage(
        AActor *DamagedActor, 
        float Damage, 
        const class UDamageType *DamageType,
        class AController *InstigatedBy,
        AActor *DamageCauser);

    UFUNCTION()
    void OnTakePointDamage(
        AActor* DamagedActor,
        float Damage,
        class AController* InstigatedBy,
        FVector HitLocation,
        class UPrimitiveComponent* FHitComponent,
        FName BoneName,
        FVector ShotFromDirection,
        const class UDamageType* DamageType,
        AActor* DamageCauser);

    UFUNCTION()
    void OnTakeRadialDamage(
        AActor* DamagedActor,
        float Damage,
        const class UDamageType* DamageType,
        FVector Origin,
        FHitResult HitInfo,
        class AController* InstigatedBy,
        AActor* DamageCauser);

    void HealUpdate();
    void SetHealth(float NewHealth);
    bool IsHealthFull() const;

    void PlayCameraShake();

    void Killed(AController* KillerController);

    void ApplyDamage(float Damage, AController *InstigatedBy);

    float GetPointDamageModifier(AActor *DamagedActor, const FName &BoneName);

    void ReportDamageEvent(float Damage, AController *InstigatedBy);
};
