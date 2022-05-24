#include <SDL2/SDL.h>
#include "lodepng.h"

// Fake SDL IMAGE IMG_Load that use lodepng. Note calling SDL_FreeSurface won't
// free the data array so don't use it in production !
SDL_Surface* IMG_Load(const char* filename);
