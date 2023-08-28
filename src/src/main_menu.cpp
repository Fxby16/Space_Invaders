#include <main_menu.hpp>
#include <global.hpp>

void MainMenu::init(){
    title_font=TTF_OpenFont("fonts/unispace_bd.otf",55);
    buttons_font=TTF_OpenFont("fonts/unispace_bd.otf",25);
    play.CreateButtonSolid({0,0,0,0},{25,25,25,0},"Play",buttons_font,{255,255,255,0},WINDOW_WIDTH/2-BUTTONS_WIDTH/2,WINDOW_HEIGHT/2-BUTTONS_HEIGHT,BUTTONS_WIDTH,BUTTONS_HEIGHT,true,{255,255,255,0});
    quit.CreateButtonSolid({0,0,0,0},{25,25,25,0},"Quit",buttons_font,{255,255,255,0},WINDOW_WIDTH/2-BUTTONS_WIDTH/2,WINDOW_HEIGHT/2-BUTTONS_HEIGHT+BUTTONS_HEIGHT*1.5,BUTTONS_WIDTH,BUTTONS_HEIGHT,true,{255,255,255,0});
    title.create_text(title_font,{255,255,255,0},0,"Space Invaders");
    title.set_x_y(WINDOW_WIDTH/2-title.get_size().first/2,100);
}

bool MainMenu::check_play_pressed(){
    return play.CheckPressedHover();
}

bool MainMenu::check_quit_pressed(){
    return quit.CheckPressedHover();
}


void MainMenu::render(){
    SDL_SetRenderDrawColor(renderer,0,0,0,0);
    SDL_RenderClear(renderer);
    title.render(NULL);
    play.Render();
    quit.Render();
}

void MainMenu::destroy(){
    title.destroy();
    play.Destroy();
    quit.Destroy();
    TTF_CloseFont(title_font);
    TTF_CloseFont(buttons_font);
}