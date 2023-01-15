// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	
	void HandleDestruction();

protected:
	void RotateTurret(FVector LookAtTarget);

	void Fire();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

private:
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Effects")
	class UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, category = "Effects");
	class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;
};
