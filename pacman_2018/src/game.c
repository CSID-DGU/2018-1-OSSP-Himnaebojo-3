#include "game.h"

#include "animation.h"
#include "board.h"
#include "fps.h"
#include "input.h"
#include "main.h"
#include "pacman.h"
#include "pellet.h"
#include "physics.h"
#include "renderer.h"
#include "sound.h"
#include "text.h"
#include "window.h"
#include <stdlib.h>
#include <time.h>

static void process_player(PacmanGame *game);
static void process_player2(PacmanGame *game);

static void process_fruit(PacmanGame *game);
static void process_item(PacmanGame *game);
<<<<<<< HEAD

=======
>>>>>>> cf13d40c95e1630a99d34a658e66cf9b0cb324af
static void process_ghosts(PacmanGame *game);

static void process_pellets(PacmanGame *game);
static void process_pellets2(PacmanGame *game);


<<<<<<< HEAD
//static bool check_pacghost_collision(PacmanGame *game); //return true if pacman collided with any ghosts
static bool check_pacghost_collision(PacmanGame *game, Pacman *pacman); //return true if pacman collided with any ghosts   //return true if pacman collided with any ghosts
=======
  //return true if pacman collided with any ghosts

//static bool check_pacghost_collision(PacmanGame *game); //return true if pacman collided with any ghosts
static bool check_pacghost_collision(PacmanGame *game, Pacman *pacman); //return true if pacman collided with any ghosts

>>>>>>> cf13d40c95e1630a99d34a658e66cf9b0cb324af
static void enter_state(PacmanGame *game, GameState state); //transitions to/ from a state
static bool resolve_telesquare(PhysicsBody *body);          //wraps the body around if they've gone tele square

