#include <Class.hpp>
#include <GravityEngine.hpp>
#include <iostream>
#include <cmath>

const int velocityScale = 100000;
const double earthVelocity = 29790;
// en m/s
const double G = 6.674e-11;
// constante gravitationel
const double sunM = 1.989e30;
// Masse soleil
const double earthM = 5.972e24;

void calculePosition(Sun &sun, Earth &earth)
{
    
    double vecXEarthSun = sun.x - earth.x;
    double vecYEarthSun = sun.y - earth.y;
    double vecZEarthSun = sun.z - earth.z;
    
    double r = sqrt(vecXEarthSun*vecXEarthSun + vecYEarthSun*vecYEarthSun + vecZEarthSun*vecZEarthSun);
    
    double E = (0.5 * (earthVelocity*earthVelocity)) - ((G*sunM) / r);

    if (E > 0){
        return;
    }
    // std::cout << E << std::endl;

    double F = (G * sunM * earthM) / (r*r);
    std::cout << F << std::endl;


}