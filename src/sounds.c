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
	t_snd *snd;
	snd = malloc(sizeof(t_snd));
	snd->music = malloc(sizeof(t_music));
	mlx->snd = snd;
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		return ;			
	if (Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1) 
		return ;
	snd->music->mus1 = Mix_LoadMUS( "/sound/blade1.ogg");
	// snd->music->mus2 = Mix_LoadMUS( "/sound/blade1.ogg");
	// snd->music->mus3 = Mix_LoadMUS( "/sound/blade1.ogg");
	// snd->music->mus4 = Mix_LoadMUS( "/sound/blade1.ogg");
	// snd->music->mus5 = Mix_LoadMUS( "/sound/blade1.ogg");
	if (!(snd->music->mus1) || !(snd->music->mus1) || !(snd->music->mus1) || !(snd->music->mus1) || !(snd->music->mus1))
		return ;
}

void	playmusic(t_music *music)
{
	if (Mix_PlayMusic(music->mus1, 0) == -1)
		return ;		
	while (Mix_PlayingMusic());
}

void	closesdl(t_snd *snd)
{
	Mix_FreeMusic(snd->music->mus1);
	// Mix_FreeMusic(snd->music->mus2);
	// Mix_FreeMusic(snd->music->mus3);
	// Mix_FreeMusic(snd->music->mus4);
	// Mix_FreeMusic(snd->music->mus5);
	Mix_CloseAudio();
    SDL_Quit();	
}

int main(int argc, char* argv[])
{
	t_main	*mlx;
	mlx = malloc(sizeof(t_main));
	initsdl(mlx);
	playmusic(mlx->snd->music);
	SDL_Delay(2000);
	closesdl(mlx->snd);
	return 0;
}