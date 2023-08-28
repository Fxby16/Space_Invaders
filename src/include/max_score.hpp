#ifndef MAX_SCORE_HPP
#define MAX_SCORE_HPP

#include <text.hpp>

#define MAX_SCORE_Y 10

class Max_score{
Text text;
Text num;
TTF_Font *font;
int n;

public:
    void init();
    void update();
    void save();
    void render();
    void destroy();
};

#endif