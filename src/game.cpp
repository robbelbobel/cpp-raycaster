#include "include/game.hpp"

Game::Game(const level_t* level, SDL_Window* window){
    Game::level = level;
    Game::player = new Player();

    Game::window = window;
}

Game::~Game(){
    delete Game::level;
    delete Game::player;
}

bool Game::tick(uint16_t deltaTime){
    return Game::handleInput(deltaTime);
}

void Game::draw(){
    renderGame(SDL_GetWindowSurface(Game::window), Game::level, Game::player);

    SDL_UpdateWindowSurface(window);
}

bool Game::handleInput(uint16_t deltaTime){
    // Handle Events
    SDL_Event e;
    
    while(SDL_PollEvent(&e)){
        switch(e.type){
            case SDL_QUIT:
                return false;

            default:
                break;
        }
    }

    // Handle Key Presses
    const uint8_t* keyState = SDL_GetKeyboardState(NULL);
    
    if(keyState[SDL_SCANCODE_W])        Game::player -> move(DIR_FORWARD,   level, deltaTime);
    if(keyState[SDL_SCANCODE_S])        Game::player -> move(DIR_BACKWARD,  level, deltaTime);
    if(keyState[SDL_SCANCODE_D])        Game::player -> move(DIR_RIGHT,     level, deltaTime);
    if(keyState[SDL_SCANCODE_A])        Game::player -> move(DIR_LEFT,      level, deltaTime);
    if(keyState[SDL_SCANCODE_RIGHT])    Game::player -> move(ANGLE_RIGHT,   level, deltaTime);
    if(keyState[SDL_SCANCODE_LEFT])     Game::player -> move(ANGLE_LEFT,    level, deltaTime);

    return true;
}