void game_tick(PacmanGame *game)
{
	unsigned dt = ticks_game() - game->ticksSinceModeChange;

	switch (game->gameState)
	{
		case GameBeginState:
			// plays the sound, has the "player 1" image, has the "READY!" thing

			break;
		case LevelBeginState:
			// similar to game begin mode except no sound, no "Player 1", and slightly shorter duration

			break;
		case GamePlayState:
			// everyone can move and this is the standard 'play' game mode
<<<<<<< HEAD
=======

>>>>>>> cf13d40c95e1630a99d34a658e66cf9b0cb324af
			if(game->pacman.livesLeft>=0){
				process_player(game);
				process_pellets(game);
			}

<<<<<<< HEAD
			process_item(game);
=======
>>>>>>> cf13d40c95e1630a99d34a658e66cf9b0cb324af
			process_fruit(game);

			if(game->multiMode && game->pacman2.livesLeft>=0){
				process_player2(game);
				process_pellets2(game);
<<<<<<< HEAD
=======
				//process_fruit2(game);
>>>>>>> cf13d40c95e1630a99d34a658e66cf9b0cb324af
			}


			if(game->pacman.bulletOn==true&&game->bullet.bullet_displaying==true)
			{
				process_bullet(game);
			}


			process_ghosts(game);


<<<<<<< HEAD
			if(game->pacman.bulletOn==true&&game->bullet.bullet_displaying==true) process_bullet(game, &game->pacman, &game->bullet);
			if(game->pacman2.bulletOn==true&&game->bullet2.bullet_displaying==true) process_bullet(game, &game->pacman2, &game->bullet2);

			if(!game->multiMode)
				game->highscore = game->pacman.score;
			else if (game->pacman.score > game->highscore){
				game->highscore = game->pacman.score;
			}
			else{
				game->highscore = game->pacman2.score;
			}
=======
			if (game->pacman.score > game->highscore) game->highscore = game->pacman.score;
			else game->highscore = game->pacman2.score;//TODO:PLAYER2 SCORE
>>>>>>> cf13d40c95e1630a99d34a658e66cf9b0cb324af

			break;
		case WinState:
			//pacman eats last pellet, immediately becomes full circle
			//everything stays still for a second or so
			//monsters + pen gate disappear
			//level flashes between normal color and white 4 times
			//screen turns dark (pacman still appears to be there for a second before disappearing)
			//full normal map appears again
			//pellets + ghosts + pacman appear again
			//go to start level mode

			break;
		case DeathState:
			// pacman has been eaten by a ghost and everything stops moving
			// he then does death animation and game starts again

			//everything stops for 1ish second

			//ghosts disappear
			//death animation starts
			//empty screen for half a second

			break;
		case GameoverState:
			// pacman has lost all his lives
			//it displays "game over" briefly, then goes back to main menu
			break;
	}

	//
	// State Transitions - refer to gameflow for descriptions
	//

	bool allPelletsEaten = game->pelletHolder.numLeft == 0;
	//bool collidedWithGhost = check_pacghost_collision(game);
	bool collidedWithGhost = check_pacghost_collision(game, &game->pacman);
	bool collidedWithGhost2;
	if(game->multiMode){
		collidedWithGhost2 = check_pacghost_collision(game, &game->pacman2);
	}

	int lives = game->pacman.livesLeft;

	switch (game->gameState)
	{
		case GameBeginState:
			if (dt > 2200) enter_state(game, LevelBeginState);

			break;
		case LevelBeginState:
			if (dt > 1800) enter_state(game, GamePlayState);
			game->pacman.godMode = false;

			break;
		case GamePlayState:
<<<<<<< HEAD
			if(!game->multiMode){
				if (key_held(SDLK_k)) enter_state(game, DeathState);
				else if (allPelletsEaten) enter_state(game, WinState);
				else if (collidedWithGhost){
					bullet_effect_eliminate(&game->pacman);
					enter_state(game, DeathState);
				}
=======
			//TODO: remove this hacks
			if(!game->multiMode){
				if (key_held(SDLK_k)) enter_state(game, DeathState);

				else if (allPelletsEaten) enter_state(game, WinState);
				else if (collidedWithGhost) enter_state(game, DeathState);
>>>>>>> cf13d40c95e1630a99d34a658e66cf9b0cb324af
			}
			else{
				if (key_held(SDLK_k)) enter_state(game, DeathState);
				else if (allPelletsEaten) enter_state(game, WinState);
				else if (collidedWithGhost){//
					if(game->pacman.livesLeft>0){
						pacman_location_init_player1(&game->pacman);
					}else{

					}
					game->pacman.livesLeft--;
<<<<<<< HEAD
					bullet_effect_eliminate(&game->pacman);
=======
>>>>>>> cf13d40c95e1630a99d34a658e66cf9b0cb324af
					//unsigned deathdt = ticks_game();
					//draw_pacman_death(&game->pacman, 1500 - 1000);
				}
				else if (collidedWithGhost2){
					pacman_location_init_player2(&game->pacman2);
					game->pacman2.livesLeft--;
<<<<<<< HEAD
					bullet_effect_eliminate(&game->pacman2);
=======
>>>>>>> cf13d40c95e1630a99d34a658e66cf9b0cb324af
					//unsigned dt;
					//printf("%d\n", dt);
					//draw_pacman_death(&game->pacman2, deathdt - 1000);
				}
				else if(game->pacman.livesLeft<=0 && game->pacman2.livesLeft<=0){
					enter_state(game, DeathState);
				}
			}

			break;
		case WinState:
			//if (transitionLevel) //do transition here
			if (dt > 4000) enter_state(game, LevelBeginState);

			break;
		case DeathState:
			if (dt > 4000)
			{
				if (lives <= 0) enter_state(game, GameoverState);
				else enter_state(game, LevelBeginState);
			}

			break;
		case GameoverState:
			if (dt > 2000)
			{
				//TODO: go back to main menu

			}
			break;
	}
}

void game_render(PacmanGame *game)
{
	unsigned dt = ticks_game() - game->ticksSinceModeChange;
	static unsigned godDt = 0;
	static bool godChange = false;

	//common stuff that is rendered in every mode:
	// 1up + score, highscore, base board, lives, small pellets, fruit indicators
	draw_common_oneup(true, game->pacman.score);
	draw_common_highscore(game->highscore);

	draw_pacman_lives(game->pacman.livesLeft);

	draw_small_pellets(&game->pelletHolder);
	draw_fruit_indicators(game->currentLevel);


	//in gameover state big pellets don't render
	//in gamebegin + levelbegin big pellets don't flash
	//in all other states they flash at normal rate

	switch (game->gameState)
	{
		case GameBeginState:
			draw_game_playerone_start();
			draw_game_ready();

			draw_large_pellets(&game->pelletHolder, false);
			draw_board(&game->board);
			break;
		case LevelBeginState:
			draw_game_ready();

			//we also draw pacman and ghosts (they are idle currently though)
			draw_pacman_static(&game->pacman);
			if(game->multiMode){
				draw_pacman_static(&game->pacman2);
			}
			for (int i = 0; i < 4; i++) draw_ghost(&game->ghosts[i]);

			draw_large_pellets(&game->pelletHolder, false);
			draw_board(&game->board);
			break;
		case GamePlayState:
			draw_large_pellets(&game->pelletHolder, true);
			draw_board(&game->board);

			if (game->gameFruit1.fruitMode == Displaying_F) draw_fruit_game(game->currentLevel, &game->gameFruit1);
			if (game->gameFruit2.fruitMode == Displaying_F) draw_fruit_game(game->currentLevel, &game->gameFruit2);
			if (game->gameFruit3.fruitMode == Displaying_F) draw_fruit_game(game->currentLevel, &game->gameFruit3);
			if (game->gameFruit4.fruitMode == Displaying_F) draw_fruit_game(game->currentLevel, &game->gameFruit4);
			if (game->gameFruit5.fruitMode == Displaying_F) draw_fruit_game(game->currentLevel, &game->gameFruit5);

			if (game->gameFruit1.eaten && ticks_game() - game->gameFruit1.eatenAt < 2000) draw_fruit_pts(&game->gameFruit1);
			if (game->gameFruit2.eaten && ticks_game() - game->gameFruit2.eatenAt < 2000) draw_fruit_pts(&game->gameFruit2);
			if (game->gameFruit3.eaten && ticks_game() - game->gameFruit3.eatenAt < 2000) draw_fruit_pts(&game->gameFruit3);
			if (game->gameFruit4.eaten && ticks_game() - game->gameFruit4.eatenAt < 2000) draw_fruit_pts(&game->gameFruit4);
			if (game->gameFruit5.eaten && ticks_game() - game->gameFruit5.eatenAt < 2000) draw_fruit_pts(&game->gameFruit5);

<<<<<<< HEAD
=======

>>>>>>> cf13d40c95e1630a99d34a658e66cf9b0cb324af
			if(game->pacman.livesLeft>=0){
				draw_pacman(&game->pacman);
			}
			if(game->multiMode && game->pacman2.livesLeft>=0){
				draw_pacman(&game->pacman2);
			}

<<<<<<< HEAD
			for(int i=0;i<2;i++)
			{
				if(game->item[i].itemMode==Displaying_I)
				{
					draw_item_game(&game->item[i]);
				}
			}

			if(game->bullet.bullet_displaying==true)
				draw_bullet(&game->bullet);
			if(game->multiMode && game->bullet2.bullet_displaying==true)
				draw_bullet(&game->bullet2);
=======

			if(game->bullet.bullet_displaying==true)
				draw_bullet(&game->bullet);

		
>>>>>>> cf13d40c95e1630a99d34a658e66cf9b0cb324af


			if(game->pacman.godMode == false)
			{
				for (int i = 0; i < 4; i++)
				{
					if(game->ghosts[i].isDead == 1)
					{
						draw_eyes(&game->ghosts[i]);
					} else
						draw_ghost(&game->ghosts[i]);
				}

			}
			else
			{
				if(godChange == false)
				{
					game->pacman.originDt = ticks_game();
					godChange = true;
				}
				godDt = ticks_game() - game->pacman.originDt;
				for (int i = 0; i < 4; i++)
				{
					if(game->ghosts[i].isDead == 1)
					{
						draw_eyes(&game->ghosts[i]);
					}
					else if(draw_scared_ghost(&game->ghosts[i], godDt))
					{
						// nothing
						if(game->ghosts[i].isDead == 2)
						{
							draw_ghost(&game->ghosts[i]);
						}
					}
					else
					{
						game->pacman.godMode = false;
						godChange = false;
						if(game->ghosts[i].isDead == 2)
							game->ghosts[i].isDead = 0;
					}
				}
			}
			break;
		case WinState:
			draw_pacman_static(&game->pacman);
			if(game->multiMode){
				draw_pacman_static(&game->pacman2);
			}

			if (dt < 2000)
			{
				for (int i = 0; i < 4; i++) draw_ghost(&game->ghosts[i]);
				draw_board(&game->board);
			}
			else
			{
				//stop rendering the pen, and do the flash animation
				draw_board_flash(&game->board);
			}

			break;
		case DeathState:
			//draw everything the same for 1ish second
			if (dt < 1000)
			{
				//draw everything normally

				//TODO: this actually draws the last frame pacman was on when he died
				draw_pacman_static(&game->pacman);

				for (int i = 0; i < 4; i++) draw_ghost(&game->ghosts[i]);
			}
			else
			{
				//draw the death animation
				//printf("%d\n", dt);
				draw_pacman_death(&game->pacman, dt - 1000);
			}

			draw_large_pellets(&game->pelletHolder, true);
			draw_board(&game->board);
			break;
		case GameoverState:
			draw_game_gameover();
			draw_board(&game->board);
			draw_credits(num_credits());
			break;
	}
}

static void enter_state(PacmanGame *game, GameState state)
{
	//process leaving a state
	switch (game->gameState)
	{
		case GameBeginState:
			game->pacman.livesLeft--;

			break;
		case WinState:
			game->currentLevel++;
			game->gameState = LevelBeginState;
			level_init(game);
			break;
		case DeathState:
			// Player died and is starting a new game, subtract a life
			if (state == LevelBeginState)
			{
				game->pacman.livesLeft--;
				pacdeath_init(game);
			}
			break;
		default: ; //do nothing
	}

	//process entering a state
	switch (state)
	{
		case GameBeginState:
			play_sound(LevelStartSound);

			break;
		case LevelBeginState:
			
			break;
		case GamePlayState:
			break;
		case WinState:

			break;
		case DeathState:
			break;
		case GameoverState:
			break;
	}

	game->ticksSinceModeChange = ticks_game();
	game->gameState = state;
}

//checks if it's valid that pacman could move in this direction at this point in time
bool can_move(Pacman *pacman, Board *board, Direction dir)
{
	//easy edge cases, tile has to be parallal with a direction to move it
	if ((dir == Up   || dir == Down ) && !on_vert(&pacman->body)) return false;
	if ((dir == Left || dir == Right) && !on_horo(&pacman->body)) return false;

	//if pacman wants to move on an axis and he is already partially on that axis (not 0)
	//it is always a valid move
	if ((dir == Left || dir == Right) && !on_vert(&pacman->body)) return true;
	if ((dir == Up   || dir == Down ) && !on_horo(&pacman->body)) return true;

	//pacman is at 0/0 and moving in the requested direction depends on if there is a valid tile there
	int x = 0;
	int y = 0;

	dir_xy(dir, &x, &y);

	int newX = pacman->body.x + x;
	int newY = pacman->body.y + y;

	return is_valid_square(board, newX, newY) || is_tele_square(newX, newY);
}

static void process_player(PacmanGame *game)
{
	Pacman *pacman = &game->pacman;
	Board *board = &game->board;

	if (pacman->missedFrames != 0)
	{
		pacman->missedFrames--;
		return;
	}

	Direction oldLastAttemptedDir = pacman->lastAttemptedMoveDirection;

	Direction newDir;

	bool dirPressed = dir_pressed_now(&newDir);

	if (dirPressed)
	{
		//user wants to move in a direction
		pacman->lastAttemptedMoveDirection = newDir;

		//if player holds opposite direction to current walking dir
		//we can always just switch current walking direction
		//since we're on parallel line
		if (newDir == dir_opposite(pacman->body.curDir))
		{
			pacman->body.curDir = newDir;
			pacman->body.nextDir = newDir;
		}

		//if pacman was stuck before just set his current direction as pressed
		if (pacman->movementType == Stuck)
		{
			pacman->body.curDir = newDir;
		}

		pacman->body.nextDir = newDir;
	}
	else if (pacman->movementType == Stuck)
	{
		//pacman is stuck and player didn't move - player should still be stuck.
		//don't do anything
		return;
	}
	else
	{
		//user doesn't want to change direction and pacman isn't stuck
		//pacman can move like normal

		//just set the next dir to current dir
		pacman->body.nextDir = pacman->body.curDir;
	}

	pacman->movementType = Unstuck;

	int curDirX = 0;
	int curDirY = 0;
	int nextDirX = 0;
	int nextDirY = 0;

	dir_xy(pacman->body.curDir, &curDirX, &curDirY);
	dir_xy(pacman->body.nextDir, &nextDirX, &nextDirY);

	int newCurX = pacman->body.x + curDirX;
	int newCurY = pacman->body.y + curDirY;
	int newNextX = pacman->body.x + nextDirX;
	int newNextY = pacman->body.y + nextDirY;

	bool canMoveCur =  is_valid_square(board, newCurX, newCurY) || is_tele_square(newCurX, newCurY);
	bool canMoveNext = is_valid_square(board, newNextX, newNextY) || is_tele_square(newNextX, newNextY);

	//if pacman is currently on a center tile and can't move in either direction
	//don't move him
	if (on_center(&pacman->body) && !canMoveCur && !canMoveNext)
	{
		pacman->movementType = Stuck;
		pacman->lastAttemptedMoveDirection = oldLastAttemptedDir;

		return;
	}

	move_pacman(&pacman->body, canMoveCur, canMoveNext);

	//if pacman is on the center, and he couldn't move either of  his last directions
	//he must be stuck now
	if (on_center(&pacman->body) && !canMoveCur && !canMoveNext)
	{
		pacman->movementType = Stuck;
		return;
	}

	resolve_telesquare(&pacman->body);
}

static void process_player2(PacmanGame *game)
{
	Pacman *pacman2 = &game->pacman2;
	Board *board = &game->board;

	if (pacman2->missedFrames != 0)
	{
		pacman2->missedFrames--;
		return;
	}

	Direction oldLastAttemptedDir2 = pacman2->lastAttemptedMoveDirection;

	Direction newDir2;

	bool dirPressed2 = dir_pressed_now2(&newDir2);
	if (dirPressed2)
	{
		//user wants to move in a direction
		pacman2->lastAttemptedMoveDirection = newDir2;

		//if player holds opposite direction to current walking dir
		//we can always just switch current walking direction
		//since we're on parallel line
		if (newDir2 == dir_opposite(pacman2->body.curDir))
		{
			pacman2->body.curDir = newDir2;
			pacman2->body.nextDir = newDir2;
		}

		//if pacman was stuck before just set his current direction as pressed
		if (pacman2->movementType == Stuck)
		{
			pacman2->body.curDir = newDir2;
		}

		pacman2->body.nextDir = newDir2;
	}
	else if (pacman2->movementType == Stuck)
	{
		//pacman is stuck and player didn't move - player should still be stuck.
		//don't do anything
		return;
	}
	else
	{
		//user doesn't want to change direction and pacman isn't stuck
		//pacman can move like normal

		//just set the next dir to current dir
		pacman2->body.nextDir = pacman2->body.curDir;
	}

	pacman2->movementType = Unstuck;

	int curDirX_ = 0;
	int curDirY_ = 0;
	int nextDirX_ = 0;
	int nextDirY_ = 0;

	dir_xy(pacman2->body.curDir, &curDirX_, &curDirY_);
	dir_xy(pacman2->body.nextDir, &nextDirX_, &nextDirY_);

	int newCurX_ = pacman2->body.x + curDirX_;
	int newCurY_ = pacman2->body.y + curDirY_;
	int newNextX_ = pacman2->body.x + nextDirX_;
	int newNextY_ = pacman2->body.y + nextDirY_;

	bool canMoveCur_ =  is_valid_square(board, newCurX_, newCurY_) || is_tele_square(newCurX_, newCurY_);
	bool canMoveNext_ = is_valid_square(board, newNextX_, newNextY_) || is_tele_square(newNextX_, newNextY_);

	//if pacman is currently on a center tile and can't move in either direction
	//don't move him
	if (on_center(&pacman2->body) && !canMoveCur_ && !canMoveNext_)
	{
		pacman2->movementType = Stuck;
		pacman2->lastAttemptedMoveDirection = oldLastAttemptedDir2;

		return;
	}

	move_pacman(&pacman2->body, canMoveCur_, canMoveNext_);

	//if pacman is on the center, and he couldn't move either of  his last directions
	//he must be stuck now
	if (on_center(&pacman2->body) && !canMoveCur_ && !canMoveNext_)
	{
		pacman2->movementType = Stuck;
		return;
	}

	resolve_telesquare(&pacman2->body);
}

static void process_ghosts(PacmanGame *game)
{
	for (int i = 0; i < 4; i++)
	{
		Ghost *g = &game->ghosts[i];

		if (g->movementMode == InPen)
		{
			//ghosts bob up and down - move in direction. If they hit a square, change direction
			bool moved = move_ghost(&g->body);

			if (moved && (g->body.y == 13 || g->body.y == 15))
			{
				g->body.nextDir = g->body.curDir;
				g->body.curDir = dir_opposite(g->body.curDir);
			}

			continue;
		}

		if (g->movementMode == LeavingPen)
		{
			//ghost is in center of tile
			//move em to the center of the pen (in x axis)
			//then more em up out the gate
			//when they are out of the gate, set them to be in normal chase mode then set them off on their way

			continue;
		}

		//all other modes can move normally (I think)
		MovementResult result = move_ghost(&g->body);
		resolve_telesquare(&g->body);

		if (result == NewSquare)
		{
			//if they are in a new tile, rerun their target update logic
			execute_ghost_logic(g, g->ghostType, &game->ghosts[0], &game->pacman);

			g->nextDirection = next_direction(g, &game->board);
		}
		else if (result == OverCenter)
		{
			//they've hit the center of a tile, so change their current direction to the new direction
			g->body.curDir = g->transDirection;
			g->body.nextDir = g->nextDirection;
			g->transDirection = g->nextDirection;
		}
	}
}

static void process_fruit(PacmanGame *game)
{
	int pelletsEaten = game->pelletHolder.totalNum - game->pelletHolder.numLeft;

	GameFruit *f1 = &game->gameFruit1;
	GameFruit *f2 = &game->gameFruit2;
	GameFruit *f3 = &game->gameFruit3;
	GameFruit *f4 = &game->gameFruit4;
	GameFruit *f5 = &game->gameFruit5;

	int curLvl = game->currentLevel;

	if (pelletsEaten >= 30 && f1->fruitMode == NotDisplaying_F)
	{
		f1->fruitMode = Displaying_F;
		regen_fruit(f1, curLvl);
	}
	else if (pelletsEaten == 60 && f2->fruitMode == NotDisplaying_F)
	{
		f2->fruitMode = Displaying_F;
		regen_fruit(f2, curLvl);
	}
	else if (pelletsEaten == 90 && f3->fruitMode == NotDisplaying_F)
	{
		f3->fruitMode = Displaying_F;
		regen_fruit(f3, curLvl);
	}
	else if (pelletsEaten == 120 && f4->fruitMode == NotDisplaying_F)
	{
		f4->fruitMode = Displaying_F;
		regen_fruit(f4, curLvl);
	}
	else if (pelletsEaten == 150 && f5->fruitMode == NotDisplaying_F)
	{
		f5->fruitMode = Displaying_F;
		regen_fruit(f5, curLvl);
	}

	unsigned int f1dt = ticks_game() - f1->startedAt;
	unsigned int f2dt = ticks_game() - f2->startedAt;
	unsigned int f3dt = ticks_game() - f3->startedAt;
	unsigned int f4dt = ticks_game() - f4->startedAt;
	unsigned int f5dt = ticks_game() - f5->startedAt;

	Pacman *pac = &game->pacman;

	if (f1->fruitMode == Displaying_F)
	{
		if (f1dt > f1->displayTime) f1->fruitMode = Displayed_F;
	}
	if (f2->fruitMode == Displaying_F)
	{
		if (f2dt > f2->displayTime) f2->fruitMode = Displayed_F;
<<<<<<< HEAD
	}
	if (f3->fruitMode == Displaying_F)
	{
		if (f3dt > f3->displayTime) f3->fruitMode = Displayed_F;
	}
	if (f4->fruitMode == Displaying_F)
	{
		if (f4dt > f4->displayTime) f4->fruitMode = Displayed_F;
	}
	if (f5->fruitMode == Displaying_F)
	{
		if (f5dt > f5->displayTime) f5->fruitMode = Displayed_F;
	}
=======
	}
	if (f3->fruitMode == Displaying_F)
		{
			if (f3dt > f3->displayTime) f3->fruitMode = Displayed_F;
		}
	if (f4->fruitMode == Displaying_F)
		{
			if (f4dt > f4->displayTime) f4->fruitMode = Displayed_F;
		}
	if (f5->fruitMode == Displaying_F)
		{
			if (f5dt > f5->displayTime) f5->fruitMode = Displayed_F;
		}
>>>>>>> cf13d40c95e1630a99d34a658e66cf9b0cb324af

	//check for collisions

	if (f1->fruitMode == Displaying_F && collides_obj(&pac->body, f1->x, f1->y))
	{
		f1->fruitMode = Displayed_F;
		f1->eaten = true;
		f1->eatenAt = ticks_game();
		pac->score += fruit_points(f1->fruit);
	}

	if (f2->fruitMode == Displaying_F && collides_obj(&pac->body, f2->x, f2->y))
	{
		f2->fruitMode = Displayed_F;
		f2->eaten = true;
		f2->eatenAt = ticks_game();
		pac->score += fruit_points(f2->fruit);
	}
	if (f3->fruitMode == Displaying_F && collides_obj(&pac->body, f3->x, f3->y))
	{
		f3->fruitMode = Displayed_F;
		f3->eaten = true;
		f3->eatenAt = ticks_game();
		pac->score += fruit_points(f3->fruit);
	}
	if (f4->fruitMode == Displaying_F && collides_obj(&pac->body, f4->x, f4->y))
	{
		f4->fruitMode = Displayed_F;
		f4->eaten = true;
		f4->eatenAt = ticks_game();
		pac->score += fruit_points(f4->fruit);
	}
	if (f5->fruitMode == Displaying_F && collides_obj(&pac->body, f5->x, f5->y))
	{
		f5->fruitMode = Displayed_F;
		f5->eaten = true;
		f5->eatenAt = ticks_game();
		pac->score += fruit_points(f5->fruit);
	}


	if(game->multiMode){
		Pacman *pac2 = &game->pacman2;

		if (f1->fruitMode == Displaying_F && collides_obj(&pac2->body, f1->x, f1->y))
		{
			f1->fruitMode = Displayed_F;
			f1->eaten = true;
			f1->eatenAt = ticks_game();
			pac->score += fruit_points(f1->fruit);
		}

		if (f2->fruitMode == Displaying_F && collides_obj(&pac2->body, f2->x, f2->y))
		{
			f2->fruitMode = Displayed_F;
			f2->eaten = true;
			f2->eatenAt = ticks_game();
			pac->score += fruit_points(f2->fruit);
		}
		if (f3->fruitMode == Displaying_F && collides_obj(&pac2->body, f3->x, f3->y))
		{
			f3->fruitMode = Displayed_F;
			f3->eaten = true;
			f3->eatenAt = ticks_game();
			pac->score += fruit_points(f3->fruit);
		}
		if (f4->fruitMode == Displaying_F && collides_obj(&pac2->body, f4->x, f4->y))
		{
			f4->fruitMode = Displayed_F;
			f4->eaten = true;
			f4->eatenAt = ticks_game();
			pac->score += fruit_points(f4->fruit);
		}
		if (f5->fruitMode == Displaying_F && collides_obj(&pac2->body, f5->x, f5->y))
		{
			f5->fruitMode = Displayed_F;
			f5->eaten = true;
			f5->eatenAt = ticks_game();
			pac->score += fruit_points(f5->fruit);
		}

	}
}

