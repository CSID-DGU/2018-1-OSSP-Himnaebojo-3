#include "pacman.h"

#include <limits.h>

void pacman_init(Pacman *pacman) {
	pacman_location_init(pacman);

	pacman->score = 0;
	pacman->livesLeft = 3;

	pacman->missedFrames = 0;
	pacman->godMode = false;
	pacman->boostOn = false;
}

void pacman_level_init(Pacman *pacman) {
	pacman_location_init(pacman);
}

void pacman_location_init(Pacman *pacman) {
	pacman->body = (PhysicsBody ) { 14, 23, -8, 0, Left, Left, 1, 0, 0 };
	pacman->body.velocity = 80;
	pacman->movementType = Unstuck;
	pacman->lastAttemptedMoveDirection = Left;
	pacman->transDirection = Left; //add
}

int pacman_speed_normal(int level) {
	if (level == 1)
		return 80;
	if (level <= 4)
		return 90;
	if (level <= 20)
		return 100;
	return 90;
}

int pacman_speed_fright(int level) {
	if (level == 1)
		return 90;
	if (level <= 4)
		return 95;
	if (level <= 20)
		return 100;
	return 100;
}

typedef struct {
	Direction dir;
	int distance;
} Targetcalc;

typedef struct {
	int x;
	int y;
} Boardoffset;

