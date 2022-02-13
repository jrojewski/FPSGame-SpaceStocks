#include "BTTask_IncreaseSpeed.h"
#include "MeleeEnemy.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_IncreaseSpeed::UBTTask_IncreaseSpeed() {
	NodeName = TEXT("IncreaseSpeed");
}

EBTNodeResult::Type UBTTask_IncreaseSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr) {
		return EBTNodeResult::Failed;
	}

	Character = Cast<AMeleeEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (Character == nullptr) {
		return EBTNodeResult::Failed;
	}

	Character->GetCharacterMovement()->MaxWalkSpeed = 1600;

	return EBTNodeResult::Succeeded;
}