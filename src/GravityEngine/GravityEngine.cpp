#include <Classes/Structs.hpp>
#include <GravityEngine/GravityEngine.hpp>
#include <iostream>
#include <cmath>

const double G = 6.674e-11;
// constante gravitationel

void calculPosition(Planets &planets, double deltaT)
{

    // double E = (0.5 * (earthVelocity * earthVelocity)) - ((G * sunM) / r);
    // E <= 0 if hellipse
    // if (E > 0)
    // {
    //     return;
    // }
    // std::cout << E << std::endl;

    planets.earth.calculPosition(planets.sun, planets.earth, deltaT);
    planets.mars.calculPosition(planets.sun, planets.mars, deltaT);
    planets.mercury.calculPosition(planets.sun, planets.mercury, deltaT);
    planets.venus.calculPosition(planets.sun, planets.venus, deltaT);
    planets.saturn.calculPosition(planets.sun, planets.saturn, deltaT);
    planets.neptune.calculPosition(planets.sun, planets.neptune, deltaT);
    planets.jupiter.calculPosition(planets.sun, planets.jupiter, deltaT);
    planets.uranus.calculPosition(planets.sun, planets.uranus, deltaT);
}

void calculOrbit(Planets &planets, double deltaT)
{
    planets.earth.getOrbit(planets.sun, planets.earth, deltaT);
    planets.mars.getOrbit(planets.sun, planets.mars, deltaT);
    planets.mercury.getOrbit(planets.sun, planets.mercury, deltaT);
    planets.venus.getOrbit(planets.sun, planets.venus, deltaT);
    planets.saturn.getOrbit(planets.sun, planets.saturn, deltaT);
    planets.neptune.getOrbit(planets.sun, planets.neptune, deltaT);
    planets.jupiter.getOrbit(planets.sun, planets.jupiter, deltaT);
    planets.uranus.getOrbit(planets.sun, planets.uranus, deltaT);
}

double getAcceleration(double forceVec, double planetM, double deltaT)
{
    return forceVec / planetM * deltaT;
}

double getPlanetSunDistance(double vecX, double vecY, double vecZ)
{
    // distance soleil - planète
    return sqrt(vecX * vecX + vecY * vecY + vecZ * vecZ);
}

double getPlanetVectorX(double sunX, double planetX)
{
    return sunX - planetX;
}

double getPlanetVectorY(double sunY, double planetY)
{
    return sunY - planetY;
}

double getPlanetVectorZ(double sunZ, double planetZ)
{
    return sunZ - planetZ;
}

double getVectorForce(double vector, double r, double planetM)
{
    const double sunM = 1.989e30;
    double F = (G * sunM * planetM) / (r * r);
    // std::cout << F << std::endl;

    return F * (vector / r);
}