#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"
#include "render.hpp"

class Game{
public:
    /* PUBLIC FUNCTIONS */
    Game(const level_t* level, SDL_Window* window);
    ~Game();

    bool tick(uint16_t deltaTime);
    void draw();

private:
    /* PRIVATE FUNCTIONS */
    bool handleInput(uint16_t deltaTime);

    /* PRIVATE VARIABLES */
    SDL_Window* window;
    const level_t* level;
    Player* player;
};

#endif