// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "CountdownTimer.generated.h"

UCLASS()

class RESCUEBALL_API ACountdownTimer : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACountdownTimer();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> GameOverWidget;
	UUserWidget* GameOverWidgetInstance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 CountdownTime = 120;
private:
	
	UPROPERTY(EditAnywhere)
		UTextRenderComponent* CountDownText = nullptr;
	FTimerHandle TimeHandler;
	FInputModeUIOnly InputModeData;
	void UpdateTimerDisplay();
	void AdvanceTimer();
	void CountDownHasFinished();
};
