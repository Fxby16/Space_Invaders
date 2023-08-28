#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class Texture{

SDL_Texture *t;

public:
    /**
     * \param to_load a string containing the path to a image
     * \returns vector of pointers to the textures created
    */
    void TextureFromImg(const char *to_load);
    /**
     * \returns a pointer to the texture
    */
    SDL_Texture *GetTexture();
    void Destroy();
};

#endif