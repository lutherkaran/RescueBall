// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
//#include "Blueprint/UserWidget.h"
#include "Ball.generated.h"

UCLASS()
class RESCUEBALL_API ABall : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABall();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere)
		USceneComponent *CenterOfMass;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent *Ball;
	UPROPERTY(EditAnywhere)
		USpringArmComponent *SpringArm;
	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera;
	//UPrimitiveComponent *OurActor2;
	//USceneComponent* GetCenterOfMass();

	void MoveForward(float x);
	void MoveRight(float y);
	
	void CameraPitch(float _x);
	void CameraYaw(float _x);

	void Sprint();
	void Reset();
	float GetSpeed();
	void  SetSpeed(float _speed);

	FVector2D CameraInput;
	FVector MovementInput;
	FVector CurrentVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float fSpeed = 500.f;
	float fSpeedMultiplier = 2.f;
	FInputModeUIOnly InputModeData;

};

//#include "Camera/CameraComponent.h"
//#include "Components/SphereComponent.h"
//#include "Components/StaticMeshComponent.h"
//#include "Components/InputComponent.h"
//#include "GameFramework/"
//#include "GameFramework/Pawn.h"
//#include "GameFramework/Pawn.h"
