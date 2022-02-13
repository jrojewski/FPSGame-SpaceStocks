#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainMenuInterface.h"
#include "FPSGameInstance.generated.h"

UCLASS()
class FPSPROJECT_API UFPSGameInstance : public UGameInstance, public IMainMenuInterface
{
	GENERATED_BODY()

public:
	UFPSGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init();

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION()
	void PlayGame();

	UFUNCTION()
	void QuitGame();

	TSubclassOf<class UFPS_HUD> FPS_HUDClass;
private:
	TSubclassOf<class UUserWidget> MenuClass;
};
