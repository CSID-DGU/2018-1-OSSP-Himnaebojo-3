#include "pacman.h"
#include <limits.h>

void pacman_init(Pacman *pacman)
{
	pacman_location_init(pacman);

	pacman->score = 0;
	pacman->livesLeft = 3;

	pacman->missedFrames = 0;
	pacman->godMode = false;
	pacman->boostOn = false;
	pacman->bulletOn=false;
}

void pacman_init_multiMode(Pacman *pacman1, Pacman *pacman2, int PveMode)
{
	pacman_level_init_multimode(pacman1, pacman2);

	pacman1->score = 0;
	pacman1->livesLeft = 3;

	pacman1->missedFrames = 0;
	pacman1->godMode = false;
	pacman1->boostOn = false;

	pacman2->score = 0;
	pacman2->livesLeft = 3;

	pacman2->missedFrames = 0;
	pacman2->godMode = false;
	pacman2->boostOn = false;

	if(PveMode){
		pacman2->body.velocity=90;
	}

}

void pacman_level_init(Pacman *pacman)
{
	pacman_location_init(pacman);
}

void pacman_location_init(Pacman *pacman)
{
	pacman->body = (PhysicsBody) {14, 23, -8, 0, Left, Left, 1, 0, 0};
	pacman->body.velocity = 80;
	pacman->movementType = Unstuck;
	pacman->lastAttemptedMoveDirection = Left;
}

void pacman_level_init_multimode(Pacman *pacman1, Pacman *pacman2)
{
	pacman_location_init_player1(pacman1);
	pacman_location_init_player2(pacman2);
}

void pacman_location_init_player1(Pacman *pacman)
{
	pacman->body = (PhysicsBody) {12, 23, -8, 0, Left, Left, 1, 0, 0};
	pacman->body.velocity = 80;
	pacman->movementType = Unstuck;
	pacman->lastAttemptedMoveDirection = Left;
}

void pacman_location_init_player2(Pacman *pacman, int pveMode)
{
	pacman->body = (PhysicsBody) {16, 23, -8, 0, Left, Left, 1, 0, 0};

	pacman->body.velocity = 80;
	if(pveMode){
		pacman->body.velocity = 90;
	}

	pacman->movementType = Unstuck;
	pacman->lastAttemptedMoveDirection = Right;
}

void pacman_death(Pacman *pacman)
{
	pacman->body = (PhysicsBody) {14, 23, -8, 0, Left, Left, 1, 0, 0};
	pacman->body.velocity = 0;
	pacman->movementType = Unstuck;
	pacman->lastAttemptedMoveDirection = Right;
}

int pacman_speed_normal(int level)
{
	if (level == 1)  return 80;
	if (level <= 4)  return 90;
	if (level <= 20) return 100;
	return 90;
}

int pacman_speed_fright(int level)
{
	if (level == 1)  return 90;
	if (level <= 4)  return 95;
	if (level <= 20) return 100;
	return 100;
}


typedef struct
{
	Direction dir;
	int distance;
} Targetcalc;

typedef struct
{
	int x;
	int y;
} Boardoffset;

Direction next_direction_pac(Pacman *pac, Board *board, int target_x, int target_y)
{
	Targetcalc targets[4] =  { {Up, INT_MAX}, {Left, INT_MAX}, {Down, INT_MAX}, {Right, INT_MAX}};
	Boardoffset offsets[4] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} };

	int x, y;

	dir_xy(pac->lastAttemptedMoveDirection, &x, &y);

	//calculate the distances between the squares (or if it is even valid)
	for (int i = 0; i < 4; i++)
	{
		int testX = pac->body.x  + offsets[i].x;
		int testY = pac->body.y  + offsets[i].y;

		if (testX == 0&& testY==14) testX = 26;
		if (testX == 27&& testY==14) testX = 1;

		//make sure the square is a valid walkable square
		if (!(is_valid_square(board, testX, testY) || is_tele_square(testX, testY))) continue;

		//a further condition is that ghosts cannot enter certain squares moving upwards
		//if (targets[i].dir == Up && is_ghost_noup_square(testX, testY)) continue;

		int dx = testX - target_x;
		int dy = testY - target_y;
		//really the square root, but don't take to keep precision
		targets[i].distance = (dx * dx + dy * dy);
	}

	//a ghost can never turn around, so exclude the opposite direction to what they are facing
	Direction reverseDir = dir_opposite(pac->lastAttemptedMoveDirection);

	Targetcalc shortest = {Right, INT_MAX};

	//iterate backwards so that we get the tie-breaking logic for free
	for (int i = 3; i >= 0; i--)
	{
		if (targets[i].dir == reverseDir) continue;

		if (targets[i].distance <= shortest.distance)
		{
			shortest.distance = targets[i].distance;
			shortest.dir = targets[i].dir;
		}
	}

	return shortest.dir;
}
Direction next_direction_pac2(Pacman *pac, Board *board, int target_x, int target_y)
{
	Targetcalc targets[4] =  { {Up, 0}, {Left, 0}, {Down, 0}, {Right, 0}};
	Boardoffset offsets[4] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} };

	//calculate the distances between the squares (or if it is even valid)
	for (int i = 0; i < 4; i++)
	{
		int testX = pac->body.x  + offsets[i].x;
		int testY = pac->body.y  + offsets[i].y;

		if (testX == 0 &&testY==14) testX = 26;
		if (testX == 27&&testY==14) testX = 1;

		//make sure the square is a valid walkable square
		if (!(is_valid_square(board, testX, testY) || is_tele_square(testX, testY))) continue;

		int dx = testX - target_x;
		int dy = testY - target_y;
		//really the square root, but don't take to keep precision
		targets[i].distance = (dx * dx + dy * dy);
	}

	Direction reverseDir = dir_opposite(pac->lastAttemptedMoveDirection);
	Targetcalc farthest = {Right, 0};

	//iterate backwards so that we get the tie-breaking logic for free
	for (int i = 3; i >= 0; i--)
	{
		if (targets[i].distance > farthest.distance)
		{
			farthest.distance = targets[i].distance;
			farthest.dir = targets[i].dir;
		}
	}

	return farthest.dir;
}
