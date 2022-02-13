// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomPoint.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindRandomPoint::UBTTask_FindRandomPoint() {
	NodeName = TEXT("Find Random Point");
}

EBTNodeResult::Type UBTTask_FindRandomPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	if (GetWorld()) {
		navSystem = UNavigationSystemV1::GetCurrent(GetWorld());
		if (navSystem != nullptr) {
			startPos = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
			endPos = FNavLocation(startPos);
			if (navSystem->GetRandomReachablePointInRadius(startPos, 10000, endPos)) {

				OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), endPos.Location);
			}
		}
	}
	return EBTNodeResult::Succeeded;
}