#include <level.hpp>
#include <string>
#include <global.hpp>

void Level::init(){
    font=TTF_OpenFont("fonts/unispace_bd.otf",35);
    text.create_text(font,{255,255,255,0},0,"Level:");
    num.create_text(font,{255,255,255,0},0,std::to_string(level).c_str());
    text.set_x_y(WINDOW_WIDTH/2-(text.get_size().first+10+num.get_size().first)/2,LEVEL_Y);
    num.set_x_y(text.get_x_y().first+10+text.get_size().first,LEVEL_Y);
}

void Level::update(){
num.destroy();
    num.create_text(font,{255,255,255,0},0,std::to_string(level).c_str());
    text.set_x_y(WINDOW_WIDTH/2-(text.get_size().first+10+num.get_size().first)/2,LEVEL_Y);
    num.set_x_y(text.get_x_y().first+10+text.get_size().first,LEVEL_Y);
}

void Level::render(){
    text.render(NULL);
    num.render(NULL);
}

void Level::destroy(){
    text.destroy();
    num.destroy();
    TTF_CloseFont(font);
}