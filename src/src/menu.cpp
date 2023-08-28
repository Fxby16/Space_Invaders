#include <menu.hpp>

void Menu::init(){
    font=TTF_OpenFont("fonts/unispace_bd.otf",55);
    won.create_text(font,{255,255,255,0},0,"You won");
    won.set_x_y(WINDOW_WIDTH/2-won.get_size().first/2,WINDOW_HEIGHT/2-won.get_size().second);

    lost.create_text(font,{255,255,255,0},0,"You lost");
    lost.set_x_y(WINDOW_WIDTH/2-lost.get_size().first/2,WINDOW_HEIGHT/2-lost.get_size().second);

    final_score.init();
    final_score.set_x_y(WINDOW_WIDTH/2-final_score.width()/2,won.get_x_y().second+won.get_size().second+20);
}

void Menu::render(bool state){
    if(state)
        won.render(NULL);
    else if(!state)
        lost.render(NULL);
    final_score.update();
    final_score.set_x_y(WINDOW_WIDTH/2-final_score.width()/2,won.get_x_y().second+won.get_size().second+20);
    final_score.render();
}

void Menu::destroy(){
    won.destroy();
    lost.destroy();
    final_score.destroy();
    TTF_CloseFont(font);
}