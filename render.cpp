#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

namespace render {

unsigned int buffer_size;

SDL_Surface* screen;

void initialize(unsigned int N) {
	buffer_size = N;

	if ( SDL_Init(SDL_INIT_VIDEO) != 0 ){
		printf("Failed to initialize sdl\n");
		return;
	}

	screen = SDL_SetVideoMode(640, 480, 0, SDL_DOUBLEBUF | SDL_HWSURFACE);
	SDL_WM_SetCaption("Frobnicators Analyzer", NULL);
}

void terminate() {
	SDL_Quit();
}

bool update() {
	SDL_Event event;
	while ( SDL_PollEvent(&event) ){
		switch ( event.type ){
		case SDL_QUIT:
			return false;
			break;

		case SDL_KEYDOWN:
			if ( event.key.keysym.sym == SDLK_ESCAPE){
				return false;
			}
		}
	}
	return true;
}

void render(const float* const amplitudes) {
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

	lineRGBA(screen,
			 0, 240,
			 640, 240,
			 255, 255, 255, 255);

	int width = 4;
	int dist = 2;

	float height = 250.0;

	for(int i=0; i<(buffer_size/2); ++i) {
		float val = amplitudes[i];

		int x = i*(dist*2+width);
		int y_top = 240 - (val*5.0) * height;

		if(x > 640) break;

		boxRGBA(screen,
				x, y_top,
				x+width, 240,
				255, 255, 255, 255);
	}

	SDL_Flip(screen);

}

}
