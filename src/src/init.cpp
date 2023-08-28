#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <global.hpp>
#include <text.hpp>
#include <textures.hpp>

int Init(const char *title,int w,int h){
    if(SDL_Init(SDL_INIT_EVERYTHING)<0)
        return -1;
    if(TTF_Init()<0)
        return -1;
    if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)==0)
        return -1;

    window=SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,w,h,SDL_WINDOW_ALLOW_HIGHDPI);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    return 0;
}

void SetFullScreen(){
bool update_event=false;
    fullscreen=!fullscreen;
    if(fullscreen){
        SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);
    }
    else if(!fullscreen){
        SDL_SetWindowFullscreen(window,0);
        SDL_SetWindowPosition(window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
    }
    while(!update_event){ //wait for the update confirmation
        while(SDL_PollEvent(&event)){
            if(event.window.event==SDL_WINDOWEVENT_EXPOSED){
                update_event=true;
                break;
            }
        }
    }
}

void Quit(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}