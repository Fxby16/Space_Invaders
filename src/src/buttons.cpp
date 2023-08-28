#include <buttons.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void Button::CreateButtonImg(const char *bg_img,const char *bg_img_hover,const char *s,TTF_Font *font,SDL_Color color,int button_x,int button_y,int button_w,int button_h){
SDL_Surface *sf;

    type=IMG;

    button_rect.h=button_h;
    button_rect.w=button_w;
    button_rect.x=button_x;
    button_rect.y=button_y;

    sf=IMG_Load(bg_img);
    bg=SDL_CreateTextureFromSurface(renderer,sf);
    SDL_FreeSurface(sf);

    sf=IMG_Load(bg_img_hover);
    bg_hover=SDL_CreateTextureFromSurface(renderer,sf);
    SDL_FreeSurface(sf);

    if(s!=NULL){
        sf=TTF_RenderUTF8_Blended_Wrapped(font,s,color,0);
        text.dest.w=sf->w;
        text.dest.h=sf->h;
        text.dest.x=button_x+((button_w-sf->w>=0)?(button_w-sf->w)/2:0);
        text.dest.y=button_y+((button_h-sf->h>=0)?(button_h-sf->h)/2:0);
        text.texture=SDL_CreateTextureFromSurface(renderer,sf);
        SDL_FreeSurface(sf);
    }else{
        text.texture=NULL;
    }  
}

void Button::CreateButtonSolid(SDL_Color bg_color,SDL_Color bg_color_hover,const char *s,TTF_Font *font,SDL_Color color,int button_x,int button_y,int button_w,int button_h,bool Border,SDL_Color Border_color){
SDL_Surface *sf;

    type=COLOR;
    if(Border){
        border=Border;
        border_color=Border_color;
    }

    button_rect.h=button_h;
    button_rect.w=button_w;
    button_rect.x=button_x;
    button_rect.y=button_y;

    bg_c=bg_color;
    bg_c_hover=bg_color_hover;

    sf=TTF_RenderUTF8_Blended_Wrapped(font,s,color,0);
    text.dest.w=sf->w;
    text.dest.h=sf->h;
    text.dest.x=button_x+((button_w-sf->w>=0)?(button_w-sf->w)/2:0);
    text.dest.y=button_y+((button_h-sf->h>=0)?(button_h-sf->h)/2:0);
    text.texture=SDL_CreateTextureFromSurface(renderer,sf);
    SDL_FreeSurface(sf);
}

void Button::Set_X_Y(int x,int y){
    button_rect.x=x;
    button_rect.y=y;
}

void Button::Destroy(){
    if(text.texture!=NULL)
        SDL_DestroyTexture(text.texture);
    if(type==IMG){
        SDL_DestroyTexture(bg);
        SDL_DestroyTexture(bg_hover);
    }
}

bool Button::CheckPressedHover(){
int x,y;
    Uint32 buttons=SDL_GetMouseState(&x,&y);

    if((x>=button_rect.x && x<=button_rect.x+button_rect.w) && (y>=button_rect.y && y<=button_rect.y+button_rect.h)){
        hover=true;
        if(buttons==SDL_BUTTON_LEFT && !pressed)
            pressed=true;
    }else
        hover=false;

    if((buttons & SDL_BUTTON_LEFT)==0 && pressed){
        pressed=false;
        if(hover)
            return true;
        else 
            return false;
    }
    
    return false;
}

void Button::Render(){
    if(type==IMG){
        if(hover)
            SDL_RenderCopy(renderer,bg_hover,NULL,&button_rect);
        else
            SDL_RenderCopy(renderer,bg,NULL,&button_rect);
    }else if(type==COLOR){
        if(hover){
            SDL_SetRenderDrawColor(renderer,bg_c_hover.r,bg_c_hover.g,bg_c_hover.b,bg_c_hover.a);
            SDL_RenderFillRect(renderer,&button_rect);
        }else{
            SDL_SetRenderDrawColor(renderer,bg_c.r,bg_c.g,bg_c.b,bg_c.a);
            SDL_RenderFillRect(renderer,&button_rect);
        }
    }
    if(border){
        SDL_SetRenderDrawColor(renderer,border_color.r,border_color.g,border_color.b,border_color.a);
        SDL_RenderDrawRect(renderer,&button_rect);
    }
    if(text.texture!=NULL)
        SDL_RenderCopy(renderer,text.texture,NULL,&text.dest);
}