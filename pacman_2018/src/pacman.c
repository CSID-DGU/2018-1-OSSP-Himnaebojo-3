#include "pacman.h"

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

void pacman_init_multiMode(Pacman *pacman1, Pacman *pacman2)
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

void pacman_location_init_player2(Pacman *pacman)
{
	pacman->body = (PhysicsBody) {16, 23, -8, 0, Left, Left, 1, 0, 0};
	pacman->body.velocity = 80;
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
