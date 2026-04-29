// Copyright Kevin Gauthier 2026

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemReadyInterface.h"
#include "GameFramework/PlayerState.h"
#include "CommonGameplayPlayerState.generated.h"


/**
 * This class holds replicated state for the player and any controllers that request a player state be made for them.
 * CommonGameplayPlayerState owns the AbilitySystemComponent, with the controller and pawn accessing it through this class.
 * This means the AbilitySystemComponent is replicated across players, and isn't reset when the pawn is respawned.
 */
UCLASS()
class GAMEPLAYABILITYCOMMON_API ACommonGameplayPlayerState : public APlayerState, public IAbilitySystemInterface, public IAbilitySystemReadyInterface
{	
	GENERATED_BODY()

public:
	ACommonGameplayPlayerState();

//===========
// FUNCTIONS
//===========

public:

	/**
	 * Retrieves the ability system component that is owned by this player state.
	*/
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:

//============
// PROPERTIES
//============

public:

protected:
	/**
	 * The ability system component, used to manage gameplay attributes, effects, and abilities.
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability System")
	TObjectPtr<UAbilitySystemComponent> AbilitySystem;

	/**
	 * Replication properties for gameplay effects on the ability system.
	 * Full = Makes all clients able to access all info of all other clients (heavy replication traffic).
	 * Mixed (default) = Makes owning client and server able to access all info, minimal info for other clients.
	 * Minimal = This won't work in this context, don't use it.
	*/
	UPROPERTY()
	EGameplayEffectReplicationMode ReplicationMode = EGameplayEffectReplicationMode::Mixed;

//===========
// DELEGATES
//===========

public:

protected:
	
};
