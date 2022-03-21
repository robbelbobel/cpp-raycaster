#ifndef DRAW_H
#define DRAW_H

#include <SDL.h>

#include "ray.hpp"
#include "texture.hpp"

#define WIDTH   800.0f
#define HEIGHT  450.0f

#define WALLPIXELHEIGHT 1
#define FLOORPIXELHEIGHT 1

#define RAYCOUNT WIDTH 
#define FOV 90.0f

#define WALLHEIGHT 1.0f

void renderEnvironment(SDL_Surface* windowSurface, const level_t* level, Player* player);
void renderMap(SDL_Surface* windowSurface, const level_t* level, Player* player);
void renderGame(SDL_Surface* windowSurface, const level_t* level, Player* player);

#endif