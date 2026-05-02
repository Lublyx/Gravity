#include <Planets/Saturn/Saturn.hpp>

Saturn::Saturn(){
    x = 0.0f;
    y = 1.4267e12;
    z = 0.0f;
    vx = 9640.7;
    vy = 0.0f;
    masse = 5.6846e26;
    sphereSize = 12;
    orbit = 0.0f;
    r = 0.98f;
    g = 0.90f;
    b = 0.56f;
    angle = 2.486;
    vz = vx * sin(glm::radians(angle));
}