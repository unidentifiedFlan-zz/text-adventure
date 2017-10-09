# text-adventure
console text adventure framework + short example

This is a framework in which to create text adventure games. Adventures can then be played in the command console. New text 
adventures are created by substituting for adventure1(.cpp/.h) and adding the appropriate header file to the top of the main file (TextAdventure.cpp). A short example, adventure1.cpp, is included demonstrating how an adventure might be constructed.

There are three classes: scenes, versions and options. Each scene relates to a place in the game (this could be, for example,
the kitchen or the kitchen table) and the player interacts with a particular version of that scene. Within each version are  options that may be taken by the player. The scenes each therefore have a list of corresponding versions, and each version a 
list of options. 

The current scene is represented by a pointer to a scene in the list of all scenes (sceneList) which allows the player to jump 
from one scene or scene version to another depending on their actions. Scenes have to be regularly updated to reflect the actions 
taken by the player elsewhere. A Boolean tensor (actionTracker) is used to track which options have been taken throughout the game and scene versions are updated to the next versions by checking the relevant elements of this tensor. The relevant elements are listed in the updateTracker vector found in the class type "version".
