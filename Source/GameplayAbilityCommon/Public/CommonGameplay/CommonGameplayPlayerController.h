// Copyright Kevin Gauthier 2026

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemReadyInterface.h"
#include "GameFramework/PlayerController.h"
#include "CommonGameplayPlayerController.generated.h"

struct FGameplayAbilitySpecHandle;
class ACommonGameplayPlayerState;

/**
 * This PlayerController automatically supports CommonGameplayPlayerStates, for easy retrieval of the AbilitySystemComponent
 * It is meant to work with CommonGameplayPlayerState and CommonGameplayPawn or CommonGameplayCharacter.
 * The Ability System Component exists on the PlayerState, so if your AI system re-uses controllers
 * be aware that you'll also need to reset any ability stats you want to reset yourself.
*/
UCLASS()
class GAMEPLAYABILITYCOMMON_API ACommonGameplayPlayerController
	: public APlayerController, public IAbilitySystemInterface, public IAbilitySystemReadyInterface
{	
	GENERATED_BODY()

//===========
// FUNCTIONS
//===========

public:

	virtual void BeginPlay() override;

	/**
	 * Retrieves the AbilitySystemComponent from the PlayerState.
	*/
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/**
	 * Retrieves this controller's CommonGameplayPlayerState.
	*/
	UFUNCTION(BlueprintPure, Category="Ability System")
	ACommonGameplayPlayerState* GetCommonGameplayPlayerState() { return CommonGameplayPlayerState; }

	/**
	 * Returns true if the ability system is ready.
	 * This has the side effect of initializing the ability system if it isn't
	 * properly initialized already.
	*/
	UFUNCTION(BlueprintPure, Category="Ability System")
	bool IsAbilitySystemReady();

protected:
	
	void CheckAbilitySystemReady();

	void NotifyAbilitySystemReady();

//============
// PROPERTIES
//============

public:

protected:

	UPROPERTY()
	TObjectPtr<ACommonGameplayPlayerState> CommonGameplayPlayerState;

	UPROPERTY(Replicated)
	bool bServerAbilitySystemIsReady;

	UPROPERTY()
	FTimerHandle CheckReadyTimerHandle;

//===========
// DELEGATES
//===========

public:


protected:
	
};
