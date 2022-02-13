#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Components/BoxComponent.h"
#include "MeleeEnemy.generated.h"

UCLASS()
class FPSPROJECT_API AMeleeEnemy : public AEnemy
{
	GENERATED_BODY()

public:
	AMeleeEnemy();

	void Attack();

	UPROPERTY(EditAnywhere)
	UBoxComponent* MeleeBox;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* AttackAnimation;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float Damage = 50;

	UFUNCTION()
	void OnOverlapDealDamage(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
