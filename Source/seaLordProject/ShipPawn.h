// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ShipPawn.generated.h"

class UFloatingPawnMovement;
class UCameraComponent;
class USpringArmComponent;
class UBuoyancyComponent;
UCLASS()
class SEALORDPROJECT_API AShipPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShipPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Accelerate();
	void Brake();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Steer(float Value);
	void LookX(float Value);
	void LookY(float Value);
	void Shoot();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USpringArmComponent* m_springArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UCameraComponent* m_camera;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* m_shipMesh;
	UPROPERTY(EditAnywhere)
	UBuoyancyComponent* m_buoyancy;
	UPROPERTY(EditAnywhere)
	UFloatingPawnMovement* m_movement;

	UPROPERTY(EditAnywhere)
	float m_maxVelocity;
	float m_currentVelocity;

	bool m_isAccelerating;
	bool m_isBraking;

	UPROPERTY(EditAnywhere)
	float m_accelerationRate;
	UPROPERTY(EditAnywhere)
	float m_brakeRate;
	UPROPERTY(EditAnywhere)
	float m_dampingRate;
	UPROPERTY(EditAnywhere)
	float m_steeringRate;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FVector GetForwardVector();
};
