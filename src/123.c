#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

/* 	gcc 123.c -L /Users/adoyle/homebrew/lib -lSDL2-2.0.0 -I /Users/adoyle/homebrew/include/SDL2  
 */
int main(int argc, char* argv[])
{

	Mix_Music *music = NULL;
	// Initialize SDL.
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		return -1;			
	//Initialize SDL_mixer 
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) 
		return -1; 	
	// Load our music
	music = Mix_LoadMUS( "blade1.ogg" );
	if (music == NULL)
		return -1;	
	if ( Mix_PlayMusic( music, 0) == -1 )
		return -1;		
	while (Mix_PlayingMusic());	
	SDL_Delay( 2000 );
	Mix_FreeMusic(music);
	Mix_CloseAudio();
    SDL_Quit();
	
	return 0;
}