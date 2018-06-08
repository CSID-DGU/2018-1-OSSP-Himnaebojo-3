#include "item.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL/SDL.h>

#include "fps.h"

void reset_item(GameItem *gameItem, Board *board)
{
	//srand((unsigned)time(NULL));
	int randX = 0;
	int randY = 0;
	do {
			randX = rand() % 26;
			randY = rand() % 30;
	} while( (is_valid_square(board, randX, randY) || is_tele_square(randX, randY) ) == false);

	gameItem->item = Bullet;
	gameItem->itemMode = NotDisplaying;
	gameItem->startedAt = 0;
	gameItem->displayTime = 0;

	gameItem->eaten = false;
	gameItem->eatenAt = 0;

	gameItem->x = randX;
	gameItem->y = randY;
}

void regen_item(GameItem *gameItem, int level)
{
	gameFruit->fruit = fruit_for_level(level);
	gameFruit->displayTime = rand_fruit_visible_time();
	gameFruit->startedAt = ticks_game();
}

int rand_fruit_visible_time(void)
{
	// chosen by a random number generator
	// guarenteed to be random
	return 9500;
}
