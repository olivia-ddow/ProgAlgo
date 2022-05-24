#include <SDL2/SDL.h>
#include "lodepng.h"

// Fake SDL IMAGE IMG_Load that use lodepng. Note calling SDL_FreeSurface won't
// free the data array so don't use it in production !
SDL_Surface* IMG_Load(const char* filename) {
	unsigned char* image;
	unsigned w, h;
	unsigned error = lodepng_decode32_file(&image, &w, &h, filename);
	if(error) {
		printf("decoder error %u: %s\n", error, lodepng_error_text(error));
		return 0;
	}
	unsigned rmask = 0xff000000;
	unsigned gmask = 0x00ff0000;
	unsigned bmask = 0x0000ff00;
	unsigned amask = 0x000000ff;
	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(image, w, h, 32, 4*w, rmask, gmask, bmask, amask);
	return surface;
}
