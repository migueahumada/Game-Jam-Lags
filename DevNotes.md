# Where's Ramón documentation

![Image of Onta Ramón](https://img.itch.zone/aW1nLzI2NzYwMDYwLnBuZw==/original/jk5H7M.png)

This a description of the programming structure used in our game, Where's Ramón. Intellectual property belongs to Hungry Snail Games.

> It also works as a space for comments about the project from the programmer AKA Miko.

# Native UE5 System

On this project where conveniently using UE5 game framework. We aren't really using C++, we're dealing almost completely with Blueprints. We have important things such as:

- **GM_GameMode**: The game mode on the level. This chages with the level we're on.

- **BP_Player**: Is the same player for the whole game. Inherits from Character.

- **GI_Game**: This is the game instance, specifically reserved for things such as the checkpoint system and save system.

- **BP_HUD**: We're using this


# UI System
There's a central class called `BP_HUD` which is just a child of the HUD class. I'm using it as a somekind of singleton pattern. Not perfect but it does work quite well.

# Health, updating the player and the HUD

In this part I will use the observer pattern.
- `BP_AC_Health` -> Has functionality about the player's health. Add health, change and more stuff.
- `BP_HUD` -> It has an array of references to different widgets that has the `BPI_ShowableWidget` interface. 
- `BPI_ShowableWidget`->  Will have functions such as `UpdateWidgetState` where each widget that implemnets the interface will act on its own with the event listeners.

## Health System
The player will have in total 16 slots of life and each slot will by divided by three. 

So the life points will be the product of 
``16 * 3 = 48``.