static void process_item(PacmanGame *game)
{
	for(int i=0;i<2;i++)
	{
		GameItem *item = &game->item[i];

		if (item->itemMode == NotDisplaying_I)
		{
			item->itemMode = Displaying_I;
			regen_item(item, item->item);
		}

		unsigned int itemdt = ticks_game() - item->startedAt;

		Pacman *pac = &game->pacman;
<<<<<<< HEAD
		Pacman *pac2 = &game->pacman2;
=======
>>>>>>> cf13d40c95e1630a99d34a658e66cf9b0cb324af

		if (item->itemMode == Displaying_I)
		{
			if (itemdt > item->displayTime)
				item->itemMode = Displayed_I;
		}

		//check for collisions

		//Bullet
<<<<<<< HEAD

		switch(game->multiMode){
		case 1:
			if (i==0&&item->itemMode == Displaying_I && collides_obj(&pac2->body, item->x, item->y))
			{
				item->itemMode = Displayed_I;
				item->eaten = true;
				item->eatenAt = ticks_game();

				pac2->bulletOn=true;
				pac2->bulletsLeft=5;
			}

			if(i==0&&game->pacman2.bulletsLeft==0&&game->bullet2.bullet_displaying==false)
			{
				pac2->bulletOn=false;
			}

			if (i==1&&item->itemMode == Displaying_I && collides_obj(&pac2->body, item->x, item->y))
			{
				item->itemMode = Displayed_I;
				item->eaten = true;
				item->eatenAt = ticks_game();

				LowVelocity_item(game);
			}

			if(i==1&&(ticks_game()-item->eatenAt)>5000)
			{
				for(int j=0;j<4;j++)
				{
					game->ghosts[j].body.velocity=80;
				}
			}
			//일부로 break 제외, 멀티모드의 경우 위 아래 케이스 모두 적용되도록 하기 위함
		case 0:
			if (i==0&&item->itemMode == Displaying_I && collides_obj(&pac->body, item->x, item->y))
			{
				item->itemMode = Displayed_I;
				item->eaten = true;
				item->eatenAt = ticks_game();

				game->pacman.bulletOn=true;
				game->pacman.bulletsLeft=5;
			}

			if(i==0&&game->pacman.bulletsLeft==0&&game->bullet.bullet_displaying==false)
			{
				game->pacman.bulletOn=false;
			}

			if (i==1&&item->itemMode == Displaying_I && collides_obj(&pac->body, item->x, item->y))
			{
				item->itemMode = Displayed_I;
				item->eaten = true;
				item->eatenAt = ticks_game();

				LowVelocity_item(game);
			}

			if(i==1&&(ticks_game()-item->eatenAt)>5000)
			{
				for(int j=0;j<4;j++)
				{
					game->ghosts[j].body.velocity=80;
				}
			}


		}

		/*if (i==0&&item->itemMode == Displaying_I && collides_obj(&pac->body, item->x, item->y))
=======
		if (i==0&&item->itemMode == Displaying_I && collides_obj(&pac->body, item->x, item->y))
>>>>>>> cf13d40c95e1630a99d34a658e66cf9b0cb324af
		{
			item->itemMode = Displayed_I;
			item->eaten = true;
			item->eatenAt = ticks_game();

			game->pacman.bulletOn=true;
			game->pacman.bulletsLeft=5;
		}

		if(i==0&&game->pacman.bulletsLeft==0&&game->bullet.bullet_displaying==false)
<<<<<<< HEAD
=======

	

>>>>>>> cf13d40c95e1630a99d34a658e66cf9b0cb324af
		{
			game->pacman.bulletOn=false;
		}

		//LowVelocity
		if (i==1&&item->itemMode == Displaying_I && collides_obj(&pac->body, item->x, item->y))
		{
			item->itemMode = Displayed_I;
			item->eaten = true;
			item->eatenAt = ticks_game();

			LowVelocity_item(game);
		}
<<<<<<< HEAD

=======
>>>>>>> cf13d40c95e1630a99d34a658e66cf9b0cb324af
		if(i==1&&(ticks_game()-item->eatenAt)>5000)
		{
			for(int j=0;j<4;j++)
			{
				game->ghosts[j].body.velocity=80;
			}
<<<<<<< HEAD
		}*/
=======
		}
>>>>>>> cf13d40c95e1630a99d34a658e66cf9b0cb324af
	}
}
static void process_pellets(PacmanGame *game)
{
	int j = 0;
	//if pacman and pellet collide
	//give pacman that many points
	//set pellet to not be active
	//decrease num of alive pellets
	PelletHolder *holder = &game->pelletHolder;

	for (int i = 0; i < holder->totalNum; i++)
	{
		Pellet *p = &holder->pellets[i];

		//skip if we've eaten this one already
		if (p->eaten) continue;

		if (collides_obj(&game->pacman.body, p->x, p->y))
		{
			holder->numLeft--;

			p->eaten = true;
			game->pacman.score += pellet_points(p);
			if(pellet_check(p))
			{
				game->pacman.godMode = true;
				game->pacman.originDt = ticks_game();
				for(j = 0; j< 4; j++)
				{
					if(game->ghosts[j].isDead == 2)
						game->ghosts[j].isDead = 0;
				}
			}


			//TODO play eat sound

			//eating a small pellet makes pacman not move for 1 frame
			//eating a large pellet makes pacman not move for 3 frames
			game->pacman.missedFrames = pellet_nop_frames(p);

			//can only ever eat 1 pellet in a frame, so return
			return;
		}
	}

	//maybe next time, poor pacman
}

