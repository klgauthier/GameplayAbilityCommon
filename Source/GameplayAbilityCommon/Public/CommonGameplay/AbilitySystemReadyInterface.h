//MIT License
//Copyright (c) 2026 Kevin Gauthier

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AbilitySystemReadyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UAbilitySystemReadyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMEPLAYABILITYCOMMON_API IAbilitySystemReadyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// Called once the ability system has been properly initialized with an avatar and an owner.
	// This happens some time after begin play due to waiting on the possession of the pawn
	// by its controller.
	UFUNCTION(BlueprintNativeEvent, Category="Ability System")
	void AbilitySystemReady(class UAbilitySystemComponent* AbilitySystemComponent);
};
