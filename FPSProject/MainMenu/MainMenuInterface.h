#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MainMenuInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMainMenuInterface : public UInterface
{
	GENERATED_BODY()
};

class FPSPROJECT_API IMainMenuInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void PlayGame() = 0;
	virtual void QuitGame() = 0;
};
