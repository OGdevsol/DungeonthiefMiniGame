// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UPhysicsHandleComponent *PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("GOT PHYSICS HANDLE: %s"), *PhysicsHandle->GetName());
		PhysicsHandle->GetName();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NO PHYSICS HANDLE FOUND"));
	}

}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UPhysicsHandleComponent *PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		return;
	}
	FVector TargetLocation = GetComponentLocation() + GetForwardVector() * holdDistance;
	PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());

	// ...
}
void UGrabber::Grab()
{
	UPhysicsHandleComponent *PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		return;
	}

	FVector Start = GetComponentLocation(); 

	FVector End = Start + GetForwardVector() * MaxGrabDistance;
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);

	FCollisionShape sphere = FCollisionShape::MakeSphere(grabRadius);
	FHitResult hitResult;
	bool hasHit = GetWorld()->SweepSingleByChannel(
		hitResult,
		Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		sphere);
	DrawDebugSphere(GetWorld(), hitResult.ImpactPoint, 10, 10, FColor::Yellow, false, 5);
	DrawDebugSphere(GetWorld(), hitResult.Location, 10, 10, FColor::Blue, false, 5);

	if (hasHit)
	{
		UPrimitiveComponent *HitComponent = hitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			hitResult.GetComponent(), NAME_None, hitResult.ImpactPoint, GetComponentRotation());
	}
}

void UGrabber::Release()
{
}
