#ifndef TEXT_HPP
#define TEXT_HPP

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <vector>
#include <global.hpp>

struct Text_Texture{
    SDL_Texture *texture;
    SDL_Rect dest;
};

class Text{

Text_Texture t;

public:

    /**
     * \param font font to be used
     * \param color the color of the text
     * \param wrap max length of the text(0 for unlimited)
     * \param string string that contains the text
     * \param x x position of the top left vertex of the rendering square 
     * \param y y position of the top left vertex of the rendering square 
    */
    void create_text(TTF_Font *font,SDL_Color color,Uint32 wrap,const char *string,Uint32 x=0,Uint32 y=0);
    
    /**
     * \returns width and height of the text texture
    */
    std::pair<int,int> get_size();

    /**
     * set x and y coordinates for the text
     * \param x x coordinate
     * \param y y coordinate
    */
    void set_x_y(int x,int y);

    /**
     * \returns x and y coordinates of the text
    */
    std::pair<int,int> get_x_y();

    /**
     * \param tt the portion of texture to be rendered, or NULL for the entire texture
    */
    void render(SDL_Rect *tt); 
    void destroy();
};

#endif