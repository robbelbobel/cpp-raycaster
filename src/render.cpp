#include "include/render.hpp"

void renderEnvironment(SDL_Surface* windowSurface, const level_t* level, Player* player){
    uint16_t planeDist = (WIDTH / 2) / tanf(angle::toRad(FOV / 2));

    float angleStep     = FOV / RAYCOUNT;
    float startAngle    = player -> getAngle() - FOV / 2;

    float wallWidth     = WIDTH / RAYCOUNT;

    vecf2d_t position;
    position.x = player -> getPosition().x;
    position.y = player -> getPosition().y;

    Ray ray(position);

    for(uint16_t i = 0; i < RAYCOUNT; i++){
        float angle = startAngle + i * angleStep;

        ray.cast(level, angle);
        
        /** RENDER WALLS **/
        // Calculate Wall Position   
        int16_t wallTop     = HEIGHT / 2 - ((WALLHEIGHT / 2) / (ray.getLength() * cosf(angle::toRad(angle - player -> getAngle())))) * planeDist;
        uint16_t wallBottom = HEIGHT / 2 + ((WALLHEIGHT / 2) / (ray.getLength() * cosf(angle::toRad(angle - player -> getAngle())))) * planeDist;
        uint16_t wallHeight = wallBottom - wallTop;

        SDL_Rect texPixelRect;

        texPixelRect.x = WIDTH - i * wallWidth;
        texPixelRect.w = wallWidth;
        texPixelRect.h = WALLPIXELHEIGHT;

        // Default To Error Texture If Texture ID Is Out Of Range
        const texture_t* wallTexture = ray.getEndPoint().textureID > level -> textureCount ? &level -> textures[0] : &level -> textures[ray.getEndPoint().textureID];

        // Calulate Texture Column
        uint8_t texCol;

        switch(ray.getEndPoint().direction){
            case POINT_DIR_UP:
                texCol = (ray.getEndPoint().position.x - floor(ray.getEndPoint().position.x)) * wallTexture -> size.x;
                break;

            case POINT_DIR_DOWN:
                texCol = (1 - (ray.getEndPoint().position.x - floor(ray.getEndPoint().position.x))) * wallTexture -> size.x;
                break;

            case POINT_DIR_LEFT:
                texCol = (1 - (ray.getEndPoint().position.y - floor(ray.getEndPoint().position.y))) * wallTexture -> size.x;
                break;

            case POINT_DIR_RIGHT:
                texCol = (ray.getEndPoint().position.y - floor(ray.getEndPoint().position.y)) * wallTexture -> size.x;
                break;
        }

        float pixelStep = (float) wallTexture -> size.y / (wallBottom - wallTop);
        
        for(int16_t j = wallTop; j < wallBottom; j += WALLPIXELHEIGHT){
            if(j < 0) continue; 
            if(j > HEIGHT) break;

            texPixelRect.y = j;

            uint32_t color = wallTexture -> pixelData[wallTexture -> currentFrame][(uint8_t)(pixelStep * (j - wallTop)) * wallTexture -> size.x + texCol];
            
            SDL_FillRect(windowSurface, &texPixelRect, SDL_MapRGB(windowSurface -> format, color >> 16, (color >> 8) & 0xFF, color & 0xFF));
        }

        /** RENDER FLOOR **/
        if(level -> type & 0b10){
            texPixelRect.h = FLOORPIXELHEIGHT;

            for(uint16_t j = wallBottom; j < HEIGHT; j+= FLOORPIXELHEIGHT){
                float dist = ((planeDist / (j - HEIGHT * player -> getPosition().z)) * player -> getPosition().z) / cosf(angle::toRad(angle - player -> getAngle()));

                float x = player -> getPosition().x + dist * cosf(angle::toRad(angle));
                float y = player -> getPosition().y - dist * sinf(angle::toRad(angle));

                const uint16_t mapIndex = (uint16_t) y * level -> size.x + (uint16_t) x;

                const texture_t* texture = mapIndex < level -> size.x * level -> size.x ? &level -> textures[level -> floorMap[mapIndex]] : &level -> textures[0];

                uint32_t color = texture -> pixelData[texture -> currentFrame][((uint16_t)(y * texture -> size.x) % texture -> size.x) * texture -> size.y + (uint16_t) (x * texture -> size.x) % texture -> size.x];
                
                texPixelRect.y = j;

                SDL_FillRect(windowSurface, &texPixelRect, SDL_MapRGB(windowSurface -> format, color >> 16, (color >> 8) & 0xFF, color & 0xFF));
            }
        }
    }
}

void renderMap(SDL_Surface* windowSurface, const level_t* level, Player* player){
    /* TILE RENDERING */
    // Calculate Tile Dimensions
    SDL_Rect tile_r;
    tile_r.x = 0;
    tile_r.y = 0;
    tile_r.h = HEIGHT / (level -> size.y * 3);
    tile_r.w = tile_r.h;
    
    // Draw Tiles
    for(uint8_t y = 0; y < level -> size.y; y++){
        for(uint8_t x = 0; x < level -> size.x; x++){
            tile_r.x = x * tile_r.w;
            tile_r.y = y * tile_r.h;

            SDL_FillRect(windowSurface, &tile_r, SDL_MapRGB(windowSurface -> format, level -> wallMap[y * level -> size.x + x] ? 0xFF : 0x00, 0x00, 0x00));
        }
    }
    
    /* PLAYER RENDERING */
    // Calculate Player Dimensions
    SDL_Rect player_r;
    player_r.h = tile_r.h / 2;
    player_r.w = player_r.h;
    player_r.x = (player -> getPosition().x * tile_r.h) - (player_r.w / 2);
    player_r.y = (player -> getPosition().y * tile_r.h) - (player_r.h / 2);

    // // Draw Player
    SDL_FillRect(windowSurface, &player_r, SDL_MapRGB(windowSurface -> format, 0xFF, 0xFF, 0xFF));
}

void renderGame(SDL_Surface* windowSurface, const level_t* level, Player* player){
    // Clear Screen
    SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface -> format, 24, 24, 24));

    // Render Game Elements
    renderEnvironment(windowSurface, level, player);
    renderMap(windowSurface, level, player);
}