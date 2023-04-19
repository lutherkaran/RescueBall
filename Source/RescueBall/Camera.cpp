// Fill out your copyright notice in the Description page of Project Settings.

#include "RescueBall.h"
#include "Camera.h"
#include "Ball.h"


// Sets default values
ACamera::ACamera()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACamera::BeginPlay()
{
	Super::BeginPlay();
	//RootComponent = FindComponentByClass<USceneComponent>();
	//CenterOfMass = BallActor->GetCenterOfMass();
	//
	//// Create a spring arm component to control the camera
	//SpringArm = FindComponentByClass<USpringArmComponent>();
	//SpringArm->TargetArmLength = 500.f; // The distance from the camera to the ball
	//SpringArm->bEnableCameraLag = true; // Add some smoothing to the camera movement
	//
	//if (CenterOfMass != nullptr){ SpringArm->AttachTo(CenterOfMass); }
	//
	//// Create a camera component to view the scene
	//Camera = FindComponentByClass<UCameraComponent>();
	//Camera->AttachTo(SpringArm, USpringArmComponent::SocketName);
	//Camera->bUsePawnControlRotation = false;

	//for (TActorIterator<ABall> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	//{
	//	// Found an actor of class "MyActorClass" in the world
	//	BallActor = *ActorItr;
	//	// Do something with the actor
	//}
}

// Called every frame
void ACamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (BallActor == nullptr || Camera == nullptr || SpringArm == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Camera or Ball or Spring arm could be null"));
		return;
	}

	BallActor->UpdateComponentTransforms();

	// Get the ball's location and rotation
	//CenterOfMass = BallActor->GetCenterOfMass();
	//FVector BallLocation = CenterOfMass->GetComponentLocation();
	//FRotator BallRotation = BallActor->GetActorRotation();
	//
	//// Set the target location of the SpringArmComponent to follow the ball's location
	//FVector CameraPosition = BallLocation + FVector(-500, 0, 200);
	//SpringArm->SetWorldLocation(CameraPosition);
	//
	//// Set the rotation of the SpringArmComponent to face the ball
	//FVector Direction = BallLocation - CameraPosition;
	//Direction.Z = 0.f; // Ignore the height difference
	//FRotator NewRotation = Direction.Rotation();
	////NewRotation.Roll = BallRotation.Roll; // Apply the ball's roll rotation to the camera
	//SpringArm->SetWorldRotation(NewRotation);
	//
	//// Set the camera's location and rotation based on the SpringArmComponent
	//Camera->SetWorldLocation(SpringArm->GetComponentLocation());
	//Camera->SetWorldRotation(SpringArm->GetComponentRotation());
}

