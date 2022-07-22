// Fill out your copyright notice in the Description page of Project Settings.

#include "RescueBall.h"
#include "Ball.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"


// Sets default values
ABall::ABall()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Ball = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	Ball->SetSimulatePhysics(true);
	Ball->AttachTo(RootComponent);

	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	SpringArm->AttachTo(RootComponent);
	SpringArm->bAbsoluteRotation = false;
	SpringArm->RelativeRotation = FRotator(-45.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 450.f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 3.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachTo(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABall::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
	FRotator YawRotation = GetActorRotation();
	FRotator PitchRotation = SpringArm->GetComponentRotation();
	{
		YawRotation.Yaw += CameraInput.X;
		SetActorRotation(YawRotation);
	}

	//Rotating the camera with a limit
	{
		PitchRotation.Pitch = FMath::Clamp(PitchRotation.Pitch + CameraInput.Y, -80.0f, -15.0f);
		SpringArm->SetWorldRotation(FRotator(PitchRotation.Pitch, YawRotation.Yaw, 0.f));
	}
	// Moving the ball
	if (!CurrentVelocity.IsZero() || !MovementInput.IsZero()){

		MovementInput = MovementInput.GetSafeNormal() * fSpeed;
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
		NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
		SetActorLocation(NewLocation);
	}


}

// Called to bind functionality to input
void ABall::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	if (InputComponent){
		InputComponent->BindAxis("X", this, &ABall::MoveForward);
		InputComponent->BindAxis("Y", this, &ABall::MoveRight);
		InputComponent->BindAxis("CameraPitch", this, &ABall::CameraPitch);
		InputComponent->BindAxis("CameraYaw", this, &ABall::CameraYaw);
		InputComponent->BindAction("Sprint", IE_Pressed, this, &ABall::Sprint);
		InputComponent->BindAction("Sprint", IE_Released, this, &ABall::Reset);
	}
}
void ABall::Reset(){ fSpeed = fSpeed / fSpeedMultiplier; }
void ABall::Sprint(){ fSpeed = fSpeed * fSpeedMultiplier; }

void ABall::CameraPitch(float y){ CameraInput.Y = y; }
void ABall::CameraYaw(float x){ CameraInput.X = x; }
float ABall::GetSpeed(){ return fSpeed; }
void ABall::SetSpeed(float _speed){ fSpeed = _speed; }

void ABall::MoveForward(float _x){
	MovementInput.X = FMath::Clamp<float>(_x, -1.0f, 1.0f);
	//FVector fTorque = FVector(0.f, _x * 2000000.0f, 0.f);
	//Ball->AddTorque(fTorque, NAME_None, false);
}
void ABall::MoveRight(float _y){
	MovementInput.Y = FMath::Clamp<float>(_y, -1.0f, 1.0f);
	//FVector fTorque = FVector((-1.0f)*_y * 2000000.0f, 0.f, 0.f);
	//Ball->AddTorque(fTorque, NAME_None, false);
}
