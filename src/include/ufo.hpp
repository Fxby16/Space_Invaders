#ifndef UFO_HPP
#define UFO_HPP

#include <textures.hpp>
#include <chrono>

#define UFO_SPEED 6
#define UFO_WIDTH (24*3)
#define UFO_HEIGHT (14*3)

constexpr std::chrono::milliseconds UFO_TIME=std::chrono::milliseconds(15000);
extern std::chrono::steady_clock::time_point ufo_time;

class Ufo{
Texture ufo;
int x,y;
public:
    void init();
    void update();
    void check_collisions();
    void render();
    void destroy();
};

#endif