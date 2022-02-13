#include "FPS_PlayerCharacter.h"
#include "Weapon.h"
#include "WeaponLocation.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FPS_HUD.h"
#include "FPS_PlayerController.h"

// Sets default values
AFPS_PlayerCharacter::AFPS_PlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetCapsuleComponent());
	Camera->bUsePawnControlRotation = true;

	HandsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandsMesh"));
	HandsMesh->SetupAttachment(Camera);
}

// Called when the game starts or when spawned
void AFPS_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Weapon = GetWorld()->SpawnActor<AWeapon>(PrimaryWeaponClass);
	Weapon->AttachToComponent(HandsMesh, FAttachmentTransformRules::FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false), TEXT("WeaponSocket"));
	Weapon->SetOwner(this);
	Weapon->SetActorEnableCollision(false);

	HiddenWeapon = GetWorld()->SpawnActor<AWeapon>(SecondaryWeaponClass);
	HiddenWeapon->AttachToComponent(HandsMesh, FAttachmentTransformRules::FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false), TEXT("SecondaryWeaponSocket"));
	HiddenWeapon->SetOwner(this);
	HiddenWeapon->SetActorEnableCollision(false);
	HiddenWeapon->Mesh->SetVisibility(false);

	Health = MaxHealth;

	bCanShoot = false;
	bCanAim = false;
	bIsReloading = false;
	bIsSprinting = false;
	bIsAiming = false;
	bIsJumping = false;

	Cast<AFPS_PlayerController>(GetController())->CallHUD();

	AnimInstance = HandsMesh->GetAnimInstance();
	WeaponAnimInstance = Weapon->GetAnimInstance();

	if (AnimInstance != nullptr) {
		//Drawing time of weapon at the start of the game is LONGER than usual
		float DrawTime = AnimInstance->Montage_Play(Weapon->DrawAnimation, 0.1f) / 0.1f;
		GetWorldTimerManager().SetTimer(SwitchWeaponTimerHandle, this, &AFPS_PlayerCharacter::FireReset, DrawTime);
	}

	if (CameraInCurve)
	{
		FOnTimelineFloat InTimelineCallback;

		InTimelineCallback.BindUFunction(this, FName("AimOnCameraMovement"));
		InTimeline.AddInterpFloat(CameraInCurve, InTimelineCallback);
	}

	if (CameraOutCurve)
	{
		FOnTimelineFloat OutTimelineCallback;

		OutTimelineCallback.BindUFunction(this, FName("AimOffCameraMovement"));
		OutTimeline.AddInterpFloat(CameraOutCurve, OutTimelineCallback);
	}
}

// Called every frame
void AFPS_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InTimeline.TickTimeline(DeltaTime);
	OutTimeline.TickTimeline(DeltaTime);
}

// Called to bind functionality to input
void AFPS_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("LookUpDown"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRightLeft"), this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AFPS_PlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AFPS_PlayerCharacter::MoveRight);

	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Pressed, this, &AFPS_PlayerCharacter::SprintStart);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Released, this, &AFPS_PlayerCharacter::SprintStop);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAxis(TEXT("Shoot"), this, &AFPS_PlayerCharacter::Shoot);

	PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Pressed, this, &AFPS_PlayerCharacter::AimOn);
	PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Released, this, &AFPS_PlayerCharacter::AimOff);

	PlayerInputComponent->BindAction(TEXT("PrimaryWeapon"), EInputEvent::IE_Pressed, this, &AFPS_PlayerCharacter::ChangeToPrimaryWeapon);
	PlayerInputComponent->BindAction(TEXT("SecondaryWeapon"), EInputEvent::IE_Pressed, this, &AFPS_PlayerCharacter::ChangeToSecondaryWeapon);
	PlayerInputComponent->BindAction(TEXT("WeaponReload"),EInputEvent::IE_Pressed, this, &AFPS_PlayerCharacter::WeaponReload);

	PlayerInputComponent->BindAction(TEXT("Esc"), EInputEvent::IE_Pressed, this, &AFPS_PlayerCharacter::Escape);
}

