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
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BallMesh(TEXT("/Game/Rolling/Meshes/BallMesh.BallMesh"));
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Attach the ball to the ball movement component
	Ball = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball0"));
	Ball->SetStaticMesh(BallMesh.Object);
	Ball->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	Ball->SetSimulatePhysics(true);
	Ball->SetAngularDamping(0.1f);
	Ball->SetLinearDamping(0.1f);
	Ball->BodyInstance.MassScale = 3.5f;
	Ball->BodyInstance.MaxAngularVelocity = 800.0f;
	Ball->SetNotifyRigidBodyCollision(true);
	RootComponent = Ball;

	// Create a camera boom attached to the ball movement component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	SpringArm->AttachTo(RootComponent);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bAbsoluteRotation = true;
	SpringArm->RelativeRotation = FRotator(-45.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 500.f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 3.f;

	// Create a camera and attach to boom
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
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

	if (Ball == nullptr || Camera == nullptr || SpringArm == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Camera or Ball or Spring arm could be null"));
		return;
	}
}

// Called to bind functionality to input
void ABall::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	if (InputComponent){
		InputComponent->BindAxis("X", this, &ABall::MoveForward);
		InputComponent->BindAxis("Y", this, &ABall::MoveRight);
		InputComponent->BindAction("Sprint", IE_Pressed, this, &ABall::Sprint);
		InputComponent->BindAction("Sprint", IE_Released, this, &ABall::Reset);
	}
}
void ABall::Reset(){ fSpeed = fSpeed / fSpeedMultiplier; }
void ABall::Sprint(){ fSpeed = fSpeed * fSpeedMultiplier; }

float ABall::GetSpeed(){ return fSpeed; }
void ABall::SetSpeed(float _speed){ fSpeed = _speed; }

void ABall::MoveForward(float _x){
	//MovementInput.X = FMath::Clamp<float>(_x, -1.0f, 1.0f);
	FVector fTorque = FVector(0.f, _x * 50000000.0f, 0.f);
	Ball->AddTorque(fTorque);
}
void ABall::MoveRight(float _y){
	//MovementInput.Y = FMath::Clamp<float>(_y, -1.0f, 1.0f);
	FVector fTorque = FVector((-1.0f)*_y * 50000000.0f, 0.f, 0.f);
	Ball->AddTorque(fTorque);
}