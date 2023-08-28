#include <spaceship.hpp>
#include <enemies.hpp>

std::vector<projectile>ship_projectiles;

void Spaceship::init(){
    spaceship.TextureFromImg("img/spaceship.png");
    
    init_pos();

    upper_hitbox.w=10;
    upper_hitbox.h=11;

    lower_hitbox.w=SHIP_WIDTH;
    lower_hitbox.h=SHIP_HEIGHT-lower_hitbox.y+1;

    time=std::chrono::steady_clock::now();
}

void Spaceship::init_pos(){
    x=(WINDOW_WIDTH/2)-(SHIP_WIDTH/2);
    y=WINDOW_HEIGHT-SHIP_HEIGHT-30;

    upper_hitbox.x=x+10;
    upper_hitbox.y=y;
    lower_hitbox.x=x;
    lower_hitbox.y=y+12;
}

void Spaceship::move(){
const Uint8 *keys=SDL_GetKeyboardState(NULL);
    if(keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]){
        x=((x-SHIP_SPEED>=0)?x-SHIP_SPEED:0);
        upper_hitbox.x=x+10;
        lower_hitbox.x=x;
    }
    else if(keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]){
        x=((x+SHIP_SPEED<=WINDOW_WIDTH-SHIP_WIDTH+1)?x+SHIP_SPEED:WINDOW_WIDTH-SHIP_WIDTH+1);
        upper_hitbox.x=x+10;
        lower_hitbox.x=x;
    }
    
}

void Spaceship::shoot(){
    auto end_time=std::chrono::steady_clock::now();
    if(std::chrono::duration_cast<std::chrono::milliseconds>(end_time-time).count()>=SPACESHIP_SHOOT_TIME){
        const Uint8 *keys=SDL_GetKeyboardState(NULL);
        if(keys[SDL_SCANCODE_SPACE]){
            ship_projectiles.push_back({SHIP_WIDTH/2-1+x,y-PROJECTILE_HEIGHT});
            time=end_time;
        }
    }
}

void Spaceship::update_projectiles(){
    for(int i=0;i<ship_projectiles.size();i++){
        ship_projectiles[i].y-=PROJECTILE_SPEED;
        if(ship_projectiles[i].y+PROJECTILE_HEIGHT<0){
            std::swap(ship_projectiles[i],ship_projectiles[ship_projectiles.size()-1]);
            ship_projectiles.pop_back();
        }
    }
}

bool Spaceship::check_collision(){
    for(auto [p_x,p_y]:enemy_projectiles){
        if(p_y>=y+SHIP_WIDTH)
            continue;
        if(p_y+PROJECTILE_HEIGHT>=upper_hitbox.y && p_x>=upper_hitbox.x && p_x+PROJECTILE_WIDTH<=upper_hitbox.x+upper_hitbox.w)
            return true;
        if(p_y+PROJECTILE_HEIGHT>=lower_hitbox.y && p_x>=lower_hitbox.x && p_x+PROJECTILE_WIDTH<=lower_hitbox.x+lower_hitbox.w)
            return true;
    }
    return false;
}

void Spaceship::render_projectiles(){
    SDL_SetRenderDrawColor(renderer,255,242,0,0);
    SDL_Rect dest;
    dest.w=PROJECTILE_WIDTH;
    dest.h=PROJECTILE_HEIGHT;
    for(auto p:ship_projectiles){
        dest.x=p.x;
        dest.y=p.y;
        SDL_RenderFillRect(renderer,&dest);
    }
}

void Spaceship::render_ship(){
SDL_Rect dest;
    dest.x=x;
    dest.y=y;
    dest.w=SHIP_WIDTH;
    dest.h=SHIP_HEIGHT;
    SDL_RenderCopy(renderer,spaceship.GetTexture(),NULL,&dest);
}

void Spaceship::destroy(){
    SDL_DestroyTexture(spaceship.GetTexture());
}