// Copyright Kevin Gauthier 2026

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "CommonGameplayAIController.generated.h"

class ACommonGameplayPlayerState;

/*
 * This AIController automatically supports CommonGameplayPlayerStates, for easy retrieval of the AbilitySystemComponent
 * It is meant to work with CommonGameplayPlayerState and CommonGameplayPawn or CommonGameplayCharacter.
 * The Ability System Component exists on the PlayerState, so it will persist through pawn respawns and be
 * replicated across the network.
*/ 
UCLASS()
class GAMEPLAYABILITYCOMMON_API ACommonGameplayAIController : public AAIController, public IAbilitySystemInterface
{
	GENERATED_BODY()

	ACommonGameplayAIController();

//===========
// FUNCTIONS
//===========

public:

	virtual void BeginPlay() override;

	/*
	 * Retrieves the AbilitySystemComponent from the PlayerState.
	*/
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/*
	 * Retrieves this controller's CommonGameplayPlayerState.
	*/
	UFUNCTION(BlueprintPure, Category="Ability System")
	ACommonGameplayPlayerState* GetCommonGameplayPlayerState() { return CommonGameplayPlayerState; }

protected:

	/*
	 * Called only on the client so that we can refresh the AbilitySystemComponent when needed.
	*/
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
