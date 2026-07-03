//MIT License
//Copyright (c) 2026 Kevin Gauthier

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemReadyInterface.h"
#include "GameFramework/Character.h"
#include "CommonGameplayCharacter.generated.h"

class ACommonGameplayPlayerState;

/**
 * This Character works with CommonGameplayPlayerState and a CommonGameplayPlayerController or CommonGameplayAIController.
 * The ability system component for this pawn is owned by its PlayerState, so it will persist through pawn respawns
 * and be replicated across the network.
*/
UCLASS()
class GAMEPLAYABILITYCOMMON_API ACommonGameplayCharacter 
	: public ACharacter, public IAbilitySystemInterface, public IAbilitySystemReadyInterface
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
	
	// called only on the server
	virtual void PossessedBy(AController* NewController) override;

	// called only on the client
	virtual void OnRep_PlayerState() override;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Ability System")
	virtual bool IsAbilitySystemReady() const { return bServerAbilitySystemIsReady && bLocalAbilitySystemIsReady; }
	
protected:
	virtual void NotifyAbilitySystemReady();
	virtual void ServerAbilitySystemReady();
	virtual void LocalAbilitySystemReady();
	
	UFUNCTION()
	void OnRep_ServerAbilitySystemIsReady();

//============
// PROPERTIES
//============

public:

protected:

	UPROPERTY()
	TObjectPtr<ACommonGameplayPlayerState> CommonGameplayPlayerState;
	
	UPROPERTY(Replicated, ReplicatedUsing=OnRep_ServerAbilitySystemIsReady)
	bool bServerAbilitySystemIsReady;
	
	bool bLocalAbilitySystemIsReady;
	bool bHasBeginPlayFired;

//===========
// DELEGATES
//===========

public:


protected:
};
