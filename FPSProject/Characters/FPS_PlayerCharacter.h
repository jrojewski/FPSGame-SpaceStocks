#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Components/TimelineComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ChildActorComponent.h"
#include "Weapon.h"

#include "FPS_PlayerCharacter.generated.h"

class UWeaponLocation;

UCLASS()
class FPSPROJECT_API AFPS_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPS_PlayerCharacter();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsHandlingPrimaryWeapon = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsReloading = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsSprinting = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsAiming = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanShoot = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanAim = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsJumping = false;

	UFUNCTION()
	void FireReset();

	UFUNCTION(BlueprintPure)
	FText GetHealthIntText() const;

	UFUNCTION(BlueprintPure)
	FText GetCurrentAmmoIntText() const;

	UFUNCTION(BlueprintPure)
	FText GetMaxAmmoIntText() const;

	UFUNCTION(BlueprintPure)
	ESlateVisibility GetCrosshairVisibility() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* HandsMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsTakingDMG = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Shoot(float AxisValue);
	void WeaponReload();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AWeapon* Weapon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AWeapon* HiddenWeapon;

	UFUNCTION(BlueprintCallable)
	void AimOn();
	UFUNCTION(BlueprintCallable)
	void AimOff();

	UPROPERTY(EditAnywhere)
	FTransform LeftHandSocketTransform;

	UPROPERTY(EditAnywhere)
	FRotator InRot = FRotator(0, 0, 0);

	UPROPERTY(EditAnywhere)
	FRotator OutRot;

private:
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100;

	UPROPERTY(EditAnywhere)
	float Health;

	UPROPERTY()
	UAnimInstance* AnimInstance;

	UPROPERTY()
	UAnimInstance* WeaponAnimInstance;

	UPROPERTY(EditAnywhere)
	USoundBase* TakeDamageSound;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	void SprintStart();
	void SprintStop();

	void ChangeToPrimaryWeapon();
	void ChangeToSecondaryWeapon();
	void SwitchToPrimaryWeapon();
	void SwitchToSecondaryWeapon();

	void Escape();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> PrimaryWeaponClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> SecondaryWeaponClass;

	UPROPERTY(EditAnywhere)
	UCurveFloat* CameraInCurve;
	UPROPERTY(EditAnywhere)
	UCurveFloat* CameraOutCurve;

	FTimeline InTimeline;
	FTimeline OutTimeline;

	UFUNCTION()
	void AimOnCameraMovement();
	UFUNCTION()
	void AimOffCameraMovement();

	FTimerHandle IsTakingDMGTimerHandle;
	FTimerHandle IsReloadingTimerHandle;
	FTimerHandle SwitchWeaponTimerHandle;
	FTimerHandle RestartLevelTimerHandle;

	UFUNCTION()
	void ResetIsTakingDMG();

	UFUNCTION()
	void ResetIsReloading();
};
