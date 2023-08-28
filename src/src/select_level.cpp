#include <select_level.hpp>
#include <string>
#include <enemies.hpp>
#include <iostream>

void Select_level::init(){
    unispace_40=TTF_OpenFont("fonts/unispace_bd.otf",40);
    title.create_text(unispace_40,{255,255,255,0},0,"Select Level");
    title.set_x_y(WINDOW_WIDTH/2-title.get_size().first/2,TITLE_Y);
    level.create_text(unispace_40,{255,255,255,0},0,std::to_string(::level).c_str());
    level.set_x_y(WINDOW_WIDTH/2-level.get_size().first/2,TITLE_Y+title.get_size().second+50);
    left.CreateButtonImg("img/left_arrow.png","img/left_arrow.png",NULL,NULL,{0,0,0,0},level.get_x_y().first-level.get_size().second,level.get_x_y().second,level.get_size().second,level.get_size().second);
    right.CreateButtonImg("img/right_arrow.png","img/right_arrow.png",NULL,NULL,{0,0,0,0},level.get_x_y().first+level.get_size().first,level.get_x_y().second,level.get_size().second,level.get_size().second);
    ::level=1;
    prob_green=prob_red=prob_light_blue=100;
}

void Select_level::update(){
    if(left.CheckPressedHover()){
        ::level=std::max(1,::level-1);
        prob_green=std::min(100,prob_green+5);
        if(::level%3==0)
            prob_red=std::min(100,prob_red+5);
    }
    if(right.CheckPressedHover()){
        ::level=std::min(::level+1,50);
        prob_green=std::max(-1,prob_green-5);
        if(::level%3==0)
            prob_red=std::max(-1,prob_red-5);
    }
    level.destroy();
    level.create_text(unispace_40,{255,255,255,0},0,std::to_string(::level).c_str());
    level.set_x_y(WINDOW_WIDTH/2-level.get_size().first/2,TITLE_Y+title.get_size().second+50);
    left.Set_X_Y(level.get_x_y().first-level.get_size().second,level.get_x_y().second);
    right.Set_X_Y(level.get_x_y().first+level.get_size().first,level.get_x_y().second);
}

void Select_level::render(){
    SDL_SetRenderDrawColor(renderer,0,0,0,0);
    SDL_RenderClear(renderer);
    update();
    title.render(NULL);
    level.render(NULL);
    left.Render();
    right.Render();
}

void Select_level::destroy(){
    title.destroy();
    level.destroy();
    left.Destroy();
    right.Destroy();
    TTF_CloseFont(unispace_40);
}