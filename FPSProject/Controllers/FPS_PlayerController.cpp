#include "FPS_PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "FPSGameInstance.h"
#include "FPS_HUD.h"
#include "Kismet/GameplayStatics.h"

void AFPS_PlayerController::CallHUD() {
	UWorld* World = GetWorld();
	if (World == nullptr) return;

	UFPSGameInstance* FPSGameInstance = Cast<UFPSGameInstance>(UGameplayStatics::GetGameInstance(World));
	if (FPSGameInstance == nullptr) return;

	PlayerHUD = CreateWidget<UFPS_HUD>(this, FPSGameInstance->FPS_HUDClass);
	if (PlayerHUD == nullptr) return;

	PlayerHUD->AddToViewport();
}

void AFPS_PlayerController::CallDeathScreen() {
	if (PlayerHUD == nullptr) return;
	PlayerHUD->SetVisibility(ESlateVisibility::Hidden);

	UUserWidget* DeathScreen = CreateWidget(this, DeathScreenClass);
	if (DeathScreen != nullptr) {
		DeathScreen->AddToViewport();
	}
}