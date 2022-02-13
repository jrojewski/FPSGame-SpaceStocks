#include "AnimNotify_EnableAiming.h"
#include "FPS_PlayerCharacter.h"

void UAnimNotify_EnableAiming::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	if (Cast<AFPS_PlayerCharacter>(MeshComp->GetOwner()) == nullptr) return;

	AFPS_PlayerCharacter* Player = Cast<AFPS_PlayerCharacter>(MeshComp->GetOwner());

	Player->bCanAim = true;
}