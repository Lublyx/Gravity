#include <Planets/Neptune/Neptune.hpp>

Neptune::Neptune(){
    x = 0.0f;
    y = 4.4984e12;
    z = 0.0f;
    vx = 5432.48;
    vy = 0.0f;
    vz = 0.0f;
    masse = 1.0243e26;
    sphere.init(7);
    orbit = 0.0f;
    r = 0.44f;
    g = 0.46f;
    b = 0.83f;
}