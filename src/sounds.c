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
	snd->music->mus1 = Mix_LoadMUS( "/sound/blade1.ogg");
	snd->music->mus1 = Mix_LoadMUS( "D:\\Coding\\doom-nuked\\sound\\blade2.ogg");
	snd->music->mus2 = Mix_LoadMUS( "D:\\Coding\\doom-nuked\\sound\\blade4.ogg");
	// snd->music->mus2 = Mix_LoadMUS( "/sound/blade2.ogg");
	// snd->music->mus3 = Mix_LoadMUS( "/sound/blade3.ogg");
	// snd->music->mus4 = Mix_LoadMUS( "/sound/blade4.ogg");
	// snd->music->mus5 = Mix_LoadMUS( "/sound/blade5.ogg");
	mlx->snd->music->nummus = 1;
	if (!(snd->music->mus1) || !(snd->music->mus2) || !(snd->music->mus3) || !(snd->music->mus4) || !(snd->music->mus5))
		return ;
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

			}
		}
	}
}

int main(int argc, char* argv[])
{
	t_main	*mlx;
	mlx = malloc(sizeof(t_main));
	initsdl(mlx);
	eventsmusic(mlx);
	closesdl(mlx->snd);
	return 0;
}