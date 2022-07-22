// Fill out your copyright notice in the Description page of Project Settings.

#include "RescueBall.h"
#include "Ball.h"
#include "CountdownTimer.h"


// Sets default values
ACountdownTimer::ACountdownTimer()
{
	FString Timer = "TIMER";
	PrimaryActorTick.bCanEverTick = true;
	CountDownText = CreateDefaultSubobject<UTextRenderComponent>((TEXT("CountDownNumber")));
	CountDownText->SetText(FText(FText::FromString(Timer)));
	CountDownText->SetHorizontalAlignment(EHTA_Center);
	CountDownText->SetWorldSize(150.f);
	CountDownText->SetTextRenderColor(FColor(255, 0, 0));
	RootComponent = CountDownText;

}

// Called when the game starts or when spawned
void ACountdownTimer::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimeHandler, this, &ACountdownTimer::AdvanceTimer, 1.0f, true);
	if (GameOverWidget)
	{
		//UE_LOG(LogTemp, Warning, TEXT("GAME OVER"));
		GameOverWidgetInstance = CreateWidget<UUserWidget>(this->GetGameInstance(), GameOverWidget);
		GameOverWidgetInstance->AddToViewport();
		GameOverWidgetInstance->SetVisibility(ESlateVisibility::Hidden);

	}

}

// Called every frame
void ACountdownTimer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ACountdownTimer::UpdateTimerDisplay()
{
	CountDownText->SetText(FText::FromString(FString::FromInt(FMath::Max(CountdownTime, 0))));
}

void ACountdownTimer::AdvanceTimer()
{
	--CountdownTime;
	UpdateTimerDisplay();
	if (CountdownTime < 1)
	{
		GetWorldTimerManager().ClearTimer(TimeHandler);
		CountDownHasFinished();
	}

}
void ACountdownTimer::CountDownHasFinished(){



	if (GameOverWidgetInstance){

		GameOverWidgetInstance->SetVisibility(ESlateVisibility::Visible);
		InputModeData.SetLockMouseToViewport(true);
		GetWorld()->GetFirstPlayerController()->SetInputMode(InputModeData);
		GetWorld()->GetFirstPlayerController()->DisableInput(GetWorld()->GetFirstPlayerController());
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

		for (TObjectIterator<ABall> It; It; ++It)
		{
			if (It)
				It->fSpeed = 0;
		}
	}
	//GetWorld()->GetFirstPlayerController()->ConsoleCommand("RestartLevel");
}

