#ifndef SELECT_LEVEL_HPP
#define SELECT_LEVEL_HPP

#include <text.hpp>
#include <buttons.hpp>

#define TITLE_Y 100

class Select_level{
Button left;
Button right;
Text title;
Text level;
TTF_Font *unispace_40;

public:
    void init();
    void update();
    void render();
    void destroy();
};

#endif