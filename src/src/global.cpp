#include <SDL2/SDL.h>

SDL_Window *window=NULL;
SDL_Renderer *renderer=NULL;
bool fullscreen=false;
bool quit=false;
bool show_main_menu=true;
bool show_menu=false;
bool show_select_level=false;
bool menu_state;
SDL_Event event;
SDL_Texture *projectile_;
int score=0;
bool anim=false;
int level=0;