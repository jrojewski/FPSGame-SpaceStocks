#include "AnimNotify_EnableShooting.h"
#include "FPS_PlayerCharacter.h"

void UAnimNotify_EnableShooting::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	if (Cast<AFPS_PlayerCharacter>(MeshComp->GetOwner()) == nullptr) return;

	AFPS_PlayerCharacter* Player = Cast<AFPS_PlayerCharacter>(MeshComp->GetOwner());

	Player->bCanShoot = true;
}