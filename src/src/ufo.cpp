#include <ufo.hpp>
#include <chrono>
#include <global.hpp>
#include <spaceship.hpp>

std::chrono::steady_clock::time_point ufo_time=std::chrono::steady_clock::now();

void Ufo::init(){
    ufo.TextureFromImg("img/ufo.png");
    x=WINDOW_WIDTH+1;
    y=50;
}

void Ufo::update(){
    std::chrono::milliseconds delta=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-ufo_time);
    if(UFO_TIME<=delta){
        x-=UFO_SPEED;
        if(x+UFO_WIDTH<0){
            x=WINDOW_WIDTH+1;
            ufo_time=std::chrono::steady_clock::now();
            return;
        }
        check_collisions();
        render();
    }
}

void Ufo::check_collisions(){
    for(int i=ship_projectiles.size()-1;i>=0;i--){
        auto [p_x,p_y]=ship_projectiles[i];
        if(p_y+PROJECTILE_HEIGHT<y)
            continue;
        if(p_y<=y+UFO_HEIGHT && p_x>=x && p_x+PROJECTILE_WIDTH<=x+UFO_WIDTH){
            ship_projectiles.erase(ship_projectiles.begin()+i);
            score+=30;
            x=WINDOW_WIDTH+1;
            ufo_time=std::chrono::steady_clock::now();
            return;
        }
    }
}

void Ufo::render(){
SDL_Rect dest;
    dest.h=UFO_HEIGHT;
    dest.w=UFO_WIDTH;
    dest.x=x;
    dest.y=y;
    SDL_RenderCopy(renderer,ufo.GetTexture(),NULL,&dest);
}

void Ufo::destroy(){
    ufo.Destroy();
}