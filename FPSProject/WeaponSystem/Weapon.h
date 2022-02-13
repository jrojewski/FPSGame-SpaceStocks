// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class FPSPROJECT_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	bool bCanShoot = true;

	void PullTrigger();
	void FireReset();
	void Reload();

	int GetNumOfBullets();
	int GetMaxNumOfBullets();
	void SetNumOfBullets(int NewNumOfBullets);

	UPROPERTY(EditAnywhere, Category = "Combat specification")
	float FireRate = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Combat specification")
	float ReloadTime;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* DrawAnimation;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* HideAnimation;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* ShootAnimation;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* AimShootAnimation;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* ReloadAnimation;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* AimReloadAnimation;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* FireWeaponAnimation;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* LoadedWeaponAnimation;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* EmptyWeaponAnimation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	FName WeaponKind;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USkeletalMeshComponent* Mesh;

	UFUNCTION()
	UAnimInstance* GetAnimInstance();

private:
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	UParticleSystem* HitEffect;

	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere)
	USoundBase* ReloadSound;

	UPROPERTY()
	UAnimInstance* AnimInstance;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* WeaponReloadAnimation;

	UPROPERTY(EditAnywhere)
	USoundBase* EmptySound;

	UPROPERTY(EditAnywhere, Category = "Combat specification")
	float Damage;

	UPROPERTY(EditAnywhere, Category = "Combat specification")
	int MaxNumOfBullets;

	UPROPERTY(EditAnywhere, Category = "Combat specification")
	int NumOfBullets;

	FTimerHandle FireRateTimerHandle;
	FTimerHandle ReloadTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Combat specification")
	float MaxRange;

	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);

	AController* GetOwnerController() const;
};
