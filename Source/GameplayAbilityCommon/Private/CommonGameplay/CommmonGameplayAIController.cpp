// Copyright Kevin Gauthier 2026


#include "CommonGameplay/CommonGameplayAIController.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilityCommon.h"
#include "CommonGameplay/CommonGameplayPlayerState.h"
#include "Net/UnrealNetwork.h"

ACommonGameplayAIController::ACommonGameplayAIController(): bServerAbilitySystemIsReady(false)
{
	bWantsPlayerState = true;
}

void ACommonGameplayAIController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACommonGameplayAIController, bServerAbilitySystemIsReady);
}

void ACommonGameplayAIController::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(PlayerState))
	{
		CommonGameplayPlayerState = GetPlayerState<ACommonGameplayPlayerState>();
	}

	if(IsValid(GetPawn()) && IsValid(CommonGameplayPlayerState))
	{
		CommonGameplayPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(CommonGameplayPlayerState, GetPawn());
	}

	CheckAbilitySystemReady();

	GetWorldTimerManager().SetTimer(CheckReadyTimerHandle,
		this,
		&ACommonGameplayAIController::CheckAbilitySystemReady,
		1.0f/100.0f,
		true);
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
	// ensure the server is ready if we're a client
	if(IsNetMode(NM_Client) && !bServerAbilitySystemIsReady)
	{
		return false;
	}
	
	// missing playerstate
	if(!IsValid(PlayerState))
	{
		return false;
	}

	if(!IsValid(CommonGameplayPlayerState))
	{
		CommonGameplayPlayerState = GetPlayerState<ACommonGameplayPlayerState>();
	}
	
	// missing pawn
	if(!IsValid(GetPawn()))
	{
		return false;
	}

	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if(!IsValid(ASC->GetAvatarActor()) && !IsValid(ASC->GetOwnerActor()))
	{
		ASC->InitAbilityActorInfo(CommonGameplayPlayerState, GetPawn());
	}

	if(!bServerAbilitySystemIsReady && !IsNetMode(NM_Client))
	{
		bServerAbilitySystemIsReady = true;
	}

	return bServerAbilitySystemIsReady;
}

void ACommonGameplayAIController::CheckAbilitySystemReady()
{
	if(!IsAbilitySystemReady())
	{
		return;
	}

	if(IsNetMode(NM_Client))
	{
		UE_LOG(LogGameplayAbilityCommon,
			Log,
			TEXT("Ability System Initialized on Client for player %s."), *GetName());
	}
	else if(IsNetMode(NM_ListenServer))
	{
		UE_LOG(LogGameplayAbilityCommon,
			Log,
			TEXT("Ability System Initialized on ListenServer for player %s."), *GetName());
	}
	else
	{
		UE_LOG(LogGameplayAbilityCommon,
			Log,
			TEXT("Ability System Initialized on Server for player %s."), *GetName());
	}

	Execute_AbilitySystemReady(this, GetAbilitySystemComponent());
	Execute_AbilitySystemReady(GetPawn(), GetAbilitySystemComponent());
	Execute_AbilitySystemReady(PlayerState, GetAbilitySystemComponent());
	
	GetWorldTimerManager().ClearTimer(CheckReadyTimerHandle);
}

