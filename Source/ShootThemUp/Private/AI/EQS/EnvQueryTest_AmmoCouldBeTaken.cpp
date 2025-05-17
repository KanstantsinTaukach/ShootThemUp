// Shoot them Up Game. All Rights Reserved.

#include "AI/EQS/EnvQueryTest_AmmoCouldBeTaken.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "Pickups/STUAmmoPickup.h"
#include "Weapon/STUBaseWeapon.h"

UEnvQueryTest_AmmoCouldBeTaken::UEnvQueryTest_AmmoCouldBeTaken(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    Cost = EEnvTestCost::Low;
    ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
    SetWorkOnFloatValues(false);
}

void UEnvQueryTest_AmmoCouldBeTaken::RunTest(FEnvQueryInstance& QueryInstance) const
{
    UObject* DataOwner = QueryInstance.Owner.Get();
    BoolValue.BindData(DataOwner, QueryInstance.QueryID);
    bool WantsBeTakable = BoolValue.GetValue();

    for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
    {
        const auto ItemActor = GetItemActor(QueryInstance, It.GetIndex());
        const auto PickupActor = Cast<ASTUAmmoPickup>(ItemActor);
        if (!PickupActor || PickupActor->GetWeaponType() != WeaponType) continue;

        const auto CouldBeTaken = PickupActor->CouldBeTaken();
        It.SetScore(TestPurpose, FilterType, CouldBeTaken, WantsBeTakable);
    }
}
