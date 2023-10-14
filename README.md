Refactoring still in process. Look for [WIP](#wip-ideas) and [Done](#done).

## Prologue
<details>
 <summary>Initial Task</summary>

You need to create a simple 3D platformer where the character must move from the starting point to the finish line through a field filled with obstacles. The reference for what should be achieved is the levels from the game Fall Guys.

The starting point is a 10x10-meter platform where the player is placed. Several paths, intertwined with each other, radiate from the starting point. At the finish line, all paths converge into one. The paths consist of 3x3-meter platforms.

Some of the blocks that make up the path are traps that obstruct the player in various ways. For the test task, you need to implement a minimum of 3-4 different types of traps. Two of them are mandatory:

When the player steps on a block, it activates (turns orange) and, after 1 second, deals damage to anyone standing on the block (flashes red). After dealing damage, the trap "resets" for 5 seconds and then repeats its logic from the beginning.

A block on which the wind blows, pushing the character with a certain force. The wind affects the character only while they are on the block. The wind's direction changes every 2 seconds to a random direction. The wind always blows horizontally.

You are encouraged to come up with other traps yourself. Examples of traps can be seen in the game Fall Guys. It's desirable that the mechanics of each trap are understandable to the average casual player.

The game can end in two ways - victory or defeat:

To win, the player must cross the finish line. At that moment, a message appears on the entire screen saying "Victory!" and a button to restart the game. The screen also displays the level completion time, which is calculated from the moment the player crosses the starting line.

The player loses if they fall off the path into an abyss or run out of health. The player's health must always be displayed on the screen. When the player loses, a screen appears with the message "Defeat!" and a button to restart the game.

</details>


<details>
    <summary>Work explanation</summary>

I couldn't say that i have much experience with UE, but long ago i went through gamedev.tv courses and have some knowledge how basic features works. These basic knowledge made me to finish task with ~20h (first iteration that i send as result).

First I made all necessary features from task with "as i know" realization. Result was working as task suppose, but I was unsatisfied for not flexible decisions, so I started to refactor project structure for better practice and learn something new. You could take a look to refactoring timings at [log](#done).

So, what i learned:

* Event Dispatchers and implementation for handling HP changes, GameOver events.
* Dynamic material with c++
* I remember class inheritance in UE and made some bases for Engine on-air settings and overriding some functions as ResetTimer() for all traps at once.
* Canonical UE TakeDamage
* ...updating...

</details>




## Features on Oct 14.10
* Character have HP and HP displaying at UI
* Character could receive damage (canonical UE take damage with dispatcher)
* On win/lose UI showing race time and provide ability ro restart game or change level to playground (traps and triggers representation)
* 5 traps

### Triggers
* _ATriggetBox::_[trigger.cpp](Source/WG/trigger.cpp) - trigger holding class.

### UI
* _UUserWidget::_[Game HUD](Source/WG/UI/gameHUD.cpp) - represent gameplay UI
* _UUserWidget::_[Game Over](Source/WG/UI/GameOver.cpp) - represent win/lose menu with opportunity to reset level/try playground

### Trap blocks
* AActor::[ATrapBase](Source/WG/Traps/TrapBase.cpp) - Trap base class
* UActorComponent::[UTrapBaseComponent](Source/WG/Traps/TrapBaseComponent.cpp) - trap component base class
* _UActorComponent::UTrapBaseComponent::_[Explosive Trap Component](Source/WG/Traps/Trap_Explosive_comp.cpp) - Explosive trap decomposition  
* _UActorComponent::UTrapBaseComponent::_[Wind Trap Component](Source/WG/Traps/Trap_Wind_comp.cpp) - Wind trap decomposition
* _UActorComponent::UTrapBaseComponent::_[Moving Platform Component](Source/WG/Traps/Trap_MovingPlatform_comp.cpp) - Moving trap decomposition
* _UActorComponent::UTrapBaseComponent::_[Hiding Trap Component](Source/WG/Traps/Trap_Hiding_comp.cpp) - Hiding trap decomposition
* _UActorComponent::UTrapBaseComponent::_[Jump Trap Component](Source/WG/Traps/Trap_Jump_comp.cpp) - Jump trap decomposition


## WIP ideas
* Decompose HP to component
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
* * ~~Trap activation on Start trigger~~ 13/10
* ~~Dynamic Material~~ 12/10
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
* ~~Transfer HUD from character to GameMode~~ 13/10

***

for direct contact [t.me/donoteatme](https://t.me/donoteatme) 

