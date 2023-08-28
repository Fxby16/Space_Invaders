#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <SDL2/SDL.h>
#include <chrono>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define PROJECTILE_HEIGHT 20
#define PROJECTILE_WIDTH 4
#define ENEMY_PROJECTILE_SPEED 7
#define PROJECTILE_SPEED 12
#define FPS 60
constexpr std::chrono::microseconds FRAME_TIME(16667);

struct projectile{
int x,y;
};

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern bool fullscreen;
extern bool quit;
extern bool show_main_menu;
extern bool show_menu;
extern bool show_select_level;
extern bool menu_state;
extern SDL_Surface *screenSurface;
extern SDL_Event event;
extern SDL_Texture *projectile_;
extern int score;
extern bool anim;
extern int level;

#endif