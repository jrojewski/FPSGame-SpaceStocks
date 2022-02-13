#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Enemy.generated.h"

UCLASS()
class FPSPROJECT_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere)
	AActor* Attacker = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsTakingDMG = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsAttacking = false;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UPROPERTY(EditAnywhere)
	float MaxHealth = 100;

	UPROPERTY(EditAnywhere)
	float Health;

	FTimerHandle IsTakingDMGTimerHandle;

	UFUNCTION()
	void ResetIsTakingDMG();
};
