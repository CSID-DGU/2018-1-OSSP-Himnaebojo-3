#include "main.h"

#include <stdbool.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "board.h"
#include "boardloader.h"
#include "fps.h"
#include "game.h"
#include "input.h"
#include "item.h"
#include "intermission.h"
#include "imageloader.h"
#include "menu.h"
#include "sound.h"
#include "text.h"
#include "window.h"

//Initializes all resources.
static void resource_init(void);

//Initialize all the internal entities needed for the game at startup.
static void game_init(void);

//Called when a game is about to begin (player hits enter from main menu).
static void startgame_init(void);

//Frees all resources.
static void clean_up(void);

//Performs a loop, updating and rendering at 60hz.
static void main_loop(void);

//Defers to appropriate tick, based on current state.
static void internal_tick(void);

//Defers to appropriate render, based on current state.
static void internal_render(void);

//Processess and deals with all SDL events.
static void process_events(void);

//Performs specific actions on various keypresses. Used for testing.
static void key_down_hacks(int keycode);

static ProgramState state;
static ModeState mode;
static MenuSystem menuSystem;
static PacmanGame pacmanGame;

static bool gameRunning = true;
static int numCredits = 0;

int main(void)
{
	resource_init();
	game_init();

	main_loop();

	clean_up();

	return 0;
}

static void main_loop(void)
{
	while (gameRunning && !key_held(SDLK_ESCAPE))
	{
		process_events();

		internal_tick();
		internal_render();

		fps_sleep();
	}
}

static void internal_tick(void)
{
	switch (state)
	{
		case Menu:
			menu_tick(&menuSystem);
//playmode별 실행 분기
			if (menuSystem.action == GoToGame && mode==Single)
			{
				numCredits--;
				pacmanGame.multiMode=0;
				state = Game;
				startgame_init();
			}
			else if (menuSystem.action == GoToGame && mode==Pvp)
			{
				numCredits--;
				pacmanGame.multiMode=1;
				pacmanGame.pveMode=0;
				state = Game;
				startgame_init();
			}
			else if (menuSystem.action == GoToGame && mode==Pve)
			{
				numCredits--;
				pacmanGame.multiMode=1;
				pacmanGame.pveMode=1;
				state = Game;
				startgame_init();
			}

			break;
		case Game:
			game_tick(&pacmanGame);

			if (is_game_over(&pacmanGame))
			{
				menu_init(&menuSystem);
				state = Menu;
			}

			break;
		case Intermission:
			intermission_tick();
			break;
	}
}

static void internal_render(void)
{
	clear_screen(0, 0, 0, 0);

	switch (state)
	{
		case Menu:
			menu_render(&menuSystem, &mode);
			break;
		case Game:
			game_render(&pacmanGame);
			break;
		case Intermission:
			intermission_render();
			break;
	}

	flip_screen();
}

static void game_init(void)
{
	//Load the board here. We only need to do it once
	load_board(&pacmanGame.board, &pacmanGame.pelletHolder, "maps/encodedboard");

	//set to be in menu
	state = Menu;

	//최초 실행 시 Single 모드로 설정
	mode = Single;

	//init the framerate manager
	fps_init(60);

	menu_init(&menuSystem);
}

static void startgame_init(void)
{
	gamestart_init(&pacmanGame);
}

static void resource_init(void)
{
	init_window(SCREEN_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
	load_images();
	load_sounds();
	load_text();

	//TODO: ensure all the resources loaded properly with some nice function calls
}

static void clean_up(void)
{
	dispose_window();
	dispose_images();
	dispose_sounds();
	dispose_text();

	SDL_Quit();
}

static void process_events(void)
{
	static SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				gameRunning = false;

				break;
			case SDL_KEYDOWN:
				handle_keydown(event.key.keysym.sym);
				key_down_hacks(event.key.keysym.sym);

				break;
			case SDL_KEYUP:
				handle_keyup(event.key.keysym.sym);

				break;
		}
	}

	keyevents_finished();
}

static void key_down_hacks(int keycode)
{
	if (keycode == SDLK_RETURN) pacmanGame.currentLevel++;
	if (keycode == SDLK_BACKSPACE) menuSystem.ticksSinceModeChange = SDL_GetTicks();

	static bool rateSwitch = false;

	//TODO: remove this hack and try make it work with the physics body
	if (keycode == SDLK_SPACE) fps_sethz((rateSwitch!=rateSwitch) ? 200 : 60);

	if (keycode == SDLK_b)
	{
		if(!pacmanGame.pacman.boostOn)
		{
			pacmanGame.pacman.body.velocity = 100;
			pacmanGame.pacman.boostOn = true;
		}
		else
		{
			pacmanGame.pacman.body.velocity = 80;
			pacmanGame.pacman.boostOn = false;
		}
	}

	if(pacmanGame.pacman.bulletOn==true&&pacmanGame.bullet.bullet_displaying==false&&keycode==SDLK_SLASH)//bullet모드일 경우 '/' 누르면 총알 발사
	{
		pacmanGame.pacman.bulletsLeft--;
		bullet_init(&pacmanGame.bullet, &pacmanGame.pacman);
		play_sound(BulletSound);
	}

	if(pacmanGame.pacman2.bulletOn==true&&pacmanGame.bullet2.bullet_displaying==false&&keycode==SDLK_f)
	{
		pacmanGame.pacman2.bulletsLeft--;
		bullet_init(&pacmanGame.bullet2, &pacmanGame.pacman2);
		play_sound(BulletSound);
	}

	//TODO: move logic into the tick method of the menu
	if (state == Menu && keycode == SDLK_5 && numCredits < 99)
	{
		play_sound(EatingPelletSound);
		numCredits++;
	}
    //키보드 입력에 따라 플레이 모드 바꾸기
	if (state == Menu && numCredits!=0 && keycode == SDLK_DOWN && mode<2)
	{
		play_sound(GodModeSound);
		mode++;
	}

	if (state == Menu && numCredits!=0 && keycode == SDLK_UP && mode>0)
	{
		play_sound(GodModeSound);
		mode--;
	}

	if (keycode == SDLK_9)
	{
		printf("plus\n");
		for (int i = 0; i < 4; i++) pacmanGame.ghosts[i].body.velocity += 5;

		printf("ghost speed: %d\n", pacmanGame.ghosts[0].body.velocity);
	}
	else if (keycode == SDLK_0)
	{
		printf("minus\n");
		for (int i = 0; i < 4; i++) pacmanGame.ghosts[i].body.velocity -= 5;

		printf("ghost speed: %d\n", pacmanGame.ghosts[0].body.velocity);
	}
}

int num_credits(void)
{
	return numCredits;
}
