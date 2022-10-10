// Fill out your copyright notice in the Description page of Project Settings.

#include "Mover.h"
#include "Math/UnrealMathUtility.h"

UMover::UMover()
{

	PrimaryComponentTick.bCanEverTick = true;
}

void UMover::BeginPlay()
{
	Super::BeginPlay();
	originalLocation = GetOwner()->GetActorLocation();
}

void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{

	if (checkIfMovementEnabled)
	{
		Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
		FVector CurrentLocation = GetOwner()->GetActorLocation();

		FVector targetPosition = originalLocation + moveOffset;
		float speed = FVector::Distance(originalLocation, targetPosition) / MoveTime;
		FVector NewPosition = FMath::VInterpConstantTo(CurrentLocation, targetPosition, DeltaTime, speed);
		GetOwner()->SetActorLocation(NewPosition);
	}
}
void UMover::SetShouldMove(bool NewShouldMove)
{
	checkIfMovementEnabled = NewShouldMove;
}
