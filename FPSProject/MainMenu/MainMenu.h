#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuInterface.h"
#include "MainMenu.generated.h"

UCLASS()
class FPSPROJECT_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetMenuInterface(IMainMenuInterface* TempMainMenuInterface);

	void Setup();

protected:
	virtual bool Initialize() override;
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Play;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Quit;

	UFUNCTION()
	void PlayGame();

	UFUNCTION()
	void QuitGame();

	IMainMenuInterface* MainMenuInterface;
};
