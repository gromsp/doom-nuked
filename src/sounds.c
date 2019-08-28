/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoyle <adoyle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 18:58:36 by adoyle            #+#    #+#             */
/*   Updated: 2019/08/08 19:24:20 by adoyle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sounds.h"

/* gcc sounds.c -g -L /Users/adoyle/homebrew/lib -lSDL2-2.0.0 -I /Users/adoyle/homebrew/include -L /Users/adoyle/homebrew/lib -lSDL2_mixer-2.0.0  */

void	initsdl(t_main *mlx)
{
	SDL_Window *window;
	t_snd *snd;
	snd = malloc(sizeof(t_snd));
	snd->music = malloc(sizeof(t_music));
	snd->chunks = malloc(sizeof(t_bup));
	mlx->snd = snd;
//	if (SDL_Init(SDL_INIT_AUDIO) < 0)
//		return ;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return ;
	window = SDL_CreateWindow("Hello, SDL 2!",SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED, 640, 640,
							  SDL_WINDOW_SHOWN);
	if (Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1) 
		return ;
	snd->music->mus1 = Mix_LoadMUS( "/sound/blade1.ogg"); //объединить все дорожки музщыки в одну для оптимизации
	snd->music->mus1 = Mix_LoadMUS( "D:\\Coding\\doom-nuked\\sound\\blade2.ogg");
	snd->music->mus2 = Mix_LoadMUS( "D:\\Coding\\doom-nuked\\sound\\blade4.ogg");
	// snd->music->mus2 = Mix_LoadMUS( "/sound/blade2.ogg");
	// snd->music->mus3 = Mix_LoadMUS( "/sound/blade3.ogg");
	// snd->music->mus4 = Mix_LoadMUS( "/sound/blade4.ogg");
	// snd->music->mus5 = Mix_LoadMUS( "/sound/blade5.ogg");
	mlx->snd->music->nummus = 1;
	mlx->snd->chunks->fire = Mix_LoadWAV("D:\\Coding\\doom-nuked\\sound\\fire_zkyuzme_.wav");
	if (!(snd->music->mus1) || !(snd->music->mus2) || !(snd->music->mus3) || !(snd->music->mus4) || !(snd->music->mus5))
		return ;
	Mix_AllocateChannels (16);
}

void	playmusic(t_music *music)
{
	if (Mix_PlayingMusic() == 0)
	{
		if (music->nummus == 1)
		{
			music->nummus = 2;
			Mix_PlayMusic(music->mus1, 0);
		}
		else if (music->nummus == 2)
		{
			music->nummus = 1;
			Mix_PlayMusic(music->mus1, 0);
		}
//		if (Mix_PlayMusic(music->mus3, 0) == -1)
//			return;
//		while (Mix_PlayingMusic());
//		if (Mix_PlayMusic(music->mus4, 0) == -1)
//			return;
//		while (Mix_PlayingMusic());
//		if (Mix_PlayMusic(music->mus5, 0) == -1)
//			return;
//		while (Mix_PlayingMusic());
	}
}

void	closesdl(t_snd *snd)
{
	Mix_FreeMusic(snd->music->mus1);
	Mix_FreeMusic(snd->music->mus2);
	// Mix_FreeMusic(snd->music->mus3);
	// Mix_FreeMusic(snd->music->mus4);
	// Mix_FreeMusic(snd->music->mus5);
	Mix_CloseAudio();
    SDL_Quit();	
}

void 	sound_eff(t_main *mlx)
{
	t_bup *bup;
	t_plr *plr;
	t_obj *tmp;
	int rast;
	int i;

	bup = mlx->snd->chunks;
	plr = mlx->plr;
	tmp = mlx->obj;
	while (mlx->obj->next)
	{
		rast = mlx->obj->dist - plr->x;
		if (rast < 0)
			rast = rast * (-1);
		if (rast <= 10)
		{
			if (mlx->obj->chan == -1)
				mlx->obj->chan = Mix_PlayChannel(-1, bup->fire, -1);
			else
			{
				if (rast <= 0)
					rast = 1;
				Mix_Volume(mlx->obj->chan, 128 / rast);
			}
		}
		else if (mlx->obj->chan >= 0)
		{
			Mix_HaltChannel(mlx->obj->chan);
			mlx->obj->chan = -1;
		}
		mlx->obj = mlx->obj->next;
	}
	mlx->obj = tmp;
}

void	eventsmusic(t_main *mlx)
{
	SDL_Event e;
	int quit;

	quit = 0;
	while( quit == 0 )
	{
		playmusic(mlx->snd->music);
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = 1;
				return ;
			}
			//Если нажали клавишу
			if( e.type == SDL_KEYDOWN)
			{
				if( e.key.keysym.sym == SDLK_m )
				{
					//Если музыка на паузе
					if( Mix_PausedMusic() == 1 )
					{
						//Продолжить играть
						Mix_ResumeMusic();
					}
						//Если музыка играет
					else
					{
						//Приостановить проигрывание
						Mix_PauseMusic();
					}
				}
				if (e.key.keysym.sym == SDLK_w)
				{
					mlx->plr->x++;
					sound_eff(mlx);
				}
				if (e.key.keysym.sym == SDLK_z)
					Mix_Pause(mlx->obj->chan);
			}
		}
	}
}

void	initdist(t_main *mlx)
{
	mlx->obj = malloc(sizeof(t_obj));
	mlx->obj->dist = 11;
	mlx->obj->chan = -1;
	mlx->obj->next = malloc(sizeof(t_obj));
	mlx->obj->next->dist = 22;
	mlx->obj->next->chan = -1;
	mlx->obj->next->next = malloc(sizeof(t_obj));
	mlx->obj->next->next->dist = 45;
	mlx->obj->next->next->chan = -1;
	mlx->obj->next->next->next = NULL;
	mlx->plr = malloc(sizeof(t_plr));
	mlx->plr->x = 0;
	Mix_VolumeChunk(mlx->snd->chunks->fire, 128);
}

int main(int argc, char* argv[])
{
	t_main	*mlx;
	mlx = malloc(sizeof(t_main));
	initsdl(mlx);
	initdist(mlx);
	eventsmusic(mlx);
	closesdl(mlx->snd);
	return 0;
}