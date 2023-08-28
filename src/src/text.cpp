#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <vector>
#include <text.hpp>

void Text::create_text(TTF_Font *font,SDL_Color color,Uint32 wrap,const char *string,Uint32 x,Uint32 y){
    SDL_Surface *temp=TTF_RenderUTF8_Blended_Wrapped(font,string,color,wrap);
    t.texture=SDL_CreateTextureFromSurface(renderer,temp);
    t.dest.h=temp->h;
    t.dest.w=temp->w;
    t.dest.x=x;
    t.dest.y=y;
    SDL_FreeSurface(temp);
}

std::pair<int,int> Text::get_size(){
    return {t.dest.w,t.dest.h};
}

void Text::set_x_y(int x,int y){
    t.dest.x=x;
    t.dest.y=y;
}

std::pair<int,int> Text::get_x_y(){
    return {t.dest.x,t.dest.y};
}

void Text::render(SDL_Rect *tt=NULL){
    SDL_RenderCopy(renderer,t.texture,tt,&t.dest);
}

void Text::destroy(){
    SDL_DestroyTexture(t.texture);
}