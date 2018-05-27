#pragma once

//28 across, 36 down, 16 pixels each square.
#define SCREEN_TITLE "2018-1-OSSP-Himnaebojo-3-Pacman"
#define SCREEN_WIDTH 448
#define SCREEN_HEIGHT 576

//Defines the main states the program can be in.
typedef enum
{
	Menu,
	Game,
	Intermission
} ProgramState;

//현재 플레이 모드를 정의
typedef enum
{
	Single,
	Pvp,
	Pve
} ModeState;

//Returns the number of credits the user currently has.
int num_credits(void);
