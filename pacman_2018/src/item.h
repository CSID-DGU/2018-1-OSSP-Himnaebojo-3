#pragma once

#include <stdbool.h>
#include "board.h"
#include "physics.h"

#define NUM_ITEM 2

typedef enum
{
	Bullet,
	LowVelocity,
} Item;

//Different modes a fruit can be in while in-game
//Either not-displayed (haven't eaten enough pellets yet)
//Displaying
//Displayed (either we timed-out or the player ate the fruit)
typedef enum
{
	NotDisplaying_I,
	Displaying_I,
	Displayed_I
} ItemMode;

//Defines a fruit for use in Pacman.
typedef struct
{
	Item item;              // the fruit we are displaying
	ItemMode itemMode;      // the mode the fruit is currently in
	unsigned int startedAt;   // the time we started displaying this fruit at (in SDL_Ticks())
	unsigned int displayTime; // the random time between 9000-10000 ms this fruit displays for
	int x;                    // x location onscreen
	int y;                    // y location onscreen
	bool eaten;               // if the fruit was eaten while it displayed
	unsigned int eatenAt;     // the time it was eaten (used for displaying the points gained)
} GameItem;

//총알 구조체
typedef struct
{
	PhysicsBody body;
	bool bullet_displaying;
} Item_bullet;


//Returns the fruit that should be displayed for the given level.
//Item item_for_level(int level);
void item_init(GameItem gameitem[2],Board* board);

//Generates a random time between 9000-10000 ms, for which the fruit should be displayed.
int rand_item_visible_time(void);

//Resets the given fruit back to its default state.
void reset_item(GameItem *gameItem, Item item,Board *board);

//Assigns the appropriate fruit based of the level, and generates a visible-time for the fruit.
void regen_item(GameItem *gameItem, Item item);
