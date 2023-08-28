#include <score.hpp>
#include <string>

void Score::init(){
    font=TTF_OpenFont("fonts/unispace_bd.otf",35);
    score.create_text(font,{255,255,255,0},0,"Score:",SCORE_X,SCORE_Y);
    number.create_text(font,{255,255,255,0},0,"0",SCORE_X+score.get_size().first+10,SCORE_Y);
}

void Score::set_x_y(int x,int y){
    score.set_x_y(x,y);
    number.set_x_y(score.get_x_y().first+score.get_size().first+10,score.get_x_y().second);
}

int Score::width(){
    return score.get_size().first+10+number.get_size().first;
}

void Score::update(){
    number.destroy();
    number.create_text(font,{255,255,255,0},0,std::to_string(::score).c_str(),number.get_x_y().first,number.get_x_y().second);
}

void Score::render(){
    score.render(NULL);
    number.render(NULL);
}

void Score::destroy(){
    score.destroy();
    number.destroy();
    TTF_CloseFont(font);
}