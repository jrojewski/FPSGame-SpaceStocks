#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "NavigationSystem.h"
#include "BTTask_FindRandomPoint.generated.h"

UCLASS()
class FPSPROJECT_API UBTTask_FindRandomPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_FindRandomPoint();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UNavigationSystemV1* navSystem;
	FVector startPos;
	FNavLocation endPos;
};
