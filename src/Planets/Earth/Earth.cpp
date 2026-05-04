#include <Planets/Earth/Earth.hpp>

Earth::Earth()
{
    x = 0.0f;
    y = 1.520977e11;
    z = 0.0f;
    vx = 29291;
    vy = 0.0;
    masse = 5.972e24;
    orbit = 0.0f;
    sphereSize = 3;
    r = 0.20f;
    g = 0.65f;
    b = 0.89f;
    angle = 0;
    vz = vx * sin(glm::radians(angle));
}