static void process_pellets2(PacmanGame *game)
{
	int j = 0;

	PelletHolder *holder = &game->pelletHolder;

	for (int i = 0; i < holder->totalNum; i++)
	{
		Pellet *p = &holder->pellets[i];

		//skip if we've eaten this one already
		if (p->eaten) continue;

		if (collides_obj(&game->pacman2.body, p->x, p->y))
		{
			holder->numLeft--;

			p->eaten = true;
			game->pacman2.score += pellet_points(p);
			if(pellet_check(p)) {
				game->pacman2.godMode = true;
				game->pacman2.originDt = ticks_game();
				for(j = 0; j< 4; j++) {
					if(game->ghosts[j].isDead == 2)
						game->ghosts[j].isDead = 0;
				}
			}

			//play eat sound

			game->pacman2.missedFrames = pellet_nop_frames(p);

			return;
		}
	}

}

static bool check_pacghost_collision(PacmanGame *game, Pacman *pacman)
{
	for (int i = 0; i < 4; i++)
	{
		Ghost *g = &game->ghosts[i];



		if (collides(&pacman->body, &g->body)) {
			if(pacman->godMode == false)
				return true;
			else {
				if(g->isDead == 2) {return true;}
				g->isDead = 1;
				death_send(g);
			}
		}
	}

	return false;
}

