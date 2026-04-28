// Copyright Kevin Gauthier 2026


#include "CommonGameplay/CommonGameplayPawn.h"

#include "GameplayAbilityCommon.h"
#include "CommonGameplay/CommonGameplayPlayerState.h"

UAbilitySystemComponent* ACommonGameplayPawn::GetAbilitySystemComponent() const
{
	if(!IsValid(GetPlayerState()))
	{
		UE_LOG(LogGameplayAbilityCommon,
			Error,
			TEXT("[ACommonGameplayPlayerController::GetAbilitySystemComponent] Failed to get a valid PlayerState."));
	
		return nullptr;
	}

	const ACommonGameplayPlayerState* PlayerStateCast = GetPlayerState<ACommonGameplayPlayerState>();

	return PlayerStateCast->GetAbilitySystemComponent();
}

void ACommonGameplayPawn::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	CommonGameplayPlayerState = Cast<ACommonGameplayPlayerState>(GetPlayerState());
}

