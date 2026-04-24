// Copyright Kevin Gauthier 2026


#include "CommonGameplay/CommonGameplayAIController.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilityCommon.h"
#include "CommonGameplay/CommonGameplayPlayerState.h"

ACommonGameplayAIController::ACommonGameplayAIController()
{
	bWantsPlayerState = true;
}

void ACommonGameplayAIController::BeginPlay()
{
	Super::BeginPlay();

	CommonGameplayPlayerState = Cast<ACommonGameplayPlayerState>(PlayerState);

	if(!IsValid(CommonGameplayPlayerState))
	{
		UE_LOG(LogGameplayAbilityCommon,
			Error,
			TEXT("CommonGameplayPlayerController requires the player state class to be a CommonGameplayPlayerState or a child of it."));
	}
}

UAbilitySystemComponent* ACommonGameplayAIController::GetAbilitySystemComponent() const
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

void ACommonGameplayAIController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// we need to refresh our ability system component when we're a client player controller
	// as this controller, the player state, and ability component can initialize out of order
	if(GetWorld()->IsNetMode(NM_Client))
	{
		if(IsValid(CommonGameplayPlayerState))
		{
			if(UAbilitySystemComponent* ASC = GetAbilitySystemComponent(); IsValid(ASC))
			{
				ASC->RefreshAbilityActorInfo();
			}
		}
	}
}

