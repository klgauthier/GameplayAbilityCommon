//MIT License
//Copyright (c) 2026 Kevin Gauthier

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemReadyInterface.h"
#include "GameFramework/PlayerController.h"
#include "CommonGameplayPlayerController.generated.h"

class ACommonGameplayPawn;
class ACommonGameplayCharacter;
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

protected:
	virtual void BeginPlay() override;
	
//===========
// FUNCTIONS
//===========

public:
	/**
	 * Retrieves the AbilitySystemComponent from the PlayerState.
	*/
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/**
	 * Retrieves this controller's CommonGameplayPlayerState.
	*/
	UFUNCTION(BlueprintPure, Category="Ability System")
	ACommonGameplayPlayerState* GetCommonGameplayPlayerState() { return CommonGameplayPlayerState; }
	
	virtual void OnRep_PlayerState() override;

//============
// PROPERTIES
//============

public:
	
	
protected:

	UPROPERTY()
	TObjectPtr<ACommonGameplayPlayerState> CommonGameplayPlayerState;

//===========
// DELEGATES
//===========

public:


protected:
	
};
