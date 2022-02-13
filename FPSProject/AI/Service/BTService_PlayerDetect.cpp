#include "BTService_PlayerDetect.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "FPS_PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_PlayerDetect::UBTService_PlayerDetect() {
	NodeName = TEXT("Player Detect");

	CurrentAttacker = nullptr;
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void UBTService_PlayerDetect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (OwnerComp.GetAIOwner() == nullptr) return;
	CurrentAIController = OwnerComp.GetAIOwner();

	if (CurrentAIController->GetPawn() == nullptr) return;

	if (Cast<AEnemy>(CurrentAIController->GetPawn())->Attacker != nullptr) {
		CurrentAttacker = PlayerPawn;

		OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), CurrentAttacker);
	}

	if ( OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn)) {
		CurrentAttacker = PlayerPawn;

		OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), CurrentAttacker);

	}	else {
		CurrentAttacker = nullptr;

		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}	