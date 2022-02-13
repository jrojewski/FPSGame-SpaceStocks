#include "BTTask_DecreaseSpeed.h"
#include "MeleeEnemy.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_DecreaseSpeed::UBTTask_DecreaseSpeed() {
	NodeName = TEXT("DecreaseSpeed");
}

EBTNodeResult::Type UBTTask_DecreaseSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr) {
		return EBTNodeResult::Failed;
	}

	Character = Cast<AMeleeEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (Character == nullptr) {
		return EBTNodeResult::Failed;
	}

	Character->GetCharacterMovement()->MaxWalkSpeed = 600;

	return EBTNodeResult::Succeeded;
}
