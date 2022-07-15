// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "GameWinning.generated.h"

UCLASS()

class RESCUEBALL_API AGameWinning : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGameWinning();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	UPROPERTY(EditAnywhere)
		ATriggerVolume *TriggerVolume;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		TSubclassOf<class UUserWidget> GameWinWidget;
	UUserWidget* GameWinWidgetInstance;
	FInputModeUIOnly InputModeData;
	bool isWon = false;
	void ShowWidget();
	AActor* player;

};
