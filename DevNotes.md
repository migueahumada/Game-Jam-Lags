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

There's a central class called `BP_ HUD` which is just a child of the HUD class. It will function as a *singleton* to all the other Widget Blueprints (WBP).

The WBPs will be divided in two:
- **Screen Widgets**: which will have a canvas and will be displayed on screen, such as:
  - HUD
  - Pause 
  - Inventory 
  - Quick Inventory 
- **SubWidgets**: That will be contained within ScreenWidgets.

All of these WBP will have an interface called `BPI_ShowableWidget`. This interface has virtual methods such as:
- `UpdateUIState`
- `OnShow`
- `OnHidden`

The way the interface works is:

1. An `Actor` with some component triggers an event for the UI.
2. The event calls an event dispatcher that shouts "Something in the UI must be changed". 
3. In the `BP_HUD` we subscribe *(bind)* to those event dispatcheres.
4. When the event we were subscribed to executes, the BP_HUD iterates over a list of Screen Widgets, which implement `BPI_ShowableWidget`.
5. During the iteration the player calls the method `UpdateUIState` in all the Screen Widgets.
6. Inside the Screen Widgets, we call `UpdateUIState` to all the subwidgets that implement `BPI_ShowableWidget`.
7. Ultimately, subwidget have their own implementation of what means for them to Update something. It can be maybe change the coin counter text or change the visibility of some items.

To update the widgets we have created a struct `S_UI_Variables` that works as a constant buffer that will contain information that will be displayed or used by the Widgets to display information.

![Image of Onta Ramón](https://blogger.googleusercontent.com/img/a/AVvXsEh12wrzFTGiwWs_Pp2oT_z_yP3PHaKoDxa757CGsw1ciemsFR8ll8uAJNyc7u3sOuWpj4qnRD-X45rMZxNNomZFjHR5UTkxhNooDFekHlQeuFVZjPg6EMYECwr5aLuD6a8fBi8hYzNQYmL8fsP7MlNy1cqeX79g7R-UKcj7WOdMY402N644BYjbUlpeuUc)


# Health, updating the player and the HUD

In this part I will use the observer pattern.
- `BP_AC_Health` -> Has functionality about the player's health. Add health, change and more stuff.
- `BP_HUD` -> It has an array of references to different widgets that has the `BPI_ShowableWidget` interface. 
- `BPI_ShowableWidget`->  Will have functions such as `UpdateWidgetState` where each widget that implemnets the interface will act on its own with the event listeners.

## Health System
The player will have a total of 16 slots of life and each slot will by divided by three. 

So the life points will be the product of 
``16 * 3 = 48``.
