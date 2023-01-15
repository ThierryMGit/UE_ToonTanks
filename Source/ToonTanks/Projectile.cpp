// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile(): Damage(50.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System Component"));
	ParticleSystemComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	BaseMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if(LaunchSound) {
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}
	if(HitCameraShakeClass) {
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
	}
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();
	if (!MyOwner) {
		Destroy();
		return;
	}

	UClass* DamageType = UDamageType::StaticClass();
	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();

	if(OtherActor && OtherActor != this && OtherActor != MyOwner) {
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageType);
		if(HitParticles) {
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation(), true);
		}
	}
	if(HitSound) {
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	}
	Destroy();
}



