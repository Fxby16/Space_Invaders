#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <textures.hpp>
#include <global.hpp>

void Texture::TextureFromImg(const char *to_load){
    auto s=IMG_Load(to_load);
    t=SDL_CreateTextureFromSurface(renderer,s);
    SDL_FreeSurface(s);
}

SDL_Texture *Texture::GetTexture(){
    return t;
}

void Texture::Destroy(){
    SDL_DestroyTexture(t);
}