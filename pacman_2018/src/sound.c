#include "sound.h"

#include <SDL/SDL_mixer.h>

//sound filenames
//static const char *EFFECT_FILES[] = {"wakawaka.wav", "bdc"};
//static const char MUSIC_FILE[] = "Music.wav";

static float volume;
static bool muted;

static Mix_Music *music;
//static Mix_Chunk *effects[NUM_EFFECTS];

static Mix_Chunk *levelStart;
static Mix_Chunk *bullet;
static Mix_Chunk *death;
static Mix_Chunk *eatingFruit;
static Mix_Chunk *eatingPellet;
static Mix_Chunk *GodMode;
static Mix_Chunk *lose;
static Mix_Chunk *speedDown;
static Mix_Chunk *win;

static int levelStartChanel;
static int bulletChanel;
static int deathChanel;
static int eatingFruitChanel;
static int eatingPelletChanel;
static int GodModeChanel;
static int loseChanel;
static int speedDownChanel;
static int winChanel;

void load_sounds(void)
{
	//22050 is sound frequency
	//MIX_DEFAULT_FORMAT is the sound format
	//2 is number of channels to use, we use 2 for stereo sound
	//4096 is the sample size
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		printf("Error creating sound effects.\n");
		printf("Aborting.\n");
		exit(1);
	}

	//now load the sounds and effects we're using
	//music = Mix_LoadMUS(MUSIC_FILE);

	//for (int i = 0; i < NUM_EFFECTS; i++)
	//{
		//effects[i] = Mix_LoadWAV(EFFECT_FILES[i]);
	//}

	levelStart = Mix_LoadWAV("sound/Level_Start.wav");
	bullet=Mix_LoadWAV("sound/Bullet.wav");
	death=Mix_LoadWAV("sound/Death.wav");
	eatingFruit=Mix_LoadWAV("sound/Eating_Fruit.wav");
	eatingPellet=Mix_LoadWAV("sound/Eating_Pellet.wav");
	GodMode=Mix_LoadWAV("sound/God_Mode.wav");
	lose=Mix_LoadWAV("sound/Lose.wav");
	speedDown=Mix_LoadWAV("sound/SpeedDown.wav");
	win=Mix_LoadWAV("sound/Win.wav");


	set_sound_volume(0.5);
	set_sound_muted(false);
}

void dispose_sounds(void)
{
	//for (int i = 0; i < NUM_EFFECTS; i++)
	//{
		//Mix_FreeChunk(effects[i]);
	//}

	Mix_FreeChunk(levelStart);

	Mix_FreeMusic(music);
}

void set_sound_volume(float vol)
{
	Mix_VolumeChunk(levelStart, vol * MIX_MAX_VOLUME);
	volume = vol;
}

float get_sound_volume(void)
{
	return volume;
}

void set_sound_muted(bool isMuted)
{
	if (isMuted)
	{
		Mix_VolumeChunk(levelStart, 0);
	}
	else
	{
		set_sound_volume(volume);
	}

	muted = isMuted;
}

bool is_sound_muted(void)
{
	return muted;
}

void play_sound(SoundEffect effectName)
{
	Mix_Chunk *chunk;
	int *channel;

	switch (effectName)
	{
		case LevelStartSound:
			chunk = levelStart;
			channel = &levelStartChanel;
			break;
		case BulletSound:
			chunk=bullet;
			channel=&bulletChanel;
			break;
		case DeathSound:
			chunk=death;
			channel=&deathChanel;
			break;
		case EatingFruitSound:
			chunk=eatingFruit;
			channel=&eatingFruitChanel;
			break;
		case EatingPelletSound:
			chunk=eatingPellet;
			channel=&eatingPelletChanel;
			break;
		case GodModeSound:
			chunk=GodMode;
			channel=&GodModeChanel;
			break;
		case LoseSound:
			chunk=lose;
			channel=&loseChanel;
			break;
		case SpeedDownSound:
			chunk=speedDown;
			channel=&speedDownChanel;
			break;
		case WinSound:
			chunk=win;
			channel=&winChanel;
			break;
	}

	*channel = Mix_PlayChannel(-1, chunk, 0);
}

void play_music(void)
{

}

void stop_sound(SoundEffect effectName)
{
	int channel;

	switch (effectName)
	{
		case LevelStartSound:  channel = levelStartChanel; break;
		default: printf("badsound\naborting\n"); exit(1); //TODO: fix this up
	}

	Mix_HaltChannel(channel);
}

void stop_music(void)
{

}
