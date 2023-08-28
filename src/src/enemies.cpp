#include <enemies.hpp>
#include <spaceship.hpp>
#include <random>
#include <chrono>
#include <ufo.hpp>

std::vector<projectile>enemy_projectiles;
std::vector<std::vector<Enemy>>enemies(3,std::vector<Enemy>(ENEMIES_NUMBER));
std::chrono::steady_clock::time_point enemy_time;
std::vector<std::pair<Texture,Texture>>enemies_textures(3);
std::chrono::steady_clock::time_point anim_time;
std::chrono::steady_clock::time_point _time;
int prob_light_blue=100;
int prob_red=100;
int prob_green=100;
int MS_ENEMY_ANIM;
int MS_ENEMY_SHOOT_;
int ENEMIES_REMAINING;

Enemy_Movement enemy_movement=RIGHT;

void init_enemies(){

    generate_enemies();

    enemies_textures[0].first.TextureFromImg("img/lightblue1.png");
    enemies_textures[0].second.TextureFromImg("img/lightblue2.png");
    enemies_textures[1].first.TextureFromImg("img/red1.png");
    enemies_textures[1].second.TextureFromImg("img/red2.png");
    enemies_textures[2].first.TextureFromImg("img/green1.png");
    enemies_textures[2].second.TextureFromImg("img/green2.png");
}

void generate_enemies(){
enemy_movement=RIGHT;
MS_ENEMY_ANIM=MS_ANIM_TIME;
MS_ENEMY_SHOOT_=MS_ENEMY_SHOOT;
ENEMIES_REMAINING=ENEMIES_NUMBER*3;

anim_time=_time=std::chrono::steady_clock::now();

int x;
int y=100;
std::random_device rd;
std::mt19937 gen(rd());

    enemies.resize(3);

    for(int i=0;i<enemies.size();i++){
        x=(WINDOW_WIDTH-(ENEMIES_NUMBER*(ENEMY_WIDTH+ENEMY_WIDTH/4)))/2;
        enemies[i].resize(ENEMIES_NUMBER);
        for(int j=0;j<enemies[i].size();j++){
            x=x+ENEMY_WIDTH/8;
            enemies[i][j].x=x;
            enemies[i][j].y=y;
            std::uniform_int_distribution<>distr_type(0,100);
            int prob=distr_type(gen);
            if(prob<=prob_green)
                enemies[i][j].type=enemy_type::GREEN;
            else if(prob<=prob_red)
                enemies[i][j].type=enemy_type::RED;
            else if(prob<=prob_light_blue)
                enemies[i][j].type=enemy_type::LIGHT_BLUE;
            x=x+ENEMY_WIDTH+ENEMY_WIDTH/8;
        }
        y+=(ENEMY_HEIGHT*2);
    }
    ufo_time=std::chrono::steady_clock::now();
}

bool count_enemies(){
int num=0;
    for(auto &i:enemies)
        num+=i.size();
    if((ENEMIES_REMAINING-num)%5==0 && num!=ENEMIES_REMAINING){
        MS_ENEMY_ANIM-=300;
        MS_ENEMY_SHOOT_-=150;
        ENEMIES_REMAINING=num;
    }
    return ((num==0)?true:false);
}

bool check_enemy_pos(){
    for(auto &i:enemies)
        for(auto &j:i)
            if(j.y+ENEMY_HEIGHT>WINDOW_HEIGHT)
                return false;

    return true;
}

void move_enemies(){
    if(enemy_movement==RIGHT){
        for(int i=0;i<enemies.size();i++)
            if(enemies[i].size()>0 && enemies[i].back().x+ENEMY_WIDTH+ENEMY_WIDTH/2>=WINDOW_WIDTH){
                enemy_movement=LEFT;
                for(int k=0;k<enemies.size();k++)
                    for(int j=0;j<enemies[k].size();j++)
                        enemies[k][j].y+=(ENEMY_HEIGHT/2);

                return;
            }
        for(int k=0;k<enemies.size();k++)
            for(int j=0;j<enemies[k].size();j++)
                enemies[k][j].x+=(ENEMY_WIDTH/2);
    }else{
        for(int i=0;i<enemies.size();i++)
            if(enemies[i].size()>0 && enemies[i][0].x-ENEMY_WIDTH/2<0){
                enemy_movement=RIGHT;
                for(int k=0;k<enemies.size();k++)
                    for(int j=0;j<enemies[k].size();j++)
                        enemies[k][j].y+=(ENEMY_HEIGHT/2);

                return;
            }
        for(int k=0;k<enemies.size();k++)
            for(int j=0;j<enemies[k].size();j++)
                enemies[k][j].x-=(ENEMY_WIDTH/2);
    }
}

