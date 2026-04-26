// Copyright Kevin Gauthier 2026


#include "CommonGameplay/CommonGameplayPlayerController.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilityCommon.h"
#include "CommonGameplay/CommonGameplayPlayerState.h"

void ACommonGameplayPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CommonGameplayPlayerState = Cast<ACommonGameplayPlayerState>(PlayerState);

	if(!IsValid(CommonGameplayPlayerState))
	{
		UE_LOG(LogGameplayAbilityCommon,
			Error,
			TEXT("CommonGameplayPlayerController requires the player state class to be a CommonGameplayPlayerState or a child of it."));
	}

	if(CommonGameplayPlayerState->IsAbilitySystemReady())
	{
		AbilitySystemReady(GetAbilitySystemComponent());
	}
	else
	{
		CommonGameplayPlayerState->AbilitySystemReadyEvent.AddUniqueDynamic(this, &ACommonGameplayPlayerController::AbilitySystemReady);
	}
}

void ACommonGameplayPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if(IsValid(CommonGameplayPlayerState))
	{
		CommonGameplayPlayerState->AbilitySystemReadyEvent.RemoveDynamic(this, &ACommonGameplayPlayerController::AbilitySystemReady);
	}
}

UAbilitySystemComponent* ACommonGameplayPlayerController::GetAbilitySystemComponent() const
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

void ACommonGameplayPlayerController::OnRep_PlayerState()
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

// empty implementation -- override if needed
void ACommonGameplayPlayerController::AbilitySystemReady_Implementation(UAbilitySystemComponent* AbilitySystem) { }