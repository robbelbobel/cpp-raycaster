#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"
#include "renderer.hpp"

class Game{
public:
    /* PUBLIC FUNCTIONS */
    Game(const level_t* level, SDL_Window* window);
    ~Game();

    bool tick(uint16_t deltaTime);
    void render();

private:
    /* PRIVATE FUNCTIONS */
    bool handleInput(uint16_t deltaTime);

    /* PRIVATE VARIABLES */
    const level_t* level;
    Player* player;
    Renderer* renderer;
};

#endif