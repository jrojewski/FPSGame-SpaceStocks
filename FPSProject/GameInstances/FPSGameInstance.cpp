#include "FPSGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.h"
#include "FPS_HUD.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

UFPSGameInstance::UFPSGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MainMenu/WBP_MainMenu")); 
	if (MenuBPClass.Class == nullptr) return;
	MenuClass = MenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> FPS_HUDBPClass(TEXT("/Game/HUD/WBP_HUD"));
	if (FPS_HUDBPClass.Class == nullptr) return;
	FPS_HUDClass = FPS_HUDBPClass.Class;
}

void UFPSGameInstance::Init()
{
	//UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName())
	//UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *FPS_HUDClass->GetName());
}

void UFPSGameInstance::LoadMenu()
{
	if (MenuClass == nullptr) return;

	UMainMenu* Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (Menu == nullptr) return;

	Menu->Setup();

	Menu->SetMenuInterface(this);
}

void UFPSGameInstance::PlayGame()
{
	UWorld* World = GetWorld();
	if (World == nullptr) return;

	UGameplayStatics::OpenLevel(World, "FirstLevel");

	return;
}

void UFPSGameInstance::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);

	return;
}
