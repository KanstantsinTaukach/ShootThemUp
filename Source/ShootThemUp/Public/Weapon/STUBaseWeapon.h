// Shoot them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
    GENERATED_BODY()

  public:
    ASTUBaseWeapon();

  protected:
    UPROPERTY(VisibleAnywhere, blueprintReadWrite, Category = "Components")
    USkeletalMeshComponent *WeaponSkeletalMesh;

    virtual void BeginPlay() override;
};
