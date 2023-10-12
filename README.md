# WG-test

# -!REFACTORING IN PROCESS WHILE YOU ARE READING THIS!-
## WIP ideas 
* ~~Canonical UE TakeDamage switch~~ 11/10
* ~~Switching to Event Dispatchers~~
* * ~~UI to dispatcher~~ 11/10
* * ~~GameOver + Trigger to Dispatcher~~ 11/10
* * ~~Trap Damage Dispatcher~~ 12/10
* Trigger to Component
* Transfer HUD from character to GameMode
* Refactor to AOE Damage instead of just getting overlapped in ExplosiveTrap
* Ad Damage Types and for traps. Wind dot / poison dot 
* ~~Dynamic Material~~ 12/10
* Refactor variable names for better understanding in BP
* Try to refactor traps to components
* * ~~Explosive Trap to Trap_Explosive_comp~~ 12/10
* * ~~Wind Trap to component~~ 12/10
* * ~~Moving Trap to component~~ 12/10
* * Shake Trap to Component <- **Refactoring now**
* * Hiding Trap to component
* * Jump pad to component
* * Clean up code from old realization
* More traps that could cause player damage
* Traps that slows
* Utility traps like speed buff
* Upgrading UI (stamina?/timer on screen)

***

## Features on Oct 12.10
[Triggers](Source/WG/trigger.cpp):

ATriggerBox base
* Game Start - start game time count and activating some traps (Moving Platform, Hiding Platform)
* Game Win - cause Win on overlap
* Game Lose - cause Lose on overlap


[Traps](Source/WG/trap_platform.cpp):

AActor base
* Explosive Trap - Standing activate prepare state, after N time explode and cause damage to all Actors on platform. Trap have cooldown
* Wind Trap - Cause wind effect on Y axis. Changing direction every N seconds
* MovingPlatform - Runs from point to point for N seconds. Setting destination with Collision Comp
* Shake&Drop Trap - Shakes for N second and then drop down
* Hiding Trap - Hide and appear in N rate
* Jump Pad - Make character to jump higher

## Refactoring
* AActor -> [ATrapBase](Source/WG/Traps/TrapBase.cpp)
* UActorComponent -> [UTrapBaseComponent](Source/WG/Traps/TrapBaseComponent.cpp)
* _UActorComponent::UTrapBaseComponent::_[Explosive Trap Component](Source/WG/Traps/Trap_Explosive_comp.cpp) - Explosive trap decomposition  
* _UActorComponent::UTrapBaseComponent::_[Wind Trap Component](Source/WG/Traps/Trap_Wind_comp.cpp) - Wind trap decomposition
* _UActorComponent::UTrapBaseComponent::_[Moving Platform Component](Source/WG/Traps/Trap_MovingPlatform_comp.cpp) - Moving Trap decomposition]
* 
***

### Other features:
* Character have HP.
* Character could receive damage (non canonical TakeDamage)
* Gameplay UI for HP
* On win/lose UI showing race time and provide ability ro restart game

