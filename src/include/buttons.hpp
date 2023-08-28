#ifndef BUTTONS_HPP
#define BUTTONS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <text.hpp>
#include <textures.hpp>

class Button{
SDL_Texture *bg;
SDL_Texture *bg_hover;
SDL_Color bg_c;
SDL_Color bg_c_hover;
Text_Texture text;
SDL_Rect button_rect;
enum button_type{
    NONE,IMG,COLOR
}type=NONE;
bool border=false;
SDL_Color border_color;
bool hover=false;
bool pressed=false;

public:

    /**
     * \param bg_img path to the background image
     * \param bg_img_hover path to the background image to display when the cursor is on the button
     * \param s text contained in the button
     * \param font the font of the text
     * \param color the color of the text
     * \param button_x the x coordinate where the button should be rendered
     * \param button_y the y coordinate where the button should be rendered
     * \param button_w button width
     * \param button_h button height
    */
    void CreateButtonImg(const char *bg_img,const char *bg_img_hover,const char *s,TTF_Font *font,SDL_Color color,int button_x,int button_y,int button_w,int button_h);

    /**
     * \param bg_color the background color
     * \param bg_img_hover the background color to display when the cursor is on the button
     * \param s text contained in the button
     * \param font the font of the text
     * \param color the color of the text
     * \param button_x the x coordinate where the button should be rendered
     * \param button_y the y coordinate where the button should be rendered
     * \param button_w button width
     * \param button_h button height
     * \param Border true if you want the border (optional)
     * \param Border_color the color of the border (required if you set Border to true)
    */
    void CreateButtonSolid(SDL_Color bg_color,SDL_Color bg_color_hover,const char *s,TTF_Font *font,SDL_Color color,int button_x,int button_y,int button_w,int button_h,bool Border=false,SDL_Color Border_color={0,0,0,0});

    void Set_X_Y(int x,int y);

    void Destroy();

    /**
     * check if the cursor is on the button and if the button has been pressed with the left mouse button
     * \returns true if the button has been pressed, false otherwise
    */
    bool CheckPressedHover();

    void Render();
};


#endif