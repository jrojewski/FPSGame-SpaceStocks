// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingEnemy.h"
#include "Kismet/GameplayStatics.h"

void AShootingEnemy::Shoot() {
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance != nullptr) {
		AnimInstance->Montage_Play(FireAnimation, 1.f);
	}

	FHitResult Hit;
	FVector ShotDirection;

	FVector CameraLocation;
	FRotator CameraRotation;


	AController* OwnerController = GetController();
	if (OwnerController == nullptr) return;
	OwnerController->GetPlayerViewPoint(CameraLocation, CameraRotation);
	ShotDirection = -CameraRotation.Vector();

	FVector End = CameraLocation + CameraRotation.Vector() * MaxRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, CameraLocation, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
	if (bSuccess)
	{

		AActor* DamageReceiver = Hit.GetActor();
		if (DamageReceiver != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			DamageReceiver->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
}