// Copyright Kevin Gauthier 2026


#include "CommonGameplay/CommonGameplayCharacter.h"

#include "GameplayAbilityCommon.h"
#include "CommonGameplay/CommonGameplayPlayerState.h"

UAbilitySystemComponent* ACommonGameplayCharacter::GetAbilitySystemComponent() const
{
	if(!IsValid(CommonGameplayPlayerState))
	{
		UE_LOG(LogGameplayAbilityCommon,
			Error,
			TEXT("[ACommonGameplayPlayerController::GetAbilitySystemComponent] Failed to get a valid CommonGameplayPlayerState."));
	
		return nullptr;
	}

	return CommonGameplayPlayerState->GetAbilitySystemComponent();
}

void ACommonGameplayCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	CommonGameplayPlayerState = Cast<ACommonGameplayPlayerState>(GetPlayerState());

	if(IsValid(CommonGameplayPlayerState))
	{
		if(UAbilitySystemComponent* ASC = GetAbilitySystemComponent(); IsValid(ASC))
		{
			ASC->InitAbilityActorInfo(CommonGameplayPlayerState, this);
			CommonGameplayPlayerState->InternalAbilitySystemReady();
		}
	}
	else
	{
		UE_LOG(LogGameplayAbilityCommon,
			Error,
			TEXT("CommonGameplayPlayerController requires the player state class to be a CommonGameplayPlayerState or a child of it."));
	}
}

void ACommonGameplayCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	CommonGameplayPlayerState = Cast<ACommonGameplayPlayerState>(GetPlayerState());

	if(IsValid(CommonGameplayPlayerState))
	{
		if(UAbilitySystemComponent* ASC = GetAbilitySystemComponent(); IsValid(ASC))
		{
			ASC->InitAbilityActorInfo(CommonGameplayPlayerState, this);
			CommonGameplayPlayerState->InternalAbilitySystemReady();
		}
	}
	else
	{
		UE_LOG(LogGameplayAbilityCommon,
			Error,
			TEXT("CommonGameplayPlayerController requires the player state class to be a CommonGameplayPlayerState or a child of it."));
	}
}
