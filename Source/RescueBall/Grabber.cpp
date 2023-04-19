// Fill out your copyright notice in the Description page of Project Settings.

#include "RescueBall.h"
#include "Components/InputComponent.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;

	FString GrabString = "LMB";
	GrabText = CreateDefaultSubobject<UTextRenderComponent>((TEXT("GrabText")));
	GrabText->SetText(FText(FText::FromString(GrabString)));
	GrabText->SetWorldSize(100.f);
	GrabText->SetVisibility(false);
	GrabText->SetTextRenderColor(FColor(255, 165, 128));
	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	//Caching Physics Handle and Input Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	InputHandle = GetOwner()->FindComponentByClass<UInputComponent>();

	if (!PhysicsHandle){
		UE_LOG(LogTemp, Error, TEXT("Missing Physics Handle Component"))
	}
	if (!InputHandle){
		UE_LOG(LogTemp, Error, TEXT("Missing Input Handle Component"))
	}
	else{
		InputHandle->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputHandle->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}


}
void UGrabber::Grab(){
	//UE_LOG(LogTemp, Error, TEXT("GrabPressed"))
	auto Hit = HitResult(PlayerViewPointLocation, PlayerViewPointRotation);
	auto toGrab = Hit.GetComponent();
	if (Hit.GetActor()){
		toGrab->SetAbsolute(false, false, false);
		PhysicsHandle->GrabComponent(toGrab, NAME_None, toGrab->GetOwner()->GetActorLocation(), true);
		GrabText->SetVisibility(false);
	};
}
void UGrabber::Release(){
	//UE_LOG(LogTemp, Error, TEXT("GrabReleased"))
	PhysicsHandle->ReleaseComponent();
}

FHitResult UGrabber::HitResult(FVector _Vector, FRotator _Rotation){
	FVector lineTraceEnd = _Vector + (_Rotation.Vector().GetSafeNormal() *fReach);
	//DrawDebugLine(GetWorld(), _Vector, lineTraceEnd, FColor(0, 255, 255), false, 0.f, 0.f, 10.f);
	FCollisionQueryParams TraceParams(FName(" "), false, GetOwner());
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(OUT Hit,
		_Vector,
		lineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
		);

	if (Hit.GetActor()){
		ShowGUI(Hit.GetActor());
	}
	else{
		GrabText->SetVisibility(false, true);
	}

	return Hit;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	PlayerViewPointLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetPawnViewLocation();
	PlayerViewPointRotation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetPawnViewLocation().Rotation();
	//HitResult(PlayerViewPointLocation, PlayerViewPointRotation);
	FVector lineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() *fReach);;
	auto Hit = HitResult(PlayerViewPointLocation, PlayerViewPointRotation);
	if (PhysicsHandle->GrabbedComponent){

		PhysicsHandle->SetTargetLocation(lineTraceEnd + FVector(0.f, 0.f, 50.f));
	}
	// ...
}
void UGrabber::ShowGUI(AActor* a){
	GrabText->SetRelativeLocation(a->GetActorLocation() + FVector(0.f, 0.f, 100.f));
	GrabText->SetRelativeRotation(a->GetTransform().GetRotation()*PlayerViewPointRotation.Quaternion());
	GrabText->SetVisibility(true);
}

