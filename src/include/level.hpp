#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <text.hpp>

#define LEVEL_Y 10

class Level{
Text text;
Text num;
TTF_Font *font;

public:
    void init();
    void update();
    void render();
    void destroy();
};

#endif