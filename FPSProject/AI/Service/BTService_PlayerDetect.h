#pragma once

#include "Enemy.h"
#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerDetect.generated.h"

UCLASS()
class FPSPROJECT_API UBTService_PlayerDetect : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_PlayerDetect();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	AActor* CurrentAttacker;
	APawn* PlayerPawn;
	AAIController* CurrentAIController;
};
