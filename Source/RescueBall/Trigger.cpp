// Fill out your copyright notice in the Description page of Project Settings.

#include "RescueBall.h"
#include "Trigger.h"


// Sets default values for this component's properties
UTrigger::UTrigger()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTrigger::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = GetOwner()->GetActorLocation();
}


// Called every frame
void UTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (GetTotalMass() > minimumWeight){
		EOpen.Broadcast();
	}
	else
		EClose.Broadcast();
}
// ...

float UTrigger::GetTotalMass(){

	float mass = 0.f;
	TArray<AActor*> overlappingActors;
	if (PressurePlate){
		PressurePlate->GetOverlappingActors(OUT overlappingActors);
		for (auto& a : overlappingActors){
			mass += a->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("NO PRESSURE PLATE FOUND"));
	}
	return mass;
}