Direction next_direction_pac(Pacman *pac, Board *board, Direction Ghost_direction, int target_x, int target_y,int flag)
{

	Targetcalc targets[4] = { { Up, INT_MAX }, { Left, INT_MAX }, { Down,
			INT_MAX }, { Right, INT_MAX } };
	Boardoffset offsets[4] = { { 0, -1 }, { -1, 0 }, { 0, 1 }, { 1, 0 } };

	int x, y;
	int dif_x=pac->body.x-target_x;//ghost_pac_distant
	int dif_y=pac->body.y-target_y;

	 if (flag==1)
	 {
		dir_xy(pac->lastAttemptedMoveDirection, &x, &y);
		int testX = pac->body.x +x;
		int testY = pac->body.y +y;
		if (dif_x > 0 && dif_y > 0) {
			if (Ghost_direction== Up) {
				//	if (testX == 0) testX = 26;
				//	if (testX == 27) testX = 1;
				if (is_valid_square(board, testX + 0, testY + 1)) {
					return Down;
				} else if (is_valid_square(board, testX + 1, testY + 0)) {
					return Right;
				} else
					return Left;
			} else if (Ghost_direction == Down) {
				if (is_valid_square(board, testX + 0, testY + 1)) {
					return Down;
				} else if (is_valid_square(board, testX + 1, testY + 0)) {
					return Right;
				} else
					return Up;
			} else if (Ghost_direction == Left) {
				if (is_valid_square(board, testX + 0, testY + 1)) {
					return Down;
				} else if (is_valid_square(board, testX + 1, testY + 0)) {
					return Right;
				} else
					return Up;
			} else if (Ghost_direction == Right) {
				if (is_valid_square(board, testX + 0, testY + 1)) {
					return Down;
				} else if (is_valid_square(board, testX + 1, testY + 0)) {
					return Right;
				} else
					return Left;
			}
		} else if (dif_x > 0 && dif_y == 0) {
			if (Ghost_direction == Up) {
				//	if (testX == 0) testX = 26;
				//	if (testX == 27) testX = 1;

				if (is_valid_square(board, testX + 1, testY + 0)) {
					return Right;
				} else if (is_valid_square(board, testX + 0, testY + 1)) {
					return Down;
				} else
					return Up;
			} else if (Ghost_direction == Down) {
				if (is_valid_square(board, testX + 1, testY + 0)) {
					return Right;
				} else if (is_valid_square(board, testX + 0, testY - 1)) {
					return Up;
				} else
					return Down;
			} else if (Ghost_direction == Left) {
				if (is_valid_square(board, testX + 1, testY + 0)) {
					return Right;
				} else if (is_valid_square(board, testX + 0, testY - 1)) {
					return Up;
				} else
					return Down;

			} else if (Ghost_direction == Right) {
				if (is_valid_square(board, testX + 1, testY + 0)) {
					return Right;
				} else if (is_valid_square(board, testX + 0, testY - 1)) {
					return Up;
				} else
					return Down;
			}
		} else if (dif_x > 0 && dif_y < 0) {
			if (Ghost_direction == Up) {
				//	if (testX == 0) testX = 26;
				//	if (testX == 27) testX = 1;

				if (is_valid_square(board, testX + 1, testY + 0)) {
					return Right;
				} else if (is_valid_square(board, testX + 0, testY - 1)) {
					return Up;
				} else
					return Down;
			} else if (Ghost_direction == Down) {
				if (is_valid_square(board, testX + 1, testY + 0)) {
					return Right;
				} else if (is_valid_square(board, testX + 0, testY - 1)) {
					return Up;
				} else
					return Left;
			} else if (Ghost_direction == Left) {
				if (is_valid_square(board, testX + 1, testY + 0)) {
					return Right;
				} else if (is_valid_square(board, testX + 0, testY - 1)) {
					return Up;
				} else
					return Down;

			} else if (Ghost_direction== Right) {
				if (is_valid_square(board, testX + 1, testY + 0)) {
					return Right;
				} else if (is_valid_square(board, testX + 0, testY - 1)) {
					return Up;
				} else
					return Left;
			}
		} else if (dif_x == 0 && dif_y < 0) {
			if (Ghost_direction == Up) {
				//	if (testX == 0) testX = 26;
				//	if (testX == 27) testX = 1;

				if (is_valid_square(board, testX + 0, testY - 1)) {
					return Up;
				} else if (is_valid_square(board, testX + 1, testY + 0)) {
					return Right;
				} else
					return Left;
			} else if (Ghost_direction == Down) {
				if (is_valid_square(board, testX + 0, testY - 1)) {
					return Up;
				} else if (is_valid_square(board, testX + 1, testY + 0)) {
					return Right;
				} else
					return Left;
			} else if (Ghost_direction == Left) {
				if (is_valid_square(board, testX + 0, testY - 1)) {
					return Up;
				} else if (is_valid_square(board, testX + 1, testY + 0)) {
					return Right;
				} else
					return Down;
			} else if (Ghost_direction== Right) {
				if (is_valid_square(board, testX + 0, testY - 1)) {
					return Up;
				} else if (is_valid_square(board, testX - 1, testY + 0)) {
					return Left;
				} else
					return Down;
			}
		} else if (dif_x < 0 && dif_y < 0) {
			if (Ghost_direction == Up) {
				//	if (testX == 0) testX = 26;
				//	if (testX == 27) testX = 1;

				if (is_valid_square(board, testX - 1, testY + 0)) {
					return Left;
				} else if (is_valid_square(board, testX + 0, testY - 1)) {
					return Up;
				} else
					return Down;
			} else if (Ghost_direction == Down) {
				if (is_valid_square(board, testX - 1, testY + 0)) {
					return Left;
				} else if (is_valid_square(board, testX + 0, testY - 1)) {
					return Up;
				} else
					return Right;
			} else if (Ghost_direction == Left) {
				if (is_valid_square(board, testX - 1, testY + 0)) {
					return Left;
				} else if (is_valid_square(board, testX + 0, testY - 1)) {
					return Up;
				} else
					return Right;
			} else if (Ghost_direction == Right) {
				if (is_valid_square(board, testX - 1, testY + 0)) {
					return Left;
				} else if (is_valid_square(board, testX + 0, testY - 1)) {
					return Up;
				} else
					return Down;
			}
		} else if (dif_x < 0 && dif_y == 0) {
			if (Ghost_direction == Up) {
				//	if (testX == 0) testX = 26;
				//	if (testX == 27) testX = 1;

				if (is_valid_square(board, testX - 1, testY + 0)) {
					return Left;
				} else if (is_valid_square(board, testX + 0, testY + 1)) {
					return Down;
				} else
					return Up;
			} else if (Ghost_direction== Down) {
				if (is_valid_square(board, testX - 1, testY + 0)) {
					return Left;
				} else if (is_valid_square(board, testX + 0, testY - 1)) {
					return Up;
				} else
					return Right;
			} else if (Ghost_direction == Left) {
				if (is_valid_square(board, testX - 1, testY + 0)) {
					return Left;
				} else if (is_valid_square(board, testX + 0, testY + 1)) {
					return Down;
				} else
					return Up;
			} else if (Ghost_direction == Right) {
				if (is_valid_square(board, testX - 1, testY + 0)) {
					return Left;
				} else if (is_valid_square(board, testX + 0, testY + 1)) {
					return Down;
				} else
					return Up;
			}
		} else if (dif_x < 0 && dif_y > 0) {
			if (Ghost_direction == Up) {
				//	if (testX == 0) testX = 26;
				//	if (testX == 27) testX = 1;

				if (is_valid_square(board, testX - 1, testY + 0)) {
					return Left;
				} else if (is_valid_square(board, testX + 0, testY + 1)) {
					return Down;
				} else
					return Right;
			} else if (Ghost_direction == Down) {
				if (is_valid_square(board, testX - 1, testY + 0)) {
					return Left;
				} else if (is_valid_square(board, testX + 0, testY + 1)) {
					return Down;
				} else
					return Up;
			} else if (Ghost_direction== Left) {
				if (is_valid_square(board, testX - 1, testY + 0)) {
					return Left;
				} else if (is_valid_square(board, testX + 0, testY + 1)) {
					return Down;
				} else
					return Right;
			} else if (Ghost_direction == Right) {
				if (is_valid_square(board, testX - 1, testY + 0)) {
					return Left;
				} else if (is_valid_square(board, testX + 0, testY + 1)) {
					return Down;
				} else
					return Up;
			}
		} else if (dif_x == 0 && dif_y > 0) {
			if (Ghost_direction == Up) {
				//	if (testX == 0) testX = 26;
				//	if (testX == 27) testX = 1;

				if (is_valid_square(board, testX + 0, testY + 1)) {
					return Down;
				} else if (is_valid_square(board, testX - 1, testY + 0)) {
					return Left;
				} else
					return Right;
			} else if (Ghost_direction == Down) {
				if (is_valid_square(board, testX + 0, testY + 1)) {
					return Down;
				} else if (is_valid_square(board, testX - 1, testY + 0)) {
					return Left;
				} else
					return Right;
			} else if (Ghost_direction == Left) {
				if (is_valid_square(board, testX + 0, testY + 1)) {
					return Down;
				} else if (is_valid_square(board, testX + 1, testY + 0)) {
					return Right;
				} else
					return Up;
			} else if (Ghost_direction == Right) {
				if (is_valid_square(board, testX + 0, testY + 1)) {
					return Down;
				} else if (is_valid_square(board, testX - 1, testY + 0)) {
					return Left;
				} else
					return Up;
			}
		}

	}

	dir_xy(pac->lastAttemptedMoveDirection, &x, &y);

	//calculate the distances between the squares (or if it is even valid)
	for (int i = 0; i < 4; i++) {
		int testX = pac->body.x + x + offsets[i].x;
		int testY = pac->body.y + y + offsets[i].y;

		if (testX == 0)
			testX = 26;
		if (testX == 27)
			testX = 1;

		//make sure the square is a valid walkable square
		if (!(is_valid_square(board, testX, testY)
				|| is_tele_square(testX, testY)))
			continue;

		int dx = testX - target_x;
		int dy = testY - target_y;

		//really the square root, but don't take to keep precision
		targets[i].distance = (dx * dx + dy * dy);
	}
	Direction reverseDir = dir_opposite(pac->lastAttemptedMoveDirection);
	Targetcalc shortest = { Right, INT_MAX };

	//iterate backwards so that we get the tie-breaking logic for free
	for (int i = 3; i >= 0; i--) {
		if (targets[i].distance <= shortest.distance) {
			if (targets[i].dir == reverseDir) continue;
			shortest.distance = targets[i].distance;
			shortest.dir = targets[i].dir;
		}
	}

	return shortest.dir;
}
