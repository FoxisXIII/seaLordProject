// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ShipPawn.generated.h"

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
    
    	// Called to bind functionality to input
    	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USpringArmComponent* m_springArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UCameraComponent* m_camera;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* m_shipMesh;
	UPROPERTY(EditAnywhere)
	UBuoyancyComponent* m_buoyancy;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
