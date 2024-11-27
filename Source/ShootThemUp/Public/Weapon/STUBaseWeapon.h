// Shoot them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUCoreTypes.h"
#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
    GENERATED_BODY()

  public:
    ASTUBaseWeapon();

    FOnClipEmptySignature OnClipEmpty;

    virtual void StartFire();
    virtual void StopFire();

    void ChangeClip();
    bool CanReload() const;

    FWeaponUIData GetUIData() const
    {
        return UIData;
    }

    FAmmoData GetAmmoData() const
    {
        return CurrentAmmo;
    }

    bool TryToAddAmmo(int32 ClipsAmount);

  protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent *WeaponSkeletalMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FName MuzzleSocketName = "MuzzleFlashSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TraceMaxDistance = 15000.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmoData DefaultAmmo{15, 10, false};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FWeaponUIData UIData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem *MuzzleFX;

    virtual void BeginPlay() override;

    virtual void MakeShot();

    virtual bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const;

    APlayerController *GetPlayerController() const;

    bool GetPlayerViewPoint(FVector &ViewLocation, FRotator &ViewRotation) const;

    FVector GetMuzzleWorldLocation() const;

    void CheckHit(FHitResult &HitResult, const FVector &TraceStart, const FVector &TraceEnd) const;

    void DecreaseAmmo();
    bool IsAmmoEmpty() const;
    bool IsAmmoFull() const;
    bool IsClipEmpty() const;
    void LogAmmo();   

    UNiagaraComponent *SpawnMuzzleFX();

  private:
    FAmmoData CurrentAmmo;
};
