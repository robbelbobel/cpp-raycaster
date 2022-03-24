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

class Renderer{
public:
    /** PUBLIC FUNCTIONS **/
    Renderer(SDL_Window* window);

    void renderGame(const level_t* level, Player* player);

private:
    /** PRIVATE FUNCTIONS **/
    void renderEnvironment(const level_t* level, Player* player);
    void renderMap(const level_t* level, Player* player);

    /** PRIVATE VARIABLES **/
    SDL_Window* window;
};

#endif