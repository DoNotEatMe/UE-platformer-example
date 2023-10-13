# -!REFACTORING IN PROCESS WHILE YOU ARE READING THIS!-

## WIP ideas 

* Trigger to Component
* Transfer HUD from character to GameMode <- **now**
* Decompose HP
* Refactor to AOE Damage instead of just getting overlapped in ExplosiveTrap
* Ad Damage Types and for traps. Wind dot / poison dot
* More Traps
* * More traps that could cause player damage
* * Traps that slows
* * Utility traps like speed buff
* Dash implementation
* Stamina implementation
* Power charges pickup implementation

## Done
* ~~Canonical UE TakeDamage switch~~ 11/10
* ~~Switching to Event Dispatchers~~
* * ~~UI to dispatcher~~ 11/10
* * ~~GameOver + Trigger to Dispatcher~~ 11/10
* * ~~Trap Damage Dispatcher~~ 12/10
* * ~~Dynamic Material~~ 12/10
* ~~Refactor variable names for better understanding in BP~~ 12/10
* ~~Try to refactor traps to components~~ 12/10
* * ~~Explosive Trap to Trap_Explosive_comp~~ 12/10
* * ~~Wind Trap to component~~ 12/10
* * ~~Moving Trap to component~~ 12/10
* * ~~Shake Trap to Component~~ 12/10
* * ~~Hiding Trap to component~~ 12/10
* * ~~Jump pad to component~~ 12/10
* * ~~Clean up code from old realization~~ 12/10
* ~~!Renew map with new Traps realization! (now broken)~~ 13/10
* ~~ExplosiveTrap Cooldown broke.~~ 13/10

***

## Features on Oct 12.10
* Character have HP.
* Character could receive damage (canonical UE take damage)
* Gameplay UI for HP
* On win/lose UI showing race time and provide ability ro restart game


[Triggers](Source/WG/trigger.cpp):

ATriggerBox base
* Game Start - start game time count and activating some traps (Moving Platform, Hiding Platform)
* Game Win - cause Win on overlap
* Game Lose - cause Lose on overlap

## Trap blocks
* AActor::[ATrapBase](Source/WG/Traps/TrapBase.cpp) - Trap base class
* UActorComponent::[UTrapBaseComponent](Source/WG/Traps/TrapBaseComponent.cpp) - trap component base class
* _UActorComponent::UTrapBaseComponent::_[Explosive Trap Component](Source/WG/Traps/Trap_Explosive_comp.cpp) - Explosive trap decomposition  
* _UActorComponent::UTrapBaseComponent::_[Wind Trap Component](Source/WG/Traps/Trap_Wind_comp.cpp) - Wind trap decomposition
* _UActorComponent::UTrapBaseComponent::_[Moving Platform Component](Source/WG/Traps/Trap_MovingPlatform_comp.cpp) - Moving trap decomposition
* _UActorComponent::UTrapBaseComponent::_[Hiding Trap Component](Source/WG/Traps/Trap_Hiding_comp.cpp) - Hiding trap decomposition
* _UActorComponent::UTrapBaseComponent::_[Jump Trap Component](Source/WG/Traps/Trap_Jump_comp.cpp) - Jump trap decomposition
***


for contact [t.me/donoteatme](https://t.me/donoteatme) 

