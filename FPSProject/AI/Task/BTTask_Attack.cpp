#include "BTTask_Attack.h"
#include "MeleeEnemy.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_Attack::UBTTask_Attack() {
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr) {
		return EBTNodeResult::Failed;
	}

	Character = Cast<AMeleeEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (Character == nullptr) {
		return EBTNodeResult::Failed;
	}

	Character->Attack();

	return EBTNodeResult::Succeeded;
}