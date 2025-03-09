// Shoot them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_AmmoCouldBeTaken.generated.h"

class ASTUBaseWeapon;

UCLASS()
class SHOOTTHEMUP_API UEnvQueryTest_AmmoCouldBeTaken : public UEnvQueryTest
{
    GENERATED_BODY()

  public:
    UEnvQueryTest_AmmoCouldBeTaken(const FObjectInitializer &ObjectInitializer);

    virtual void RunTest(FEnvQueryInstance &QueryInstance) const override;

  protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TSubclassOf<ASTUBaseWeapon> WeaponType;
};
