#include "AnimNotify_DisableShooting.h"
#include "FPS_PlayerCharacter.h"

void UAnimNotify_DisableShooting::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {	
	if (Cast<AFPS_PlayerCharacter>(MeshComp->GetOwner()) == nullptr) return;

	AFPS_PlayerCharacter* Player = Cast<AFPS_PlayerCharacter>(MeshComp->GetOwner());

	Player->bCanShoot = false;
}