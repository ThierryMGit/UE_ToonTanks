// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

	public:
		ATank();

		// Called to bind functionality to input
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

		// Called every frame
		virtual void Tick(float DeltaTime) override;

		void HandleDestruction();

		APlayerController* GetTankPlayerController() { return TankPlayerController; };

		bool bAlive;

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	private:
		UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArm;

		UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;

		UPROPERTY(EditAnyWhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float Speed;

		UPROPERTY(EditAnyWhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float TurnRate;

		APlayerController* TankPlayerController;

	private:
		void Move(float Value);
		void Rotate(float Value);
};