void AFPS_PlayerCharacter::Shoot(float AxisValue)
{
	if (this->bCanShoot == false) return;

	if (AxisValue && Weapon->bCanShoot)
	{
		if (bIsSprinting == true) {
			SprintStop();
		}

		if (Weapon->GetNumOfBullets() != 0) {
			if (bIsAiming == true) {
				if (AnimInstance != nullptr) {
					AnimInstance->Montage_Play(Weapon->AimShootAnimation);
					if (WeaponAnimInstance != nullptr) {
						WeaponAnimInstance->Montage_Play(Weapon->FireWeaponAnimation);
					}
				}
			}
			else {
				if (AnimInstance != nullptr) {
					AnimInstance->Montage_Play(Weapon->ShootAnimation);
					if (WeaponAnimInstance != nullptr) {
						WeaponAnimInstance->Montage_Play(Weapon->FireWeaponAnimation);
					}
				}
			}
		}

		Weapon->PullTrigger();
	};
}

void AFPS_PlayerCharacter::AimOn() {
	if (bCanAim == false) return;

	bIsAiming = true;

	GetCharacterMovement()->MaxWalkSpeed = 300;

	InTimeline.PlayFromStart();
}

void AFPS_PlayerCharacter::AimOnCameraMovement() {
	float InTimelineValue = InTimeline.GetPlaybackPosition();

	if (CameraInCurve == nullptr) return;
	
	float InCurveFloatValue = CameraInCurve->GetFloatValue(InTimelineValue);

	Camera->SetFieldOfView(InCurveFloatValue);
}

void AFPS_PlayerCharacter::AimOff() {
	if (bIsAiming == false) return;

	bIsAiming = false;

	GetCharacterMovement()->MaxWalkSpeed = 600;

	OutTimeline.PlayFromStart();
}

void AFPS_PlayerCharacter::AimOffCameraMovement() {
	float OutTimelineValue = OutTimeline.GetPlaybackPosition();

	if (CameraOutCurve == nullptr) return;

	float OutCurveFloatValue = CameraOutCurve->GetFloatValue(OutTimelineValue);

	Camera->SetFieldOfView(OutCurveFloatValue);
}

void AFPS_PlayerCharacter::ChangeToPrimaryWeapon() {
	if (Weapon->WeaponKind == TEXT("Primary")) return;

	bCanShoot = false;
	bCanAim = false;

	if (AnimInstance != nullptr) {
		float HideTime = AnimInstance->Montage_Play(Weapon->HideAnimation);
		GetWorldTimerManager().SetTimer(SwitchWeaponTimerHandle, this, &AFPS_PlayerCharacter::SwitchToPrimaryWeapon, HideTime);
	}
}

void AFPS_PlayerCharacter::ChangeToSecondaryWeapon() {
	if (Weapon->WeaponKind == TEXT("Secondary")) return;

	bCanShoot = false;
	bCanAim = false;

	if (AnimInstance != nullptr) {
		float HideTime = AnimInstance->Montage_Play(Weapon->HideAnimation);
		GetWorldTimerManager().SetTimer(SwitchWeaponTimerHandle, this, &AFPS_PlayerCharacter::SwitchToSecondaryWeapon, HideTime);
	}
}

void AFPS_PlayerCharacter::SwitchToPrimaryWeapon() {
	Weapon->Mesh->SetVisibility(false);

	AWeapon* tempWeapon = Weapon;
	Weapon = HiddenWeapon;
	HiddenWeapon = tempWeapon;

	bIsHandlingPrimaryWeapon = true;

	Weapon->Mesh->SetVisibility(true);
	WeaponAnimInstance = Weapon->GetAnimInstance();

	if (AnimInstance != nullptr) {
		float DrawTime = AnimInstance->Montage_Play(Weapon->DrawAnimation);
		GetWorldTimerManager().SetTimer(SwitchWeaponTimerHandle, this, &AFPS_PlayerCharacter::FireReset, DrawTime);
	}
}

