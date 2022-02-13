#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MeleeEnemy.h"
#include "BTTask_IncreaseSpeed.generated.h"

UCLASS()
class FPSPROJECT_API UBTTask_IncreaseSpeed : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_IncreaseSpeed();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	AMeleeEnemy* Character;
};
