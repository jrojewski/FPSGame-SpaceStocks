#include "AnimNotify_ShootEffects.h"
#include "ShootingEnemy.h"
#include "Kismet/GameplayStatics.h"

void UAnimNotify_ShootEffects::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{ 
	AShootingEnemy* ShootingEnemy = Cast<AShootingEnemy>(MeshComp->GetOwner());
	UParticleSystem* ParticleEffect = ShootingEnemy->MuzzleFlash;
	USoundBase* SoundEffect = ShootingEnemy->MuzzleSound;

	UGameplayStatics::SpawnEmitterAttached(ParticleEffect, MeshComp, TEXT("Muzzle_01"), FVector((FVector)(ForceInit)), FRotator(90, 0, 0));
	UGameplayStatics::SpawnSoundAttached(SoundEffect, MeshComp, TEXT("Muzzle_01"));
}