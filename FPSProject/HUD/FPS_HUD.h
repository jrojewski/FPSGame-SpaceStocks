#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPS_HUD.generated.h"

UCLASS()
class FPSPROJECT_API UFPS_HUD : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Health;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentAmmo;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MaxAmmo;
};
