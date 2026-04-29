// Copyright Kevin Gauthier 2026


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

	if(!IsAbilitySystemReady())
	{
		GetWorldTimerManager().SetTimer(CheckReadyTimerHandle,
			this,
			&ACommonGameplayAIController::CheckAbilitySystemReady,
			1.0f/100.0f,
			true);

		CheckAbilitySystemReady();		
	}
}

UAbilitySystemComponent* ACommonGameplayAIController::GetAbilitySystemComponent() const
{
	if(!IsValid(PlayerState))
	{
		UE_LOG(LogGameplayAbilityCommon,
			Error,
			TEXT("[ACommonGameplayPlayerController::GetAbilitySystemComponent] Failed to get a valid PlayerState."));
	
		return nullptr;
	}

	const ACommonGameplayPlayerState* PlayerStateCast = Cast<ACommonGameplayPlayerState>(PlayerState);

	return PlayerStateCast->GetAbilitySystemComponent();
}

bool ACommonGameplayAIController::IsAbilitySystemReady()
{
	// missing playerstate
	if(!IsValid(PlayerState))
	{
		return false;
	}

	if(!IsValid(CommonGameplayPlayerState))
	{
		CommonGameplayPlayerState = GetPlayerState<ACommonGameplayPlayerState>();
		if(!IsValid(CommonGameplayPlayerState))
		{
			return false;
		}
	}
	
	// missing pawn
	APawn* MyPawn = GetPawn();
	if(!IsValid(MyPawn))
	{
		return false;
	}

	// Controller is told it has a pawn before the pawn is told it has a controller
	if(!IsValid(MyPawn->Controller))
	{
		return false;
	}

	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if(ASC->GetAvatarActor() != MyPawn || !IsValid(ASC->GetAvatarActor()) || !IsValid(ASC->GetOwnerActor()))
	{
		ASC->InitAbilityActorInfo(CommonGameplayPlayerState, MyPawn);
	}

	return true;
}

void ACommonGameplayAIController::CheckAbilitySystemReady()
{
	if(!IsAbilitySystemReady())
	{
		return;
	}
	
	UE_LOG(LogGameplayAbilityCommon,
			Log,
			TEXT("[ACommonGameplayPlayerController] Ability System Initialized on Server for %s. OwnerActor=[%s], AvatarActor=[%s]"),
			*GetName(),
			*GetAbilitySystemComponent()->GetOwnerActor()->GetName(),
			*GetAbilitySystemComponent()->GetAvatarActor()->GetName());

	Execute_AbilitySystemReady(this, GetAbilitySystemComponent());
	Execute_AbilitySystemReady(GetPawn(), GetAbilitySystemComponent());
	Execute_AbilitySystemReady(PlayerState, GetAbilitySystemComponent());
	
	GetWorldTimerManager().ClearTimer(CheckReadyTimerHandle);
}

