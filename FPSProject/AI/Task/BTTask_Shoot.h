#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ShootingEnemy.h"
#include "BTTask_Shoot.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API UBTTask_Shoot : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_Shoot();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	AShootingEnemy* Character;
};
