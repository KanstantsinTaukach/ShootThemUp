// Shoot them Up Game. All Rights Reserved.

#pragma once

#include "Animation/AnimNotifies/AnimNotify.h"
#include "CoreMinimal.h"
#include "STUAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifiedSignature, USkeletalMeshComponent *);

UCLASS()
class SHOOTTHEMUP_API USTUAnimNotify : public UAnimNotify
{
    GENERATED_BODY()

  public:
    virtual void Notify(class USkeletalMeshComponent *MeshComp, class UAnimSequenceBase *Animation) override;

    FOnNotifiedSignature OnNotified;
};