void AFPS_PlayerCharacter::SwitchToSecondaryWeapon() {
	Weapon->Mesh->SetVisibility(false);

	AWeapon* tempWeapon = Weapon;
	Weapon = HiddenWeapon;
	HiddenWeapon = tempWeapon;

	bIsHandlingPrimaryWeapon = false;

	Weapon->Mesh->SetVisibility(true);
	WeaponAnimInstance = Weapon->GetAnimInstance();

	if (AnimInstance != nullptr) {
		float DrawTime = AnimInstance->Montage_Play(Weapon->DrawAnimation);
		GetWorldTimerManager().SetTimer(SwitchWeaponTimerHandle, this, &AFPS_PlayerCharacter::FireReset, DrawTime);
	}
}

void AFPS_PlayerCharacter::WeaponReload()
{
	if (bIsReloading == true) return;

	if (bIsSprinting == true) SprintStop();

	bIsReloading = true;
	HandsMesh->HideBoneByName("DEF-f_index_02_R", EPhysBodyOp::PBO_None);
	
	if (AnimInstance != nullptr) {
		if (bIsAiming) {
			AnimInstance->Montage_Play(Weapon->AimReloadAnimation);
		}
		else {
			bCanAim = false;
			AnimInstance->Montage_Play(Weapon->ReloadAnimation);
		}
	}

	Weapon->Reload();
	GetWorldTimerManager().SetTimer(IsReloadingTimerHandle, this, &AFPS_PlayerCharacter::ResetIsReloading, Weapon->ReloadTime);
}

void AFPS_PlayerCharacter::MoveForward(float AxisValue) 
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AFPS_PlayerCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AFPS_PlayerCharacter::SprintStart() {
	if (bIsAiming == true) {
		AimOff();
	};

	bIsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = 1200;
}

void AFPS_PlayerCharacter::SprintStop() {
	bIsSprinting = false;

	GetCharacterMovement()->MaxWalkSpeed = 600;
}

float AFPS_PlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	this->bIsTakingDMG = true;

	UGameplayStatics::SpawnSound2D(GetWorld(), TakeDamageSound);

	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;

	GetWorldTimerManager().SetTimer(IsTakingDMGTimerHandle, this, &AFPS_PlayerCharacter::ResetIsTakingDMG, 0.1f);

	//Death
	if (Health == 0) {
		//Call function from GameMode about ending the game

		Cast<AFPS_PlayerController>(GetController())->CallDeathScreen();
		GetWorldTimerManager().SetTimer(RestartLevelTimerHandle, Cast<APlayerController>(GetController()), &APlayerController::RestartLevel, 2.5f);
		DisableInput(Cast<APlayerController>(GetController()));
		DetachFromControllerPendingDestroy();
		Weapon->Destroy();
		Destroy();
	}

	return DamageToApply;
}

void AFPS_PlayerCharacter::ResetIsTakingDMG() {
	this->bIsTakingDMG = false;
}

void AFPS_PlayerCharacter::ResetIsReloading() {
	this->bIsReloading = false;
	this->bCanShoot = true;
	HandsMesh->UnHideBoneByName("DEF-f_index_02_R");
}

void AFPS_PlayerCharacter::FireReset() {
	this->bCanShoot = true;
	this->bCanAim = true;
}

FText AFPS_PlayerCharacter::GetHealthIntText() const
{
	FString HPS = FString::FromInt(Health);
	FText HPText = FText::FromString(HPS);
	return HPText;
}

FText AFPS_PlayerCharacter::GetCurrentAmmoIntText() const
{
	FString CurrentAmmoString = FString::FromInt(Weapon->GetNumOfBullets());
	FText CurrentAmmoText = FText::FromString(CurrentAmmoString);
	return CurrentAmmoText;
}

FText AFPS_PlayerCharacter::GetMaxAmmoIntText() const
{
	FString MaxAmmoString = FString::FromInt(Weapon->GetMaxNumOfBullets());
	FText MaxAmmoText = FText::FromString(MaxAmmoString);
	return MaxAmmoText;
}

ESlateVisibility AFPS_PlayerCharacter::GetCrosshairVisibility() const
{
	if (bIsAiming == true) return ESlateVisibility::Hidden;

	return ESlateVisibility::Visible;
}

void AFPS_PlayerCharacter::Escape()
{
	UWorld* World = GetWorld();
	if (World == nullptr) return;

	UGameplayStatics::OpenLevel(World, "MainMenu");

	return;
}