// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Ball.h"
#include "GameFramework/Actor.h"
#include "Camera.generated.h"

UCLASS()
class RESCUEBALL_API ACamera : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACamera();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent *Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ABall* BallActor;
	UPROPERTY(EditAnywhere)
		USceneComponent *CenterOfMass;

};
