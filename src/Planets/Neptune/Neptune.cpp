#include <Planets/Neptune/Neptune.hpp>

Neptune::Neptune(){
    x = 0.0f;
    y = 4.537e12;
    z = 0.0f;
    vx = 5386.1;
    vy = 0.0f;
    masse = 1.0243e26;
    sphereSize = 7;
    orbit = 0.0f;
    r = 0.44f;
    g = 0.46f;
    b = 0.83f;
    angle = 1.77;
    vz = vx * sin(glm::radians(angle));
}