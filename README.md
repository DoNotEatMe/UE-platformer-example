# WG-test
## WIP ideas
* ~~Canonical UE TakeDamage switch~~ 11/10
* Switching to Event Dispatchers
* * ~~UI to dispatcher~~ 10/11
* * ~~GameOver + Trigger to Dispatcher~~
* * Damage Dispatcher?
* Trigger to Component
* Transfer HUD from character to GameMode
* Refactor to AOE Damage instead GetAllOverlappingActors() in ExplosiveTrap
* Ad Damage Types and for traps. Wind dot / poison dot 
* Dynamic Material
* Refactor variable names for better understanding in BP
* Try to refactor traps to components
* More traps that could cause player damage
* Traps that slows
* Utility traps like speed buff
* Upgrading UI (stamina?/timer on screen)

***

## Features on Oct 10.10
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

***

### Other features:
* Character have HP.
* Character could receive damage (non canonical TakeDamage)
* Gameplay UI for HP
* On win/lose UI showing race time and provide ability ro restart game

