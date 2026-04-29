# GameplayAbilityCommon
A small UE5 plugin to jumpstart development that uses the Gameplay Ability System in a networked configuration.

## Basic Info
Provides new base classes for Controllers, Pawn, Character, and PlayerState that handle setting up an AbilitySystemComponent on the PlayerState.

## Setup
1. In your Project Settings, change your PlayerState class to `CommonGameplayPlayerState` or your own subclass of it.
2. Set your Controller classes to `CommonGameplayPlayerController` or `CommonGameplayPlayerState` in the appropriate places.
3. (Optional but recommended) Use `CommonGameplayPawn` or `CommonGameplayCharacter` as the base classes for your pawns.

## Additional Info
- Due to the nature of server initialization, ability systems might not be ready immediately. The Blueprint Native Event `AbilitySystemReady()` is the best place to call code or blueprints that you want to run once the ability system is ready. *Note:* This Event can fire multiple times.

## Potential Future Additions
- SimpleGameplay classes to support Pawns and Controllers whose AbilitySystemComponent lives on the pawn.
- The ability to override which class of AbilitySystemComponent is being put on PlayerStates.
