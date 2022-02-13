#include "MainMenu.h"
#include "Kismet/GameplayStatics.h"
#include "FPSGameInstance.h"
#include "FPS_HUD.h"
#include "Components/Button.h"

bool UMainMenu::Initialize() {
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (Button_Play == nullptr) return false;
	Button_Play->OnClicked.AddDynamic(this, &UMainMenu::PlayGame);

	if (Button_Quit == nullptr) return false;
	Button_Quit->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);

	return true;
}

void UMainMenu::SetMenuInterface(IMainMenuInterface* TempMainMenuInterface) {
	this->MainMenuInterface = TempMainMenuInterface;
}

void UMainMenu::Setup() {
	this->AddToViewport();
	this->bIsFocusable = true;

	UWorld* World = GetWorld();
	if (World == nullptr) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (PlayerController == nullptr) return;

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = true;

}

void UMainMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);

	FInputModeGameOnly InputModeData;

	UWorld* World = GetWorld();
	if (World == nullptr) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (PlayerController == nullptr) return;

	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = false;
}

void UMainMenu::PlayGame() {
	if (MainMenuInterface != nullptr) {
		MainMenuInterface->PlayGame();
	}
}

void UMainMenu::QuitGame() {
	if (MainMenuInterface != nullptr) {
		MainMenuInterface->QuitGame();
	}
}