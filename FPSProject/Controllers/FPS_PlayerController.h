#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPS_HUD.h"
#include "FPS_PlayerController.generated.h"

UCLASS()
class FPSPROJECT_API AFPS_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	void CallHUD();
	void CallDeathScreen();

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> DeathScreenClass;

	UPROPERTY(EditAnywhere)
	UFPS_HUD* PlayerHUD;
};
