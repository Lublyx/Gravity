#include <Planets/Mercury/Mercury.hpp>

Mercury::Mercury(){
    x = 0.0f;
    y = 5.79e10;
    z = 0.0f;
    vx = 47362;
    vy = 0.0f;
    vz = 0.0f;
    masse = 3.3011e23;
    orbit = 0.0f;
    sphere.init(1.3);
    r = 0.73f;
    g = 0.72f;
    b = 0.75f;
}