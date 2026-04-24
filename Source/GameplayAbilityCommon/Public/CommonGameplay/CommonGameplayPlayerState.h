// Copyright Kevin Gauthier 2026

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "CommonGameplayPlayerState.generated.h"

/**
 * This class holds replicated state for the player and any controllers that request a player state be made for them.
 * CommonGameplayPlayerState owns the AbilitySystemComponent, with the controller and pawn accessing it through this class.
 * This means the AbilitySystemComponent is replicated across players, and isn't reset when the pawn is respawned.
 */
UCLASS()
class GAMEPLAYABILITYCOMMON_API ACommonGameplayPlayerState : public APlayerState, public IAbilitySystemInterface
{
	friend class ACommonGameplayCharacter;
	friend class ACommonGameplayPawn;
	
	GENERATED_BODY()

public:
	ACommonGameplayPlayerState();

//===========
// FUNCTIONS
//===========

public:

	/*
	 * Called once the ability system has been properly initialized with an avatar and an owner.
	 * This happens some time after begin play due to waiting on the possession of the pawn
	 * by its controller.
	*/
	UFUNCTION(BlueprintNativeEvent, Category="Ability System")
	void AbilitySystemReady();

	/*
	 * Retrieves the ability system component that is owned by this player state.
	*/
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/*
	 * Will return true once the ability system has been properly initialized with
	 * an avatar and an owner, some time after BeginPlay has been called.
	*/
	UFUNCTION(BlueprintPure, Category="Ability System")
	bool IsAbilitySystemReady() const { return bAbilitySystemReady; }

	virtual void PostInitializeComponents() override;

protected:
	/*
	 * Called internally from CommonGameplayPawn/Character to denote that the ability system is ready.
	*/
	void InternalAbilitySystemReady();

//============
// PROPERTIES
//============

public:

protected:
	/*
	 * The ability system component, used to manage gameplay attributes, effects, and abilities.
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability System")
	TObjectPtr<UAbilitySystemComponent> AbilitySystem;

	/*
	 * Replication properties for gameplay effects on the ability system.
	 * Full = Makes all clients able to access all info of all other clients (heavy replication traffic).
	 * Mixed (default) = Makes owning client and server able to access all info, minimal info for other clients.
	 * Minimal = This won't work in this context, don't use it.
	*/
	UPROPERTY()
	EGameplayEffectReplicationMode ReplicationMode = EGameplayEffectReplicationMode::Mixed;

	/*
	 * Designates if the ability system is properly setup and ready for use.
	*/
	UPROPERTY()
	bool bAbilitySystemReady;

//===========
// DELEGATES
//===========

public:


protected:
	
};
