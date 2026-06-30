# Dev notes

This notes are only meant to guide the programming stuff, so feel free to read.

# Decoupling Systems

As of now the game is

# UI System
There's a central class called `BP_HUD` which is just a child of the HUD class. I'm using it as a somekind of singleton pattern. Not perfect but it does work quite well.

# Health, updating the player and the HUD

In this part I will use the observer pattern.
- `BP_AC_Health` -> Has functionality about the player's health. Add health, change and more stuff.
- `BP_HUD` -> It has an array of references to different widgets that has the `BPI_ShowableWidget` interface. 
- `BPI_ShowableWidget`->  Will have functions such as `UpdateWidgetState` where each widget that implemnets the interface will act on its own with the event listeners.

# Health System
The player will have in total 16 slots of life and each slot will by divided by three. 

So the life points will be the product of 
``16 * 3 = 48``.