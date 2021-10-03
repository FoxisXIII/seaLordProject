// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipController.h"

#include "ShipPawn.h"

void AShipController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Accelerate", IE_Pressed, this, &AShipController::Accelerate);
	InputComponent->BindAction("Accelerate", IE_Released, this, &AShipController::Accelerate);

	InputComponent->BindAction("Brake", IE_Pressed, this, &AShipController::Brake);
	InputComponent->BindAction("Brake", IE_Released, this, &AShipController::Brake);

	InputComponent->BindAction("Shoot", IE_Pressed, this, &AShipController::Shoot);

	InputComponent->BindAxis("Steer", this, &AShipController::Steer);
	InputComponent->BindAxis("LookX", this, &AShipController::LookX);
	InputComponent->BindAxis("LookY", this, &AShipController::LookY);
}

void AShipController::BeginPlay()
{
	Super::BeginPlay();
	m_shipPawn = Cast<AShipPawn>(GetPawn());
}

void AShipController::Accelerate()
{
	if (!m_shipPawn)return;

	m_shipPawn->Accelerate();
}

void AShipController::Brake()
{
	if (!m_shipPawn)return;

	m_shipPawn->Brake();
}

void AShipController::Shoot()
{
	if (!m_shipPawn)return;

	m_shipPawn->Shoot();
}

void AShipController::Steer(float value)
{
	if (!m_shipPawn) return;

	m_shipPawn->Steer(value);
}

void AShipController::LookX(float value)
{
	if (!m_shipPawn) return;

	m_shipPawn->LookX(value);
}

void AShipController::LookY(float value)
{
	if (!m_shipPawn) return;

	m_shipPawn->LookY(value);
}