<<<<<<< HEAD
=======
/*static bool check_pacghost_collision(PacmanGame *game)
{
	for (int i = 0; i < 4; i++)
	{
		Ghost *g = &game->ghosts[i];

		//switch(g->ghostType) {
		//case Blinky : printf("red : %d \n", g->isDead); break;
		//case Inky: printf("blue : %d \n", g->isDead); break;
		//case Clyde: printf("orange : %d \n", g->isDead); break;
		//case Pinky: printf("pink : %d \n", g->isDead); break;
		//}


		if (collides(&game->pacman.body, &g->body)) {

			if(game->pacman.godMode == false)
				return true;
			else
			{
				if(g->isDead == 2)
				{
					return true;
				}
				g->isDead = 1;
				death_send(g);
			}

		}
	}

	return false;
}*/

>>>>>>> cf13d40c95e1630a99d34a658e66cf9b0cb324af
void gamestart_init(PacmanGame *game)
{
	level_init(game);

	if(!game->multiMode)
		pacman_init(&game->pacman);
	else
		pacman_init_multiMode(&game->pacman, &game->pacman2);
	//we need to reset all fruit
	//fuit_init();
	game->highscore = 0; //TODO maybe load this in from a file..?
	game->currentLevel = 1;

	//invalidate the state so it doesn't effect the enter_state function
	game->gameState = -1;
	enter_state(game, GameBeginState);
}

