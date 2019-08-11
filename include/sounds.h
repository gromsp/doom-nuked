#ifndef SOUNDS_H
# define SOUNDS_H

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

typedef struct s_music
{
	Mix_Music	*mus1;
	Mix_Music	*mus2;
	Mix_Music	*mus3;
	Mix_Music	*mus4;
	Mix_Music	*mus5;
}				t_music;

typedef struct	s_snd
{
	t_music		*music;
}				t_snd;

typedef struct	s_main
{
	t_snd		*snd;
}				t_main;

 

#endif