# What is this?
This is a fork of [Skyrim Together Reborn](https://github.com/tiltedphoques/TiltedEvolution) (STR) that support custom behavior with Nemesis or FNIS (not tested yet). By using this fork, you forfeit any technical support from support team of STR developer. The software is provided as is and no support will be given by me (edho). Please only use it if you know what you are doing. If you are a beginner in STR, i suggest playing with the official release instead. I DO NOT recommend any kind of playthrough using this fork. This fork exists as a testing only and a proof of concept for STR developer if they decided to revamp the animation system of STR. All credit of making STR possible go to the developer. This fork will only exist as a fork and will not be merged to the official STR repository. Anyone who uses this piece of software and its source codes and its derivative must follow the license provided.

## Skyrim Together
Skyrim Together Reborn (STR) is The Elder Scroll V: Skyrim (skyrim) mod that allows player to play the game in multiplayer manner. STR dev do such an amazing job bringing skyrim to coop play. However, STR is developed with vanilla game in mind and no other mods beside STR will be supported. This proves a little bit devastating for modding community as many mods do not bode well with STR. One such type of mod is mod that change any animation behavior variable of actor e.g. animation mods that uses NEMESIS UNLIMITED BEHAVIOR ENGINE. This fork seeks to remedies this specific case.

## The Devil
The devil is always in the detail. I hope user and modders read this so they can gain knowledge on why changing behavior variables doesn't work in STR. Before we go in to much detail, i need to provide some term and its meaning. Local payer mean the player character in the local space, they are actor with formID of 0x14. Remote player is character of other player seen in game, they are actor (npc) with generated fromID (start with ff). The way the developer make animation synchronization works in STR is by synchronizing actors behavior variables of remote player. Some variables are synced to make animation work while some dont. Now the way the developer map an actor with its correct set of variable to sync is through some hardcoded hash. Each animation graph descriptor hash each own hash which is hardcoded by the developer. Sadly, the hash is calculated from the behavior variables themselves. This means that any attempt to change any behavior variables will result in the hash changing and causing hash mismatch. When hash mitmatch happened, a animation graph descriptor of actor that has the same hash cannot be found thus the actor animation cannot be synchronized. Action however like dodging that are provided by some mods worked fine but any animations that depends on some behaviors variable being synchronized will not work, e.g. walking.  

## How does this fork works?
This fork works by creating a hash for some modded animation graph descriptor dynamically on the fly when an actor attempt to do some animation. The hash creation are only done once per behavior type and wont be done again after that. This way, actor with modified behavior variable will synchronize well using this fork. Some others thing are also hardcoded by the developer and this fork will needs much more work.

## What functionality is provided?
This fork added functionality to synchronize actor with modded animation graph descriptor (behaviors variable). This fork also provided a way for modders to add more behavior variable to be synchronized. The developer of STR has provided a soft limit of 64 boolean variables and 64 integer + real variable. Either adhere to their standard for optimal stability or mod it till it crash. This fork also provided a way for modder to mod behavior variables of creature (not tested yet). See modder section for a more detailed explanation. 

## Installation
### Vortex
1. Install Official Skyrim Together Reborn.
2. Download the files provided (Reborn.zip).
3. Drag and drop (import) the files to vortex download.
4. Overwrite the official release with this fork. 
### Manual
1. Install Official Skyrim Together Reborn.
2. Download the files provided (Reborn.zip).
3. Extact the files to STR installation folder.

## Modders
This section provide modders with the resource to start. The functionality for modders has been described in earlier section. This section describe how to do it. The structure type for a patch for this fork is very simple. [root] folder refers to where the STR is installed (e.g. Data/SkyrimTogetherReborn). 

A patch consist of 5 type of files. file with a name that contains "__name.txt" are there for debugging purpose only but should contain the name of the behaviors to be patched. While its not mandated, there should be only one file of this kind per-patch. 

Files with a name that contains "__float.txt", "__int.txt" or "__bool.txt" respectively contains real, integer and boolean variables that are going to be synced. There can be many files of these kind. For example file "Vanilla__float.txt" provide float variable found in vanilla behavior to be synced while file "TDM__float.txt" provide float variable found in True Directional Movement mod.   

Last kind of file is the sig file which contains "__sig.txt" in their name. While it is not mandated, there should be only one file of this kind per-patch. This file contains some variable that are needed to catch a signature of an animation graph descriptor. For example, given a dummy variable created by NEMESIS patch for 0_masterbehavior.hkx called "bSTRHumanoid" then this variable will exist for all actor that uses 0_master.hkx hence this variable can be used to signature said behavior. Creating a patch like this by NEMESIS is optional but the sig must be unique to a certain behavior. There can be many sig variable provided in a single sig file separated by a new line. This kind of signaturing is implemented as its easy to work with considering STR dev implementation.

Behavior variables are aggregated in runtime. What does this means is that behavior variables found in seperate file in the same folder (e.g. data/meshes/actors/character/behaviors) will all be merged in runtime. For example, behavior variables of 0_master.hkx and magicbehavior.hkx will be merged. This means only create a sig file for each behavior folder. 

An example has been provided to patch 0_master.hkx (humanoid) to allow modded behavior variable. Another example is provided to sync TDM behaviors (horse archery).

Creature behavior aren't tested yet as the one that made this fork is busy with life. But they might be possible. Using the directive above and the example given, one can theoritically provide a patch for creature behavior. However, no promise are made. 

## Known Issue
1. Somehow you must not be bound when your character loaded for the first time. So play until your character is not bounded. Save the game. Exit the game. Boot it back up. Reload that save. 
2. Werewolf transformation and Vampire transformation behaviors hash is hardcoded by STR developer. I can change this, but i am looking for a better implementation without disturbing their code.
3. Horse doesn't work well with this mod. The horse animation will stop when its mounted or dismounted (like T posing in humanoid). Known simple fix for this is to disable then enable the horse. But its tedious. A fix for this is currently wanted.
4. CRASHES.. Expect a lot, lot, lots of crashes. People crashes all the time using official release of STR. this fork might make it worse.

## What this mod isn't/don't/won't!
1. This fork doesn't not touch any related DAR (Dynamic Animation Replacer) animation or whatnot. Expect DAR to work the same with or without this fork. 
2. This fork won't automagically make animation work in STR.
3. This fork won't provide any patch for any behavior except the example given.
4. This fork won't automagically synchronize behavior variables. Modders must provide on what variable to sync.
5. This fork won't make it to the official release. This fork will stay as is. 
6. This fork won't make animation of remote player to be smoothly played. Expect lots of Jank and jazz.

## The future
This fork will hopefully be made into a mod for STR if the developer of STR decided to implement a native modding API (akin to SKSE).

## Contributing
Pull request will not be accepted at the moment.

## License
[![GNU GPLv3 Image](https://www.gnu.org/graphics/gplv3-127x51.png)](http://www.gnu.org/licenses/gpl-3.0.en.html)

Tilted Online is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.