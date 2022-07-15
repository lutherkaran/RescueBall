// Fill out your copyright notice in the Description page of Project Settings.

#include "RescueBall.h"
#include "Ball.h"
#include "GameWinning.h"


// Sets default values
AGameWinning::AGameWinning()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameWinning::BeginPlay()
{
	Super::BeginPlay();
	if (GameWinWidget)
	{
		//UE_LOG(LogTemp, Warning, TEXT("GAME OVER"));
		GameWinWidgetInstance = CreateWidget<UUserWidget>(this->GetGameInstance(), GameWinWidget);
		GameWinWidgetInstance->AddToViewport();
		GameWinWidgetInstance->SetVisibility(ESlateVisibility::Hidden);

	}
	if (!TriggerVolume){ UE_LOG(LogTemp, Warning, TEXT("MISSING TRIGGER VOLUME")) }
	player = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void AGameWinning::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TriggerVolume->IsOverlappingActor(player)){
		
		isWon = true;
		ShowWidget();
	}
	else{ isWon = false; }
}
void AGameWinning::ShowWidget(){
	if (isWon){
		if (GameWinWidgetInstance){
			InputModeData.SetLockMouseToViewport(true);
			GetWorld()->GetFirstPlayerController()->SetInputMode(InputModeData);
			GameWinWidgetInstance->SetVisibility(ESlateVisibility::Visible);
			GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

			player->Destroy(true);
		}

	}

}

