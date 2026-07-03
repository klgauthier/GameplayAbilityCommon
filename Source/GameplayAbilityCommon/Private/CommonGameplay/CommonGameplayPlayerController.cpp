//MIT License
//Copyright (c) 2026 Kevin Gauthier

#include "CommonGameplay/CommonGameplayPlayerController.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilityCommon.h"
#include "TimerManager.h"
#include "CommonGameplay/CommonGameplayPlayerState.h"
#include "GameFramework/Pawn.h"
#include "Net/UnrealNetwork.h"

void ACommonGameplayPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(PlayerState))
	{
		CommonGameplayPlayerState = GetPlayerState<ACommonGameplayPlayerState>();
	}
}

UAbilitySystemComponent* ACommonGameplayPlayerController::GetAbilitySystemComponent() const
{
	if(!IsValid(PlayerState))
	{
		UE_LOG(LogGameplayAbilityCommon,
			Error,
			TEXT("[ACommonGameplayPlayerController::GetAbilitySystemComponent] Failed to get a valid PlayerState from [%s]."), *GetName());
	
		return nullptr;
	}

	const ACommonGameplayPlayerState* PlayerStateCast = GetPlayerState<ACommonGameplayPlayerState>();

	if(!PlayerStateCast)
	{
		UE_LOG(LogGameplayAbilityCommon,
			Error,
			TEXT("[ACommonGameplayPlayerController::GetAbilitySystemComponent] PlayerState must be a CommonGameplayPlayerState or child."));
	
		return nullptr;
	}

	return PlayerStateCast->GetAbilitySystemComponent();
}

void ACommonGameplayPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	if(IsValid(PlayerState))
	{
		CommonGameplayPlayerState = GetPlayerState<ACommonGameplayPlayerState>();
	}
}
