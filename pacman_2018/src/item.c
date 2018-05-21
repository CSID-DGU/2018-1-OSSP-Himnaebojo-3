#include "item.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL/SDL.h>

#include "fps.h"


/*Item item_for_level(int level)
{
	if (level < 1)
	{
		printf("invalid level: %d\n", level);
		printf("aborting\n");
		exit(1);
	}

	switch (level)
	{
		case 1:           return Bullet;
		case 2:           return LowVelocity;
		case 3: 			 return Bullet;
		case 4: 			 return LowVelocity;
		case 5:			 return Bullet;
		case 6: 			 return LowVelocity;
		case 7:  			 return Bullet;
		case 8:  			 return LowVelocity;
		case 9: 			 return Bullet;
		case 10: 			 return LowVelocity;
		case 11:			 return Bullet;
		case 12:			 return LowVelocity;
		default:          return Bullet;
	}
}*/
//기존의 reset_item을 item_init으로 대체해야 함.
void item_init(GameItem gameitem[2],Board* board)
{
	gameitem[0].item = Bullet;
	gameitem[1].item = LowVelocity;

	for (int i = 0; i < 4; i++)
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
