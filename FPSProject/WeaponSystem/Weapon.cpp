#include "Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/SkeletalMeshSocket.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	AnimInstance = Mesh->GetAnimInstance();
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AWeapon::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr) return false;

	FVector CameraLocation;
	FRotator CameraRotation;
	OwnerController->GetPlayerViewPoint(CameraLocation, CameraRotation);
	ShotDirection = -CameraRotation.Vector();

	FVector End = CameraLocation + CameraRotation.Vector() * MaxRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(Hit, CameraLocation, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

void AWeapon::PullTrigger()
{
	bCanShoot = false;

	NumOfBullets = FMath::Clamp(--NumOfBullets, 0, MaxNumOfBullets);

	if (NumOfBullets > 0)
	{

		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"), FVector((FVector)(ForceInit)), FRotator(90, 0, 0)); 
		UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));
		FHitResult Hit;
		FVector ShotDirection;
		bool bSuccess = GunTrace(Hit, ShotDirection);
		if (bSuccess)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, Hit.Location, ShotDirection.Rotation());

			AActor* DamageReceiver = Hit.GetActor();
			if (DamageReceiver != nullptr)
			{
				FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
				AController* OwnerController = GetOwnerController();
				DamageReceiver->TakeDamage(Damage, DamageEvent, OwnerController, this);
			}
		}
	}
	else {
		if (AnimInstance != nullptr) {
			AnimInstance->Montage_Play(EmptyWeaponAnimation);
		}
		UGameplayStatics::SpawnSound2D(GetWorld(), EmptySound);;
	}

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AWeapon::FireReset, FireRate);
}

void AWeapon::Reload() {
	bCanShoot = false;

	if (AnimInstance != nullptr) {
		AnimInstance->Montage_Play(WeaponReloadAnimation);
	}
	UGameplayStatics::SpawnSound2D(GetWorld(), ReloadSound);
	
	GetWorldTimerManager().SetTimer(ReloadTimerHandle, this, &AWeapon::FireReset, ReloadTime);
	NumOfBullets = MaxNumOfBullets;
}

void AWeapon::FireReset() {
	bCanShoot = true;
}

int AWeapon::GetNumOfBullets() {
	return this->NumOfBullets;
}

void AWeapon::SetNumOfBullets(int NewNumOfBullets) {
	this->NumOfBullets = NewNumOfBullets;
}

int AWeapon::GetMaxNumOfBullets() {
	return this->MaxNumOfBullets;
}

UAnimInstance* AWeapon::GetAnimInstance() {
	return this->AnimInstance;
}

AController* AWeapon::GetOwnerController() const {
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return nullptr;
	return OwnerPawn->GetController();
}