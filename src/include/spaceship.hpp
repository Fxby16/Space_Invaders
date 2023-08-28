#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP

#include <textures.hpp>
#include <global.hpp>
#include <vector>
#include <chrono>

extern std::vector<projectile>ship_projectiles;

#define SHIP_SPEED 8
#define SHIP_WIDTH (30*3)
#define SHIP_HEIGHT (26*3)
#define SPACESHIP_SHOOT_TIME 750

class Spaceship{
Texture spaceship;
int x,y;
SDL_Rect upper_hitbox;
SDL_Rect lower_hitbox;
std::chrono::steady_clock::time_point time;

public:
    void init();
    void init_pos();
    void move();
    void shoot();
    void update_projectiles();
    bool check_collision();
    void render_projectiles();
    void render_ship();
    void destroy();
};

#endif