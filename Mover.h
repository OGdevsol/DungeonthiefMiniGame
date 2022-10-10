// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DUNGEONTHIEF_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:
	UMover();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	void SetShouldMove(bool shouldMove);

private:
	FVector originalLocation;
	UPROPERTY(EditAnywhere)
	FVector moveOffset;
	UPROPERTY(EditAnywhere)
	float MoveTime = 4;
	bool checkIfMovementEnabled = false;
};