#if defined(_WIN32) || defined(_WIN64)
    #define _WIN32_WINNT 0x0A00
    #include <windows.h>
#endif

#include <init.hpp>
#include <global.hpp>
#include <spaceship.hpp>
#include <enemies.hpp>
#include <score.hpp>
#include <textures.hpp>
#include <main_menu.hpp>
#include <menu.hpp>
#include <ufo.hpp>
#include <select_level.hpp>
#include <max_score.hpp>
#include <level.hpp>
#include <iostream>

int main(int argc,char *argv[]){

#if defined(_WIN32) || defined(_WIN64)
    SetProcessDPIAware();
#endif

    Init("Space Invaders",WINDOW_WIDTH,WINDOW_HEIGHT);

Spaceship spaceship;
MainMenu main_menu;
Menu menu;
Texture background;
SDL_Rect background_rect={0,0,WINDOW_WIDTH,WINDOW_HEIGHT};
Score score;
Ufo ufo;
Select_level select_level;
Max_score max_score;
Level level_text;

    spaceship.init();
    main_menu.init();
    menu.init();
    background.TextureFromImg("img/background.png");
    score.init();
    ufo.init();
    select_level.init();
    max_score.init();
    level_text.init();

std::chrono::microseconds time_elapsed(0);
std::chrono::steady_clock::time_point previous_time_point=std::chrono::steady_clock::now();
bool render=true;
bool sleep=true;

    while(!quit){
        SDL_PollEvent(&event);
        if(event.type==SDL_QUIT)
            quit=true;
        if(sleep){    
            SDL_Delay(10);
            sleep=false;
        }
        std::chrono::microseconds delta=std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now()-previous_time_point);
        time_elapsed+=delta;
        previous_time_point+=delta;
        while(FRAME_TIME<=time_elapsed){
            const Uint8 *keys=SDL_GetKeyboardState(NULL);
            if(keys[SDL_SCANCODE_Q])
                quit=true;
            sleep=true;
            time_elapsed-=FRAME_TIME;
            if(!show_main_menu && !show_select_level){
                if(render){
                    if(count_enemies()){
                        render=false;
                        show_menu=true;
                        menu_state=true;
                        continue;
                    }
                    SDL_SetRenderDrawColor(renderer,0,0,0,0);
                    SDL_RenderClear(renderer);
                    spaceship.move();
                    spaceship.shoot();
                    enemies_shoot();
                    spaceship.update_projectiles();
                    enemies_update_projectiles();
                    check_enemies_collisions();
                    if(!check_enemy_pos()){
                        render=false;
                        show_menu=true;
                        menu_state=false;
                        continue;
                    }
                    if(spaceship.check_collision()){
                        render=false;
                        show_menu=true;
                        menu_state=false;
                    }
                    SDL_RenderCopy(renderer,background.GetTexture(),NULL,&background_rect);
                    spaceship.render_ship();
                    spaceship.render_projectiles();
                    enemies_render_projectiles();
                    render_enemies();
                    ufo.update();
                    score.update();
                    score.render();
                    max_score.update();
                    max_score.render();
                    level_text.update();
                    level_text.render();
                    SDL_RenderPresent(renderer);
                }
            }else if(show_main_menu){
                if(keys[SDL_SCANCODE_F])
                    SetFullScreen();
                if(main_menu.check_play_pressed()){
                    show_main_menu=false;
                    show_select_level=true;
                    continue;
                }
                if(main_menu.check_quit_pressed())
                    goto EXIT;
                main_menu.render();
                SDL_RenderPresent(renderer);
            }
            if(show_menu){
                max_score.save();
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer,background.GetTexture(),NULL,&background_rect);
                menu.render(menu_state);
                SDL_RenderPresent(renderer);
                if(menu_state==false){
                    if(keys[SDL_SCANCODE_RETURN]){
                        show_menu=false;
                        render=true;
                        generate_enemies();
                        spaceship.init_pos();
                        enemy_projectiles.clear();
                        ship_projectiles.clear();
                        ::score=0;
                    }
                    else if(keys[SDL_SCANCODE_M]){
                        show_menu=false;
                        render=true;
                        show_main_menu=true;
                        spaceship.init_pos();
                        enemy_projectiles.clear();
                        ship_projectiles.clear();
                        ::score=0;
                    }
                }
                if(menu_state==true){
                    max_score.save();
                    if(level<50){
                        SDL_Delay(2000);
                        show_menu=false;
                        render=true;
                        generate_enemies();
                        spaceship.init_pos();
                        enemy_projectiles.clear();
                        ship_projectiles.clear();
                        prob_green=std::max(-1,prob_green-5);
                        if(level%3==0)
                            prob_red=std::max(-1,prob_red-5);
                        ++level;
                        previous_time_point=std::chrono::steady_clock::now();
                        time_elapsed=std::chrono::microseconds(0);
                    }else{
                        if(keys[SDL_SCANCODE_M]){
                            show_menu=false;
                            render=true;
                            show_main_menu=true;
                            spaceship.init_pos();
                            enemy_projectiles.clear();
                            ship_projectiles.clear();
                            ::score=0;
                        }
                    }
                }
            }
            if(show_select_level){
                select_level.update();
                select_level.render();
                SDL_RenderPresent(renderer);
                if(keys[SDL_SCANCODE_RETURN]){
                   show_select_level=false; 
                    init_enemies();
                }else if(keys[SDL_SCANCODE_ESCAPE]){
                    show_select_level=false;
                    show_main_menu=true;
                }else if(keys[SDL_SCANCODE_F])
                    SetFullScreen();
            }
        }
    }
EXIT:
    spaceship.destroy();
    enemies_destroy_textures();
    score.destroy();
    main_menu.destroy();
    menu.destroy();
    ufo.destroy();
    select_level.destroy();
    max_score.destroy();
    level_text.destroy();
    Quit();

    return 0;
}
