#ifndef SCORE_HPP
#define SCORE_HPP

#include <text.hpp>
#include <SDL2/SDL_ttf.h>

#define SCORE_X 20
#define SCORE_Y 10

class Score{
Text score;
Text number;
TTF_Font *font;
public:
    void init();
    void set_x_y(int x,int y);
    int width();
    void update();
    void render();
    void destroy();
};

#endif