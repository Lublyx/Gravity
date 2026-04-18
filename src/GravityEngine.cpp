#include <Class.hpp>
#include <GravityEngine.hpp>
#include <iostream>
#include <cmath>

const double earthVelocity = 29790;
// en m/s
const double G = 6.674e-11;
// constante gravitationel
const double sunM = 1.989e30;
// Masse soleil
const double earthM = 5.972e24;
// Masse Terre
const double marsM = 6.4185e23;
// Masse Mars

void calculePosition(Sun &sun, Earth &earth, Mars &mars, double deltaT)
{

    // double E = (0.5 * (earthVelocity * earthVelocity)) - ((G * sunM) / r);
    // E <= 0 if hellipse
    // if (E > 0)
    // {
    //     return;
    // }
    // std::cout << E << std::endl;

    calculePositionEarth(sun, earth, deltaT);

    calculePositionMars(sun, mars, deltaT);
}

void calculePositionEarth(Sun &sun, Earth &earth, double deltaT)
{
    double vecXEarthSun = getPlanetVectorX(sun, earth.x);
    double vecYEarthSun = getPlanetVectorY(sun, earth.y);
    double vecZEarthSun = getPlanetVectorZ(sun, earth.z);

    double r = getPlanetSunDistance(vecXEarthSun, vecYEarthSun, vecZEarthSun);

    double forceVecX = getVectorForce(vecXEarthSun, r, earthM);
    double forceVecY = getVectorForce(vecYEarthSun, r, earthM);
    double forceVecZ = getVectorForce(vecZEarthSun, r, earthM);

    double accelerationEarthX = getAcceleration(forceVecX, earthM);
    double accelerationEarthY = getAcceleration(forceVecY, earthM);
    double accelerationEarthZ = getAcceleration(forceVecZ, earthM);

    earth.vx += accelerationEarthX * deltaT;
    earth.vy += accelerationEarthY * deltaT;
    earth.vz += accelerationEarthZ * deltaT;

    earth.x += earth.vx * deltaT;
    earth.y += earth.vy * deltaT;
    earth.z += earth.vz * deltaT;
}

void calculePositionMars(Sun &sun, Mars &mars, double deltaT)
{
    double vecXMarsSun = getPlanetVectorX(sun, mars.x);
    double vecYMarsSun = getPlanetVectorY(sun, mars.y);
    double vecZMarsSun = getPlanetVectorZ(sun, mars.z);

    double r = getPlanetSunDistance(vecXMarsSun, vecYMarsSun, vecZMarsSun);

    double forceVecX = getVectorForce(vecXMarsSun, r, marsM);
    double forceVecY = getVectorForce(vecYMarsSun, r, marsM);
    double forceVecZ = getVectorForce(vecZMarsSun, r, marsM);

    double accelerationMarsX = getAcceleration(forceVecX, marsM);
    double accelerationMarsY = getAcceleration(forceVecY, marsM);
    double accelerationMarsZ = getAcceleration(forceVecZ, marsM);

    mars.vx += accelerationMarsX * deltaT;
    mars.vy += accelerationMarsY * deltaT;
    mars.vz += accelerationMarsZ * deltaT;

    mars.x += mars.vx * deltaT;
    mars.y += mars.vy * deltaT;
    mars.z += mars.vz * deltaT;
}

double getAcceleration(double forceVec, double planetM)
{
    return forceVec / planetM;
}

double getPlanetSunDistance(double vecX, double vecY, double vecZ)
{
    // distance soleil - planète
    return sqrt(vecX * vecX + vecY * vecY + vecZ * vecZ);
}

double getPlanetVectorX(Sun &sun, double planetX)
{
    return sun.x - planetX;
}

double getPlanetVectorY(Sun &sun, double planetY)
{
    return sun.y - planetY;
}

double getPlanetVectorZ(Sun &sun, double planetZ)
{
    return sun.z - planetZ;
}

double getVectorForce(double vector, double r, double planetM)
{
    double F = (G * sunM * planetM) / (r * r);
    // std::cout << F << std::endl;

    return F * (vector / r);
}