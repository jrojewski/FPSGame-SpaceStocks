#include "AnimNotifyState_MeleeAttack.h"
#include "MeleeEnemy.h"

void UAnimNotifyState_MeleeAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) {
	AMeleeEnemy* MeleeEnemy = Cast<AMeleeEnemy>(MeshComp->GetOwner());
	if (MeleeEnemy == nullptr) return;

	MeleeEnemy->MeleeBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void UAnimNotifyState_MeleeAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	AMeleeEnemy* MeleeEnemy = Cast<AMeleeEnemy>(MeshComp->GetOwner());
	if (MeleeEnemy == nullptr) return;

	MeleeEnemy->MeleeBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}