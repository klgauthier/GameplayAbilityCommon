// Copyright Kevin Gauthier 2026


#include "CommonGameplay/CommonGameplayPlayerState.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilityCommon.h"

ACommonGameplayPlayerState::ACommonGameplayPlayerState()
{
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	AbilitySystem->SetIsReplicated(true);
	AbilitySystem->SetReplicationMode(ReplicationMode);

	SetNetUpdateFrequency(100.0f);

	bAbilitySystemReady = false;
}

void ACommonGameplayPlayerState::AbilitySystemReady_Implementation(UAbilitySystemComponent* AbilitySystemComponent) { }

UAbilitySystemComponent* ACommonGameplayPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystem;
}

void ACommonGameplayPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	check(AbilitySystem);
	AbilitySystem->InitAbilityActorInfo(this, GetPawn());
}

void ACommonGameplayPlayerState::InternalAbilitySystemReady()
{
	bAbilitySystemReady = true;
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	AbilitySystemReady(ASC);
	AbilitySystemReadyEvent.Broadcast(ASC);
}
