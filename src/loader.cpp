#include "include/loader.hpp"

level_t* loadLVL(const char* path){
    std::ifstream lvlStream;

    // Open File
    lvlStream.open(path, std::fstream::in | std::fstream::binary);

    if(!lvlStream.is_open()) return nullptr;

    /** FILE HEADER **/
    uint8_t* header = new uint8_t[HEADER_SIZE];
    lvlStream.read(reinterpret_cast<char*>(header), HEADER_SIZE);

    if(!(header[0] == 'L' && header[1] == 'V' && header[2] == 'L')){
        delete[] header;
        lvlStream.close();

        return nullptr;
    }

    /** META DATA **/
    // File Size
    uint32_t fileSize = 0;
    for(uint8_t i = 0; i < 3; i++) fileSize += header[FILE_SIZE_PTR + i * sizeof(uint8_t)] << (8 * i);

    // Level Data Address
    uint16_t mapDataAddress = 0;
    for(uint8_t i = 0; i < 2; i++) mapDataAddress += header[LEVEL_DATA_PTR + i * sizeof(uint8_t)] << (8 * i);

    // Texture Data Address
    uint16_t textureDataAddress = 0;
    for(uint8_t i = 0; i < 2; i++) textureDataAddress += header[TEXTURE_DATA_PTR + i * sizeof(uint8_t)] << (8 * i);

    /** READ FULL FILE **/
    delete[] header;

    // Reset File Stream
    lvlStream.clear();
    lvlStream.seekg(0, std::ios::beg);

    // Read File
    uint8_t* fileContent = new uint8_t[fileSize];
    lvlStream.read(reinterpret_cast<char*>(fileContent), fileSize);

    lvlStream.close();

    /** LEVEL GENERATION **/
    level_t* level = (level_t*) malloc(sizeof(level_t));

    /** MAP DATA **/
    loadMap(level, fileContent, mapDataAddress);

    /** TEXTURE DATA **/
    loadTextures(level, fileContent, textureDataAddress);

    delete[] fileContent;
    return level;
}

void loadMap(level_t* level, const uint8_t* fileContent, const uint16_t mapDataAddress){
    // Load Dimensions
    level -> size.x = fileContent[mapDataAddress];
    level -> size.y = fileContent[mapDataAddress + 1];

    // Load Level Type
    level -> type = fileContent[mapDataAddress + 2];

    /** MAP LOADING **/
    uint16_t mapSize = level -> size.x * level -> size.y;
    uint16_t mapAddressPtr = mapDataAddress + 3;

    // Load Wall Map
    level -> wallMap = (uint8_t*) malloc(mapSize * sizeof(uint8_t));
    for(uint16_t i = 0; i < mapSize; i++){ 
        level -> wallMap[i] = fileContent[mapAddressPtr + i];
    }
    mapAddressPtr += mapSize;
    
    // Load Floor Map
    if(level -> type >> 1 & 0b1){
        level -> floorMap = (uint8_t*) malloc(mapSize * sizeof(uint8_t));
        for(uint16_t i = 0; i < mapSize; i++) level -> floorMap[i] = fileContent[mapAddressPtr + i];
        mapAddressPtr += mapSize;
    }

    // Load Ceiling Map
    if(level -> type & 0b1){
        level -> ceilMap = (uint8_t*) malloc(mapSize * sizeof(uint8_t));
        for(uint16_t i = 0; i < mapSize; i++) level -> ceilMap[i] = fileContent[mapAddressPtr + i];
    }
}

void loadTextures(level_t* level, const uint8_t* fileContent, const uint16_t textureDataAddress){
    // Load Texture Count
    level -> textureCount = fileContent[textureDataAddress];

    /** TEXTURE LOADING **/
    level -> textures = (texture_t*) malloc((level -> textureCount + 1) * sizeof(texture_t));
    uint16_t textureAddressPtr = textureDataAddress + 1;

    for(uint8_t i = 1; i <= level -> textureCount; i++){
        //** HEADER **//
        // Load Dimensions
        level -> textures[i].size.x = fileContent[textureAddressPtr++];
        level -> textures[i].size.y = fileContent[textureAddressPtr++];

        // Load Frame Count
        level -> textures[i].frameCount = fileContent[textureAddressPtr++];

        // Load Pixel Data
        level -> textures[i].pixelData = (uint32_t**) malloc(level -> textures[i].frameCount * sizeof(uint32_t*));
        for(uint8_t j = 0; j < level -> textures[i].frameCount; j++){
            level -> textures[i].pixelData[j] = (uint32_t*) malloc(level -> textures[i].size.x * level -> textures[i].size.y * sizeof(uint32_t));

            // Load Individual Pixels
            for(uint16_t k = 0; k < level -> textures[i].size.x * level -> textures[i].size.y; k++){
                uint8_t r = fileContent[textureAddressPtr++];
                uint8_t g = fileContent[textureAddressPtr++];
                uint8_t b = fileContent[textureAddressPtr++];
                level -> textures[i].pixelData[j][k] = (uint32_t) (r << 16) + (uint32_t) (g << 8) + b;
            }
        }

        // Set Current Frame
        level -> textures[i].currentFrame = 0;
    }
}