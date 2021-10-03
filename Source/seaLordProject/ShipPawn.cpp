// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipPawn.h"
#include "BuoyancyComponent.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AShipPawn::AShipPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_shipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = m_shipMesh;

	m_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	m_springArm->SetupAttachment(m_shipMesh);

	m_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_camera->SetupAttachment(m_springArm);
	m_camera->Activate();

	m_buoyancy = CreateDefaultSubobject<UBuoyancyComponent>(TEXT("Buoyancy"));
	m_movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
}

// Called when the game starts or when spawned
void AShipPawn::BeginPlay()
{
	Super::BeginPlay();
}

FVector AShipPawn::GetForwardVector()
{
	FVector l_forward = -GetActorRightVector();
	if (l_forward.Z < 0) l_forward.Z = 0;
	return l_forward;
}

void AShipPawn::Accelerate()
{
	m_isAccelerating = !m_isAccelerating;
}

void AShipPawn::Brake()
{
	m_isBraking = !m_isBraking;
}

void AShipPawn::Shoot()
{
	UE_LOG(LogTemp, Warning, TEXT("SHOOT"));
	// DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + 1000 * m_camera->GetForwardVector(), FColor::Red,
	//               false);
}

// Called every frame
void AShipPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_isAccelerating && !m_isBraking)
		m_currentVelocity = FMath::Min(m_currentVelocity + m_maxVelocity * DeltaTime * m_accelerationRate,
		                               m_maxVelocity);
	else if (!m_isAccelerating && !m_isBraking)
		m_currentVelocity = FMath::Max(m_currentVelocity - m_maxVelocity * DeltaTime * m_dampingRate, 0.f);
	else
		m_currentVelocity = FMath::Max(m_currentVelocity - m_maxVelocity * DeltaTime * m_brakeRate, 0.f);

	m_movement->Velocity = GetForwardVector() * m_currentVelocity;
	DrawDebugLine(GetWorld(), m_shipMesh->GetComponentLocation(), m_shipMesh->GetComponentLocation() + 1000 * GetForwardVector(), FColor::Red,
			false,DeltaTime,10,10);
}

// Called to bind functionality to input
void AShipPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AShipPawn::Steer(float Value)
{
	m_shipMesh->AddLocalRotation(
		FRotator(
			0,
			m_steeringRate * Value * (1 - (0.5 * (m_currentVelocity / m_maxVelocity))) * GetWorld()->DeltaTimeSeconds,
			0));
}

void AShipPawn::LookX(float Value)
{
	m_springArm->AddLocalRotation(
		FRotator(
			0,
			m_steeringRate * Value * GetWorld()->DeltaTimeSeconds,
			0));
}

void AShipPawn::LookY(float Value)
{
	// m_springArm->AddLocalRotation(
	// 	FRotator(
	// 		m_steeringRate * Value * GetWorld()->DeltaTimeSeconds),
	// 		0,
	// 		0
	// 		);
}
