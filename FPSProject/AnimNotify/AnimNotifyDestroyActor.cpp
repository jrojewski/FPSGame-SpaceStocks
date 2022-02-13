#include "AnimNotifyDestroyActor.h"

void UAnimNotifyDestroyActor::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	MeshComp->GetOwner()->Destroy();
}