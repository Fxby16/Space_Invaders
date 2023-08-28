#ifndef ENEMIES_HPP
#define ENEMIES_HPP

#include <textures.hpp>
#include <global.hpp>
#include <vector>
#include <chrono>
#define NUM_PROJECTILES 4
#define MS_ENEMY_SHOOT 2000
#define MS_ANIM_TIME 2500
#define ENEMY_WIDTH (12*4)
#define ENEMY_HEIGHT (8*4)
#define ENEMIES_NUMBER 12

enum enemy_type{
    LIGHT_BLUE,RED,GREEN
};

enum Enemy_Movement{
    RIGHT,LEFT
};

struct Enemy{
int x,y;
int type;
};

extern std::vector<projectile>enemy_projectiles;
extern std::vector<std::vector<Enemy>>enemies;
extern std::chrono::steady_clock::time_point enemy_time;
extern std::vector<std::pair<Texture,Texture>>enemies_textures;
extern std::chrono::steady_clock::time_point anim_time;
extern int prob_light_blue;
extern int prob_red;
extern int prob_green;

void init_enemies();
void generate_enemies();
bool count_enemies();
bool check_enemy_pos();
void move_enemies();
void enemies_shoot();
void enemies_update_projectiles();
void check_enemies_collisions();
void render_enemies();
void enemies_render_projectiles();
void enemies_destroy_textures();

#endif