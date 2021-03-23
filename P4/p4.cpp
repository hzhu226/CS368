#include <SDL.h>
#undef main
#include <stdio.h>
#include <SDL_image.h>
#include <string.h>

//Screen dimension constants
const int SCREEN_WIDTH = 1152;
const int SCREEN_HEIGHT = 648;


/* 
 * Keys for other two addtional images are "q" and "e" 
 * Key for background image is "z"
 */
int main( int argc, char* args[] ) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else {
		SDL_Window* myWindow = NULL;
		myWindow = SDL_CreateWindow("p4", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		SDL_Surface* windowSurface = NULL;
		windowSurface = SDL_GetWindowSurface(myWindow);
		SDL_Surface* background = NULL;
		background = IMG_Load("background.png");
		SDL_BlitSurface( background, NULL, windowSurface, NULL );
  		SDL_UpdateWindowSurface( myWindow );


		SDL_Event e;
		bool quit = false;
		SDL_Surface* currentSurface = NULL;

		while (!quit) {
  			while (SDL_PollEvent( &e ) !=0 ) {
    			if( e.type == SDL_QUIT )
				{
					quit = true;
				}
				else if( e.type == SDL_KEYDOWN )
			    {
					switch( e.key.keysym.sym ) {
						// image one is shown when q is pressed
						case SDLK_q:
							currentSurface = IMG_Load( "one.png" );
							break;
						// image two is shown when e is pressed
						case SDLK_e:
							currentSurface = IMG_Load( "two.png" );
							break;
						// background image is shown again when z is pressed
						case SDLK_z:
							currentSurface = IMG_Load( "background.png" );
							break;
					}
				}
			
  		}
  		SDL_BlitSurface( currentSurface, NULL, windowSurface, NULL );
  		SDL_UpdateWindowSurface( myWindow );
	}

	SDL_FreeSurface(currentSurface);
	currentSurface = NULL;
	SDL_FreeSurface(background);
	background = NULL;
	//Destroy window
	SDL_DestroyWindow(myWindow);
	myWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
	}

	return 0;
}