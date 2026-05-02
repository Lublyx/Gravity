#include <Planets/Uranus/Uranus.hpp>

Uranus::Uranus(){
    x = 0.0f;
    y = 2.8707e12;
    z = 0.0f;
    vx = 6796.732;
    vy = 0.0f;
    masse = 8.6810e25;
    sphereSize = 6;
    orbit = 0.0f;
    r = 0.40f;
    g = 0.80f;
    b = 0.81f;
    angle = 0.77323;
    vz = vx * sin(glm::radians(angle));
}