// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShipPawn.h"
#include "GameFramework/PlayerController.h"
#include "ShipController.generated.h"

/**
 * 
 */
UCLASS()
class SEALORDPROJECT_API AShipController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	void Accelerate();
	void Brake();
	void Shoot();
	void Steer(float value);
	void LookX(float value);
	void LookY(float value);
	AShipPawn* m_shipPawn;
};
