#include "MeleeEnemy.h"
#include "GameFramework/Pawn.h"

AMeleeEnemy::AMeleeEnemy() {
	PrimaryActorTick.bCanEverTick = false;

	MeleeBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MeleeBox"));
	MeleeBox->SetupAttachment(GetCapsuleComponent());
}

void AMeleeEnemy::BeginPlay() {
	Super::BeginPlay();

	MeleeBox->OnComponentBeginOverlap.AddDynamic(this, &AMeleeEnemy::OnOverlapDealDamage);
}

void AMeleeEnemy::Attack() {
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance != nullptr) {
		AnimInstance->Montage_Play(AttackAnimation, 1.f);
	}
}

void AMeleeEnemy::OnOverlapDealDamage(UPrimitiveComponent* OverlappedComponent,
									class AActor* OtherActor, 
									class UPrimitiveComponent* OtherComp, 
									int32 OtherBodyIndex, 
									bool bFromSweep, 
									const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("OverlapBegin"));
	if (OtherActor && (OtherActor != this) && OtherComp) {
		FDamageEvent DamageEvent;
		OtherActor->TakeDamage(Damage, DamageEvent, GetController(), this);
	}
}