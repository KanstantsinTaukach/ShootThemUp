// Shoot them Up Game. All Rights Reserved.

#include "CV/CVWidget.h"
#include "CV/KanstantsinTaukach.h"
#include "EngineUtils.h"

void UCVWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (!CVActor)
    {
        CVActor = FindCVActorInWorld();
    }

    if (!CVActor || !CVActor->IsValidLowLevel()) return;

    UpdateTextBlocks();
}

AKanstantsinTaukach* UCVWidget::FindCVActorInWorld()
{
    const auto PlayerController = GetOwningPlayer();
    if (!PlayerController || !PlayerController->GetWorld())
    {
        return nullptr;
    }

    for (TActorIterator<AKanstantsinTaukach> It(PlayerController->GetWorld()); It; ++It)
    {
        AKanstantsinTaukach* FoundActor = *It;
        if (FoundActor && FoundActor->IsValidLowLevel())
        {
            return FoundActor;
        }
    }

    return nullptr;
}

void UCVWidget::UpdateTextBlocks()
{
    Text_Name->SetText(FText::FromString(CVActor->FullName.ToString()));

    Text_Location->SetText(FText::FromString(CVActor->Location));

    Text_Contacts->SetText(FText::FromString(
        FString::Printf(TEXT("Phone: %s\nEmail: %s\nGitHub: %s"), *CVActor->PhoneNumber, *CVActor->Email, *CVActor->GitHub)));

    Text_Education->SetText(FText::FromString(FString::Printf(TEXT("\n%s\n%s\n"), *CVActor->Education_1, *CVActor->Education_2)));

    Text_Courses->SetText(FText::FromString(FString::Printf(TEXT("Skillbox: %s\nUdemy: %s\nStanford: %s\n"),
        *CVActor->Course_Skillbox, *CVActor->Course_Udemy, *CVActor->Course_Stanford)));

    FString SkillsText;
    for (const FString& Skill : CVActor->Programming)
        SkillsText += "- " + Skill + "\n";
    for (const FString& Skill : CVActor->AI)
        SkillsText += "- " + Skill + "\n";
    for (const FString& Skill : CVActor->VFX)
        SkillsText += "- " + Skill + "\n";
    for (const FString& Skill : CVActor->Animation)
        SkillsText += "- " + Skill + "\n";
    for (const FString& Skill : CVActor->UI)
        SkillsText += "- " + Skill + "\n";
    for (const FString& Skill : CVActor->Networking)
        SkillsText += "- " + Skill + "\n";
    Text_Skills->SetText(FText::FromString(SkillsText));

    Text_About->SetText(
        FText::FromString(FString::Printf(TEXT("%s\n%s\n%s"), *CVActor->CareerGoal, *CVActor->GamingExperience, *CVActor->WorkStyle)));
}
