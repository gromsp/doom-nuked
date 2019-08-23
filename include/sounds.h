#ifndef SOUNDS_H
# define SOUNDS_H

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

typedef struct		s_plr
{
	double			x;
	double			y;
}					t_plr;

typedef struct		s_obj_specs
{
	double			x;
	double			y;
}					t_obj_specs;

typedef	struct		s_obj
{
	t_obj_specs		*specs;
	double			dist;
	int 			chan;
	Mix_Chunk		*chunk;
	struct s_obj	*next;
	struct s_obj	*prev;
}					t_obj;

typedef struct s_music
{
	Mix_Music	*mus1;
	Mix_Music	*mus2;
	Mix_Music	*mus3;
	Mix_Music	*mus4;
	Mix_Music	*mus5;
	int			nummus;
}				t_music;

typedef struct s_bup
{
	Mix_Chunk	*fire;
}				t_bup;

typedef struct	s_snd
{
	t_music		*music;
	t_bup		*chunks;
}				t_snd;

typedef struct	s_main
{
	t_snd		*snd;
	t_obj		*obj;
	t_plr		*plr;
}				t_main;

 

#endif