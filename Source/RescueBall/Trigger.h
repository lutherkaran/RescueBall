// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Trigger.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOpenEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCloseEvent);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RESCUEBALL_API UTrigger : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTrigger();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(EditAnywhere)
		float closeDelay = 1.f;
	UPROPERTY(EditAnywhere)
		ATriggerVolume *PressurePlate;
	UPROPERTY(EditAnywhere)
		float minimumWeight;
	UPROPERTY(EditAnywhere)
		FVector InitialLocation;
	UPROPERTY(BlueprintAssignable)
		FOpenEvent EOpen;
	UPROPERTY(BlueprintAssignable)
		FCloseEvent EClose;
private:
	float GetTotalMass();
};
