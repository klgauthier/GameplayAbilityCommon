//MIT License
//Copyright (c) 2026 Kevin Gauthier

#include "CommonGameplay/CommonGameplayAIController.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilityCommon.h"
#include "CommonGameplay/CommonGameplayPlayerState.h"
#include "Net/UnrealNetwork.h"

ACommonGameplayAIController::ACommonGameplayAIController()
{
	bWantsPlayerState = true;
}

void ACommonGameplayAIController::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(PlayerState))
	{
		CommonGameplayPlayerState = GetPlayerState<ACommonGameplayPlayerState>();
	}
}

UAbilitySystemComponent* ACommonGameplayAIController::GetAbilitySystemComponent() const
{
	if(!IsValid(PlayerState))
	{
		UE_LOG(LogGameplayAbilityCommon,
			Error,
			TEXT("[ACommonGameplayAIController::GetAbilitySystemComponent] Failed to get a valid PlayerState."));
	
		return nullptr;
	}

	const ACommonGameplayPlayerState* PlayerStateCast = Cast<ACommonGameplayPlayerState>(PlayerState);

	return PlayerStateCast->GetAbilitySystemComponent();
}

void ACommonGameplayAIController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	if(IsValid(PlayerState))
	{
		CommonGameplayPlayerState = GetPlayerState<ACommonGameplayPlayerState>();
	}
}