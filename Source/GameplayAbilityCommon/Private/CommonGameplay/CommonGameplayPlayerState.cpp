// Copyright Kevin Gauthier 2026


#include "CommonGameplay/CommonGameplayPlayerState.h"

#include "AbilitySystemComponent.h"

ACommonGameplayPlayerState::ACommonGameplayPlayerState()
{
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	AbilitySystem->SetIsReplicated(true);
	AbilitySystem->SetReplicationMode(ReplicationMode);

	SetNetUpdateFrequency(100.0f);
}

UAbilitySystemComponent* ACommonGameplayPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystem;
}
