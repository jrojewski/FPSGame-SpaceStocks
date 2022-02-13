#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MeleeEnemy.h"
#include "BTTask_DecreaseSpeed.generated.h"

UCLASS()
class FPSPROJECT_API UBTTask_DecreaseSpeed : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_DecreaseSpeed();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	AMeleeEnemy* Character;
};
