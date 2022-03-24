#include "include/loader.hpp"
#include "include/game.hpp"

/* FUNCTION PROTOTYPES */
uint8_t intialize(SDL_Window** window);

int main(){
    /* INTIALIZATION */
    SDL_Window* window;

    if(!intialize(&window)) return -1;

    /* INITIALIZE GAME VARIABLES */
    // Load LVL File
    level_t* level = loadLVL("/Users/robbetiteca/Documents/LVL/test.lvl");

    if(level == nullptr){
        std::cerr << "ERROR: Unable to load LVL file!" << std::endl;
        return -1;
    }

    // Create Game
    Game game(level, window);

    // Delta Time
    uint32_t oldTime = SDL_GetTicks();
    uint16_t deltaTime = 0;
    uint16_t updateTime = 0;

    /* MAIN LOOP */
    bool running = true;

    while(running){
        // Tick Game
        running = game.tick(deltaTime);

        // Draw Game
        game.render();

        SDL_UpdateWindowSurface(window);

        // Update Time Variables
        deltaTime = SDL_GetTicks() - oldTime;
        oldTime = SDL_GetTicks();
        updateTime += deltaTime;
    }

    // Quit SDL
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

/** FUNCTION DECLARATIONS **/
uint8_t intialize(SDL_Window** window){
    // Initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        std::cerr << "ERROR: Failed to intialize SDL, error code: " <<  SDL_GetError() << ".\nQuitting...\n" << std::endl;
        return 0;
    }

    // Create SDL Window
    *window = SDL_CreateWindow("Raycaster", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    if(window == nullptr){
        std::cerr << "ERROR: Failed to create SDL window, error code: " << SDL_GetError() << ".\nQuitting...\n" << std::endl;
        return 0;
    }

    return 1;
}