# 2dEngine
Base for a variety of planned 2D game projects. Currently very WIP.
Everything in this is based on my old "Kawaii" project from 2015.
At the time, I wanted to create a working basic platformer as quickly as possible.
While I accomplished this goal, the side effect of working as quickly as possible was that I could barely follow my own code and I was not able to easily add or change anything without the whole thing tumbling down.
For this project, I have a better idea of what I want to accomplish and exactly how to accomplish it.
First, I decided that "game.cpp" was much too bloated, and the main game loop had become a nightmare of a function that handled everything from initializing SDL components to managing each frame of animation for each actor on the screen.
I've tried to extend what I've learned about object-oriented programming and design patterns since then to create a more dynamic system for creating, updating, and eventually destroying sprites/actors.
So far, I have brought everything that has to do with SDL's window management and texture drawing into its own class and can simply use this object and its methods to draw the level and any actors that are currently in the list of entities.
I can also "spawn" and "despawn" any type of entity on the fly while making sure that whatever I spawn will be updated and drawn every frame, and then completely removed from the list when destroyed.
There are more than a few classes and functions that need to be reworked or taken out completely, but I have enjoyed using this as a way to look back on my old personal code and apply what I've learned since.

Please excuse some of the code smells. Some are worse than others (Currently almost everything I'm using is a public variable, I do know how to use getters and setters I promise), but time is of the essence and I've been trying to apply new things that I've learned and worry about cleaning up later.
