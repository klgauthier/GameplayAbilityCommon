// Copyright Kevin Gauthier 2026


#include "CommonGameplay/CommonGameplayCharacter.h"

#include "GameplayAbilityCommon.h"
#include "CommonGameplay/CommonGameplayPlayerState.h"

UAbilitySystemComponent* ACommonGameplayCharacter::GetAbilitySystemComponent() const
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

void ACommonGameplayCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	CommonGameplayPlayerState = Cast<ACommonGameplayPlayerState>(GetPlayerState());
}
