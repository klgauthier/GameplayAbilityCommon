// Copyright Kevin Gauthier 2026

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemReadyInterface.h"
#include "GameFramework/Character.h"
#include "CommonGameplayCharacter.generated.h"

class ACommonGameplayPlayerState;

/*
 * This Character works with CommonGameplayPlayerState and a CommonGameplayPlayerController or CommonGameplayAIController.
 * The ability system component for this pawn is owned by its PlayerState, so it will persist through pawn respawns
 * and be replicated across the network.
*/
UCLASS()
class GAMEPLAYABILITYCOMMON_API ACommonGameplayCharacter : public ACharacter, public IAbilitySystemInterface, public IAbilitySystemReadyInterface
{
	GENERATED_BODY()

//===========
// FUNCTIONS
//===========

public:
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

	// called only on the client
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
