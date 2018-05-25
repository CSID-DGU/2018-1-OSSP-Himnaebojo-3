#include "item.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL/SDL.h>

#include "fps.h"


void item_init(GameItem gameitem[2],Board* board)
{
	gameitem[0].item = Bullet;
	gameitem[1].item = LowVelocity;

<<<<<<< HEAD
	for (int i = 0; i < 2; i++)
=======
	for (int i = 0; i < 4; i++)
>>>>>>> master
	{
		reset_item(&gameitem[i], gameitem[i].item, board);
	}

	srand(time(NULL));
}

void reset_item(GameItem *gameItem, Item item,Board *board)//게임상태, item종류, 보드를 입력받음.
{
	//srand((unsigned)time(NULL));
	int randX = 0;
	int randY = 0;
	do
	{
			randX = rand() % 26;
			randY = rand() % 30;
	} while( (is_valid_square(board, randX, randY) || is_tele_square(randX, randY) ) == false);

	gameItem->item = item;
	gameItem->itemMode = NotDisplaying_I;
	gameItem->startedAt = 0;
	gameItem->displayTime = 0;

	gameItem->eaten = false;
	gameItem->eatenAt = 0;

	gameItem->x = randX;
	gameItem->y = randY;
}

void regen_item(GameItem *gameItem, Item item)//게임상태와 아이템 종류를 입력받음
{
	gameItem->item = item;
	gameItem->displayTime = rand_item_visible_time();
	gameItem->startedAt = ticks_game();
}

int rand_item_visible_time(void)
{
	// chosen by a random number generator
	// guarenteed to be random
	return 15000;
}

