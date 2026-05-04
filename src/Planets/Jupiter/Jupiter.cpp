#include <Planets/Jupiter/Jupiter.hpp>

Jupiter::Jupiter(){
    x = 0.0f;
    y = 8.16e11;
    z = 0.0f;
    vx = 12448;
    vy = 0.0f;
    masse = 1.8986e27;
    sphereSize = 10;
    orbit = 0.0f;
    r = 0.97f;
    g = 0.57f;
    b = 0.17f;
    angle = 1.304;
    vz = vx * sin(glm::radians(angle));
}