// Copyright Kevin Gauthier 2026


#include "CommonGameplay/CommonGameplayPlayerController.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilityCommon.h"
#include "CommonGameplay/CommonGameplayPlayerState.h"
#include "Net/UnrealNetwork.h"

void ACommonGameplayPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACommonGameplayPlayerController, bServerAbilitySystemIsReady);
}

void ACommonGameplayPlayerController::BeginPlay()
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
			&ACommonGameplayPlayerController::CheckAbilitySystemReady,
			1.0f/100.0f,
			true);

		CheckAbilitySystemReady();		
	}
}

UAbilitySystemComponent* ACommonGameplayPlayerController::GetAbilitySystemComponent() const
{
	if(!IsValid(PlayerState))
	{
		UE_LOG(LogGameplayAbilityCommon,
			Error,
			TEXT("[ACommonGameplayPlayerController::GetAbilitySystemComponent] Failed to get a valid PlayerState."));
	
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

bool ACommonGameplayPlayerController::IsAbilitySystemReady()
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

	if(!IsNetMode(NM_Client))
	{
		bServerAbilitySystemIsReady = true;
	}

	return true;
}

void ACommonGameplayPlayerController::CheckAbilitySystemReady()
{
	if(!IsAbilitySystemReady())
	{
		return;
	}

	const FString NetModeString = IsNetMode(NM_Client)? TEXT("Client") : IsNetMode(NM_ListenServer)? TEXT("ListenServer") : TEXT("Server");
	UE_LOG(LogGameplayAbilityCommon,
			Log,
			TEXT("[ACommonGameplayPlayerController] Ability System Initialized on %s for %s. OwnerActor=[%s], AvatarActor=[%s]"),
			*NetModeString,
			*GetName(),
			*GetAbilitySystemComponent()->GetOwnerActor()->GetName(),
			*GetAbilitySystemComponent()->GetAvatarActor()->GetName());

	Execute_AbilitySystemReady(this, GetAbilitySystemComponent());
	Execute_AbilitySystemReady(GetPawn(), GetAbilitySystemComponent());
	Execute_AbilitySystemReady(PlayerState, GetAbilitySystemComponent());
	
	GetWorldTimerManager().ClearTimer(CheckReadyTimerHandle);
}
