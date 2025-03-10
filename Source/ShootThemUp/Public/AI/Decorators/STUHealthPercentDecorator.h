// Shoot them Up Game. All Rights Reserved.

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "CoreMinimal.h"
#include "STUHealthPercentDecorator.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUHealthPercentDecorator : public UBTDecorator
{
    GENERATED_BODY()

  public:
    USTUHealthPercentDecorator();

  protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float HealtPercent = 0.6f;

    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const override;
};