void level_init(PacmanGame *game)
{
	//reset pacmans position
	if(!game->multiMode){
		pacman_level_init(&game->pacman);
	}
	else
	{
		pacman_level_init_multimode(&game->pacman, &game->pacman2);
	}

	//reset pellets
	pellets_init(&game->pelletHolder);

	//reset ghosts
	ghosts_init(game->ghosts);

	//reset fruit
	reset_fruit(&game->gameFruit1, &game->board);
	reset_fruit(&game->gameFruit2, &game->board);
	reset_fruit(&game->gameFruit3, &game->board);
	reset_fruit(&game->gameFruit4, &game->board);
	reset_fruit(&game->gameFruit5, &game->board);

	//reset item
	item_init(game->item,&game->board);

}

void pacdeath_init(PacmanGame *game)
{
	if(!game->multiMode){
		pacman_level_init(&game->pacman);
	}
	else
	{
		pacman_level_init_multimode(&game->pacman, &game->pacman2);
	}
	ghosts_init(game->ghosts);

	reset_fruit(&game->gameFruit1, &game->board);
	reset_fruit(&game->gameFruit2, &game->board);
	reset_fruit(&game->gameFruit3, &game->board);
	reset_fruit(&game->gameFruit4, &game->board);
	reset_fruit(&game->gameFruit5, &game->board);


	item_init(game->item,&game->board);

}
/*
void pacdeath_init_multi_Player1(PacmanGame *game)
{
	if(!game->multiMode){
		pacman_level_init(&game->pacman);
	}
	else
	{
		pacman_level_init_multimode(&game->pacman, &game->pacman2);
	}
}

void pacdeath_init_multi_Player2(PacmanGame *game)
{
	if(!game->multiMode){
		pacman_level_init(&game->pacman);
	}
	else
	{
		pacman_level_init_multimode(&game->pacman, &game->pacman2);
	}
}
*/
//TODO: make this method based on a state, not a conditional
//or make the menu system the same. Just make it consistant
bool is_game_over(PacmanGame *game)
{
	unsigned dt = ticks_game() - game->ticksSinceModeChange;

	return dt > 2000 && game->gameState == GameoverState;
}