void enemies_shoot(){
    auto end_time=std::chrono::steady_clock::now();
    if(std::chrono::duration_cast<std::chrono::milliseconds>(end_time-enemy_time).count()>=MS_ENEMY_SHOOT){
        enemy_time=end_time;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<>distr_w(0,ENEMIES_NUMBER-1);
        std::uniform_int_distribution<>distr_h(0,enemies.size()-1);
        int j,k;
        do{
            j=distr_h(gen);
        }while(enemies[j].size()<=0);
        
        do{
            k=distr_w(gen);
        }while(k>=enemies[j].size());
        
        if(enemies[j][k].type==enemy_type::GREEN)
            enemy_projectiles.push_back({ENEMY_WIDTH/2-PROJECTILE_WIDTH/2+enemies[j][k].x,enemies[j][k].y+ENEMY_HEIGHT});
        else if(enemies[j][k].type==enemy_type::RED){
            enemy_projectiles.push_back({ENEMY_WIDTH/2-PROJECTILE_WIDTH*2+enemies[j][k].x,enemies[j][k].y+ENEMY_HEIGHT});
            enemy_projectiles.push_back({ENEMY_WIDTH/2+PROJECTILE_WIDTH+enemies[j][k].x,enemies[j][k].y+ENEMY_HEIGHT});
        }else if(enemies[j][k].type==enemy_type::LIGHT_BLUE){
            enemy_projectiles.push_back({ENEMY_WIDTH/2-PROJECTILE_WIDTH*3+enemies[j][k].x,enemies[j][k].y+ENEMY_HEIGHT});
            enemy_projectiles.push_back({ENEMY_WIDTH/2-PROJECTILE_WIDTH/2+enemies[j][k].x,enemies[j][k].y+ENEMY_HEIGHT});
            enemy_projectiles.push_back({ENEMY_WIDTH/2+PROJECTILE_WIDTH*2+enemies[j][k].x,enemies[j][k].y+ENEMY_HEIGHT});
        }
    }
}

void enemies_update_projectiles(){
    for(int i=0;i<enemy_projectiles.size();i++){
        enemy_projectiles[i].y+=ENEMY_PROJECTILE_SPEED;
        if(enemy_projectiles[i].y>WINDOW_HEIGHT){
            std::swap(enemy_projectiles[i],enemy_projectiles[enemy_projectiles.size()-1]);
            enemy_projectiles.pop_back();
        }
    }
}

void enemies_render_projectiles(){
    SDL_SetRenderDrawColor(renderer,255,242,0,0);
    SDL_Rect dest;
    dest.w=PROJECTILE_WIDTH;
    dest.h=PROJECTILE_HEIGHT;
    for(auto p:enemy_projectiles){
        dest.x=p.x;
        dest.y=p.y;
        SDL_RenderFillRect(renderer,&dest);
    }
}

void check_enemies_collisions(){
_time=std::chrono::steady_clock::now();
    if(std::chrono::duration_cast<std::chrono::milliseconds>(_time-anim_time).count()>=MS_ENEMY_ANIM){
        move_enemies();
    }
    for(int k=ship_projectiles.size()-1;k>=0;k--){
        auto [p_x,p_y]=ship_projectiles[k];
        for(int i=enemies.size()-1;i>=0;i--)
            for(int j=enemies[i].size()-1;j>=0;j--){
                if(p_y<=enemies[i][j].y+ENEMY_HEIGHT && p_x>=enemies[i][j].x && p_x<=enemies[i][j].x+ENEMY_WIDTH){
                    score+=10;
                    enemies[i].erase(enemies[i].begin()+j);
                    ship_projectiles.erase(ship_projectiles.begin()+k);
                    goto JUMP;
                }
            }
        JUMP:
            ;
    }
}

void render_enemies(){
SDL_Rect dest;  
    dest.w=ENEMY_WIDTH;
    dest.h=ENEMY_HEIGHT;

    if(std::chrono::duration_cast<std::chrono::milliseconds>(_time-anim_time).count()>=MS_ENEMY_ANIM){
        anim=!anim;
        anim_time=_time;
    }
    for(int i=0;i<enemies.size();i++){
        std::vector<SDL_Texture*>t(3);
        if(anim){
            t[enemy_type::LIGHT_BLUE]=enemies_textures[LIGHT_BLUE].second.GetTexture();
            t[enemy_type::RED]=enemies_textures[RED].second.GetTexture();
            t[enemy_type::GREEN]=enemies_textures[GREEN].second.GetTexture();
        }else{
            t[enemy_type::LIGHT_BLUE]=enemies_textures[LIGHT_BLUE].first.GetTexture();
            t[enemy_type::RED]=enemies_textures[RED].first.GetTexture();
            t[enemy_type::GREEN]=enemies_textures[GREEN].first.GetTexture();
        }

        for(auto j:enemies[i]){
            dest.x=j.x;
            dest.y=j.y;
            SDL_RenderCopy(renderer,t[j.type],NULL,&dest);
        }
    }
}

void enemies_destroy_textures(){
    for(auto [a,b]:enemies_textures){
        a.Destroy();
        b.Destroy();
    }
}