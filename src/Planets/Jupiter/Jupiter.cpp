#include <Planets/Jupiter/Jupiter.hpp>

Jupiter::Jupiter(){
    x = 0.0f;
    y = 7.7834e11;
    z = 0.0f;
    vx = 13058.5;
    vy = 0.0f;
    vz = 0.0f;
    masse = 1.8986e27;
    sphere.init(10);
    orbit = 0.0f;
    r = 0.97f;
    g = 0.57f;
    b = 0.17f;
}