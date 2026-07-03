//MIT License
//Copyright (c) 2026 Kevin Gauthier

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemReadyInterface.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "CommonGameplayAIController.generated.h"

class ACommonGameplayPawn;
class ACommonGameplayCharacter;
class ACommonGameplayPlayerState;

/**
 * This AIController automatically supports CommonGameplayPlayerStates, for easy retrieval of the AbilitySystemComponent
 * It is meant to work with CommonGameplayPlayerState and CommonGameplayPawn or CommonGameplayCharacter.
 * The Ability System Component exists on the PlayerState, so it will persist through pawn respawns and be
 * replicated across the network.
*/ 
UCLASS()
class GAMEPLAYABILITYCOMMON_API ACommonGameplayAIController
	: public AAIController, public IAbilitySystemInterface, public IAbilitySystemReadyInterface
{
	GENERATED_BODY()

public:
	ACommonGameplayAIController();
	
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

protected:

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
