//MIT License
//Copyright (c) 2026 Kevin Gauthier

#include "CommonGameplay/CommonGameplayPawn.h"

#include "GameplayAbilityCommon.h"
#include "CommonGameplay/CommonGameplayPlayerController.h"
#include "CommonGameplay/CommonGameplayPlayerState.h"
#include "Net/UnrealNetwork.h"

void ACommonGameplayPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACommonGameplayPawn, bServerAbilitySystemIsReady);
}

void ACommonGameplayPawn::BeginPlay()
{
	Super::BeginPlay();
	
	bHasBeginPlayFired = true;
	if (IsAbilitySystemReady())
	{
		NotifyAbilitySystemReady();
	}
}

UAbilitySystemComponent* ACommonGameplayPawn::GetAbilitySystemComponent() const
{
	if(!IsValid(GetPlayerState()))
	{
		UE_LOG(LogGameplayAbilityCommon,
			Error,
			TEXT("[ACommonGameplayPawn::GetAbilitySystemComponent] Failed to get a valid PlayerState."));
	
		return nullptr;
	}

	const ACommonGameplayPlayerState* PlayerStateCast = GetPlayerState<ACommonGameplayPlayerState>();

	return PlayerStateCast->GetAbilitySystemComponent();
}

// Server Only
void ACommonGameplayPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	CommonGameplayPlayerState = GetPlayerState<ACommonGameplayPlayerState>();
	if (IsValid(CommonGameplayPlayerState))
	{
		CommonGameplayPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(CommonGameplayPlayerState, this);
		ServerAbilitySystemReady();
	}
}

// Client Only
void ACommonGameplayPawn::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	CommonGameplayPlayerState = Cast<ACommonGameplayPlayerState>(GetPlayerState());
	if (IsValid(CommonGameplayPlayerState))
	{
		CommonGameplayPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(CommonGameplayPlayerState, this);
		LocalAbilitySystemReady();
	}
}

void ACommonGameplayPawn::NotifyAbilitySystemReady()
{
	Execute_AbilitySystemReady(this, GetAbilitySystemComponent());
	
	if (AController* MyController = GetController(); IsValid(MyController))
	{
		Execute_AbilitySystemReady(MyController, GetAbilitySystemComponent());
	}
	
	if (IsValid(GetPlayerState()))
	{
		Execute_AbilitySystemReady(GetPlayerState(), GetAbilitySystemComponent());
	}
}

void ACommonGameplayPawn::ServerAbilitySystemReady()
{
	bServerAbilitySystemIsReady = true;
	bLocalAbilitySystemIsReady = true;
	
	if (bHasBeginPlayFired)
	{
		NotifyAbilitySystemReady();
	}
}

void ACommonGameplayPawn::LocalAbilitySystemReady()
{
	bLocalAbilitySystemIsReady = true;
	
	if (IsAbilitySystemReady() && bHasBeginPlayFired)
	{
		NotifyAbilitySystemReady();
	}
}

void ACommonGameplayPawn::OnRep_ServerAbilitySystemIsReady()
{
	if (IsAbilitySystemReady() && bHasBeginPlayFired)
	{
		NotifyAbilitySystemReady();
	}
}
