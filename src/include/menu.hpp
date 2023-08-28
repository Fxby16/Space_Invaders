#ifndef MENU_HPP
#define MENU_HPP

#include <text.hpp>
#include <score.hpp>

class Menu{
Text lost;
Text won;
Score final_score;
TTF_Font *font;

public:
    void init();
    void render(bool state);
    void destroy();
};

#endif