int int_length(int x)
{
    if (x >= 1000000000) return 10;
    if (x >= 100000000)  return 9;
    if (x >= 10000000)   return 8;
    if (x >= 1000000)    return 7;
    if (x >= 100000)     return 6;
    if (x >= 10000)      return 5;
    if (x >= 1000)       return 4;
    if (x >= 100)        return 3;
    if (x >= 10)         return 2;
    return 1;
}

static bool resolve_telesquare(PhysicsBody *body)
{
	//TODO: chuck this back in the board class somehow

	if (body->y != 14) return false;

	if (body->x == -1) { body->x = 27; return true; }
	if (body->x == 28) { body->x =  0; return true; }

	return false;
}


<<<<<<< HEAD
void process_bullet(PacmanGame *game,Pacman *pacman, Item_bullet *bullet)
{
	MovementResult result = move_bullet(&bullet->body);

	if (result == NewSquare)
	{
		bullet->body.nextDir = bullet->body.curDir;
	}
	else if (result == OverCenter)
	{
		bullet->body.nextDir = bullet->body.curDir;
	}

	for(int i=0;i<4;i++)
	{
		if (bullet->bullet_displaying == true && collides(&game->ghosts[i].body, &bullet->body))
		{
			if(game->ghosts[i].isDead!=1)
			{
				bullet->bullet_displaying=false;
=======
void process_bullet(PacmanGame* game)
{
	MovementResult result = move_bullet(&game->bullet.body);

	if (result == NewSquare)
	{
		game->bullet.body.nextDir = game->bullet.body.curDir;
	}
	else if (result == OverCenter)
	{
		game->bullet.body.nextDir = game->bullet.body.curDir;
	}


	for(int i=0;i<4;i++)
	{
		if (game->bullet.bullet_displaying == true && collides(&game->ghosts[i].body,&game->bullet.body))
		{
			if(game->ghosts[i].isDead!=1)
			{
				game->bullet.bullet_displaying=false;
>>>>>>> cf13d40c95e1630a99d34a658e66cf9b0cb324af
				game->ghosts[i].isDead = 1;
			}
		}
	}
<<<<<<< HEAD
	if(!is_valid_square(&game->board, bullet->body.x, bullet->body.y))
	{
		bullet->bullet_displaying=false;
=======
	if(!is_valid_square(&game->board,game->bullet.body.x,game->bullet.body.y))
	{
		game->bullet.bullet_displaying=false;
>>>>>>> cf13d40c95e1630a99d34a658e66cf9b0cb324af
	}


}

<<<<<<< HEAD
void bullet_effect_eliminate(Pacman *pac){
	pac->bulletOn = false;
	pac->bulletsLeft = 0;
}

void bullet_init(Item_bullet* bullet, Pacman* pac)
{
	bullet->body = pac->body;
=======
void bullet_init(Item_bullet* bullet,PacmanGame* game)
{
	bullet->body =game->pacman.body;

>>>>>>> cf13d40c95e1630a99d34a658e66cf9b0cb324af
	bullet->body.velocity = 200;
	bullet->bullet_displaying=true;
}

<<<<<<< HEAD
=======


}



>>>>>>> cf13d40c95e1630a99d34a658e66cf9b0cb324af
void LowVelocity_item(PacmanGame *game)
{
	for(int i=0;i<4;i++)
	{
		game->ghosts[i].body.velocity=40;
	}
}
