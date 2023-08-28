#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <text.hpp>
#include <buttons.hpp>
#define BUTTONS_WIDTH 250
#define BUTTONS_HEIGHT 120

class MainMenu{
TTF_Font *title_font;
TTF_Font *buttons_font;
Text title;
Button play;
Button quit;

public:
    void init();
    bool check_play_pressed();
    bool check_quit_pressed();
    void render();
    void destroy();
};

#endif