#include <max_score.hpp>
#include <stdio.h>
#include <string>

void Max_score::init(){
FILE *fp=fopen("./max_score.txt","r");
    font=TTF_OpenFont("fonts/unispace_bd.otf",35);
    if(fp==NULL){
        num.create_text(font,{255,255,255,0},0,"0");
        n=0;
    }else{
        fscanf(fp,"%d",&n);
        num.create_text(font,{255,255,255,0},0,std::to_string(n).c_str());
    }
    text.create_text(font,{255,255,255,0},0,"Max Score:");
    fclose(fp);

    text.set_x_y(WINDOW_WIDTH-20-(text.get_size().first+10+num.get_size().first)/2,MAX_SCORE_Y);
    num.set_x_y(text.get_x_y().first+text.get_size().first+10,MAX_SCORE_Y);
}

void Max_score::update(){
n=std::max(n,::score);
    num.destroy();
    num.create_text(font,{255,255,255,0},0,std::to_string(n).c_str());
    text.set_x_y(WINDOW_WIDTH-20-(text.get_size().first+10+num.get_size().first),MAX_SCORE_Y);
    num.set_x_y(text.get_x_y().first+text.get_size().first+10,MAX_SCORE_Y);
}

void Max_score::save(){
FILE *fp=fopen("./max_score.txt","w");
    fprintf(fp,"%d",std::max(::score,n));
    fclose(fp);
}

void Max_score::render(){
    text.render(NULL);
    num.render(NULL);
}

void Max_score::destroy(){
    text.destroy();
    num.destroy();
    TTF_CloseFont(font);
}