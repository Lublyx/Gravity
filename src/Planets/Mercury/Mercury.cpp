#include <Planets/Mercury/Mercury.hpp>

Mercury::Mercury(){
    x = 0.0f;
    y = 6.98169e10;
    z = 0.0f;
    vx = 38860;
    vy = 0.0f;
    masse = 3.3011e23;
    orbit = 0.0f;
    sphereSize = 1.3;
    r = 0.73f;
    g = 0.72f;
    b = 0.75f;
    angle = 7.00;
    vz = vx * sin(glm::radians(angle));
}