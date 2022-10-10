// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerComponent.h"
UTriggerComponent::UTriggerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}
void UTriggerComponent::BeginPlay()
{
    Super::BeginPlay();
}
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    AActor *actor = GetAcceptableActor();
    if (actor != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Unlocking"));
       UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(actor->GetRootComponent());
       if (Component!=nullptr)
       {
        Component->SetSimulatePhysics(false);
       }
       actor->AttachToComponent(this,FAttachmentTransformRules::KeepWorldTransform);
        Mover->SetShouldMove(true);
    }
    else
    {
        Mover->SetShouldMove(false);
        UE_LOG(LogTemp, Warning, TEXT("Relocking"));
    }
}
void UTriggerComponent::SetMover(UMover* NewMover)
{
    Mover = NewMover;
}
AActor *UTriggerComponent::GetAcceptableActor() const
{
    AActor *ReturnActor = nullptr;
    TArray<AActor *> Actors;
    GetOverlappingActors(Actors);

    for (int i = 0; i < Actors.Num(); i++)
    {

        if (Actors[i]->ActorHasTag(AcceptableActorTag))
        {
            return Actors[i];
            FString ActorName = Actors[i]->GetActorNameOrLabel();
        }
    }
    return nullptr;
}
