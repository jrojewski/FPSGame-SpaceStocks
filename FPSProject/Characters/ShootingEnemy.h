#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "ShootingEnemy.generated.h"

UCLASS()
class FPSPROJECT_API AShootingEnemy : public AEnemy
{
	GENERATED_BODY()
	
public:
	void Shoot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;

private:

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000;

	UPROPERTY(EditAnywhere)
	float Damage = 20;
};
