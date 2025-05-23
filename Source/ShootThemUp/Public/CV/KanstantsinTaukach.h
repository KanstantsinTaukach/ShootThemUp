// Shoot them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KanstantsinTaukach.generated.h"

UCLASS()
class SHOOTTHEMUP_API AKanstantsinTaukach : public AActor
{
    GENERATED_BODY()
protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, Category = "Personal Info")
    FName FullName = TEXT("KANSTANTSIN TAUKACH \nUNREAL ENGINE DEVELOPER");
    UPROPERTY(EditAnywhere, Category = "Personal Info")
    FString Location = TEXT("Brest, Republic of Belarus");
    UPROPERTY(EditAnywhere, Category = "Personal Info")
    FDateTime BirthDate = FDateTime(1985, 6, 8);

    UPROPERTY(EditAnywhere, Category = "Contact Info")
    FString PhoneNumber = TEXT("+37529 828-26-28");
    UPROPERTY(EditAnywhere, Category = "Contact Info")
    FString Email = TEXT("tovkachkot@gmail.com");
    UPROPERTY(EditAnywhere, Category = "Contact Info")
    FString Telegram = TEXT("@KanstantsinT");
    UPROPERTY(EditAnywhere, Category = "Contact Info")
    FString GitHub = TEXT("https://github.com/KanstantsinTaukach");

    UPROPERTY(EditAnywhere, Category = "Education")
    FString Education_1 = TEXT("Institute of Business of BSU | 2017 - 2019 | Software for Information Systems");
    UPROPERTY(EditAnywhere, Category = "Education")
    FString Education_2 = TEXT("Brest State Technical University | 2005 - 2009 | Mechanical Engineering Technology");

    UPROPERTY(EditAnywhere, Category = "Courses")
    FString Course_Skillbox = TEXT("Profession: Game Developer (UE4) from Zero to Middle");
    UPROPERTY(EditAnywhere, Category = "Courses")
    FString Course_Udemy = TEXT("Unreal Engine - Complete C++ Game Development Guide");
    UPROPERTY(EditAnywhere, Category = "Courses")
    FString Course_Stanford = TEXT("Professional Game Dev in C++ and Unreal Engine");

    UPROPERTY(EditAnywhere, Category = "Skills")
    TArray<FString> Programming = 
    { 
        TEXT("C++ Game Systems Development using UE API"),
        TEXT("OOP Principles & Design Patterns in Game Context"),
        TEXT("Performance Optimization for C++ and Blueprint Code")
    };
    UPROPERTY(EditAnywhere, Category = "Skills")
    TArray<FString> AI = 
    {
        TEXT("Behavior Trees, Blackboard, Decorators, Services"),
        TEXT("AI Perception System Setup"), 
        TEXT("EQS (Environment Query System) Implementation")
    };
    UPROPERTY(EditAnywhere, Category = "Skills")
    TArray<FString> VFX = 
    {
        TEXT("Niagara Particle Effects Creation"), 
        TEXT("GPU/CPU Particles Management"),
        TEXT("VFX Integration with Gameplay Events")
    };
    UPROPERTY(EditAnywhere, Category = "Skills")
    TArray<FString> Animation = 
    {
        TEXT("Animation Blueprints (Blend Spaces, State Machines)"),
        TEXT("Anim Notifies for Animation Sync")
    };
    UPROPERTY(EditAnywhere, Category = "Skills")
    TArray<FString> UI = 
    {
        TEXT("UMG Interface Development (HUD, Menus)")
    };
    UPROPERTY(EditAnywhere, Category = "Skills")
    TArray<FString> Networking = 
    {
        TEXT("Basic Network Replication Understanding"), 
        TEXT("RPC Usage in Server-Client Archtecture"),
        TEXT("Multiplayer Event Synchronization")
    };

    UPROPERTY(EditAnywhere, Category = "About")
    FString CareerGoal = TEXT(
        "Planning a career in game development. Drawn to the industry by passion for analytics, \ncreating new worlds, and love for games");
    UPROPERTY(EditAnywhere, Category = "About")
    FString GamingExperience = TEXT(
        "Over 20 years of gaming experience across genres - from adventures to complex RPGs. \nDeep understanding of gameplay mechanics and genre specifics.");
    UPROPERTY(EditAnywhere, Category = "About")
    FString WorkStyle = TEXT(
        "Approaches tasks with clear goals, break big problems into smaller steps, \nand builds structured solutions. Open to roles in agencies or game dev studios.");
};
