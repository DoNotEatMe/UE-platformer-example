# WG-test

[Triggers](Source/WG/trigger.cpp):

ATriggerBox base
* Game Start - start game time count and activating some traps (Moving Platform, Hiding Platform)
* Game Win - cause Win on overlap
* Game Lose - cause Lose on overlap


[Traps](Source/WG/trap_platform.cpp):

AActor base
* Explosive Trap - Standing cause prepare state, after N time explode. Trap have cooldown
* Wind Trap - Cause wind effect on Y axis. Changing direction every N seconds
* MovingPlatform - Runs from point to point for N seconds. Setting destination with Collision Comp
* Shake&Drop Trap - Shakes for N second and then drop down
* Hiding Trap - Hide and appear in N rate
* Jump Pad - Make character to jump higher


#### Other features:
* Character have HP.
* Character could receive damage (non canonical TakeDamage)
* Gameplay UI for HP
* On win/lose UI showing race time and provide ability ro restart game

