#include <Classes/Class.hpp>
#include <GravityEngine/GravityEngine.hpp>
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
const double mercuryM = 3.3011e23;
// Masse Mercure

void calculPosition(Planets &planets, double deltaT)
{

    // double E = (0.5 * (earthVelocity * earthVelocity)) - ((G * sunM) / r);
    // E <= 0 if hellipse
    // if (E > 0)
    // {
    //     return;
    // }
    // std::cout << E << std::endl;

    calculPositionEarth(planets.sun, planets.earth, deltaT);

    calculPositionMars(planets.sun, planets.mars, deltaT);

    calculPositionMercury(planets.sun, planets.mercury, deltaT);
}

void calculPositionEarth(Sun &sun, Earth &earth, double deltaT)
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

void getEarthOrbit(Sun &sun, Earth &earth, double deltaT, double &earthOrbit)
{
    double earthBaseX = earth.x;
    double earthBaseY = earth.y;
    double earthBaseZ = earth.z;

    do
    {
        calculPositionEarth(sun, earth, deltaT);
        if (earth.y > earthOrbit) earthOrbit = earth.y;
    } while (earthBaseX != earth.x && earthBaseY != earth.y && earthBaseZ != earth.z);
}

void calculPositionMars(Sun &sun, Mars &mars, double deltaT)
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

void getMarsOrbit(Sun &sun, Mars &mars, double deltaT, double &marsOrbit)
{
    double marsBaseX = mars.x;
    double marsBaseY = mars.y;
    double marsBaseZ = mars.z;

    do
    {
        calculPositionMars(sun, mars, deltaT);
        if (mars.y > marsOrbit) marsOrbit = mars.y;
    } while (marsBaseX != mars.x && marsBaseY != mars.y && marsBaseZ != mars.z);
}

void calculPositionMercury(Sun &sun, Mercury &mercury, double deltaT)
{
    double vecXMercurySun = getPlanetVectorX(sun, mercury.x);
    double vecYMercurySun = getPlanetVectorY(sun, mercury.y);
    double vecZMercurySun = getPlanetVectorZ(sun, mercury.z);

    double r = getPlanetSunDistance(vecXMercurySun, vecYMercurySun, vecZMercurySun);

    double forceVecX = getVectorForce(vecXMercurySun, r, mercuryM);
    double forceVecY = getVectorForce(vecYMercurySun, r, mercuryM);
    double forceVecZ = getVectorForce(vecZMercurySun, r, mercuryM);

    double accelerationMercuryX = getAcceleration(forceVecX, mercuryM);
    double accelerationMercuryY = getAcceleration(forceVecY, mercuryM);
    double accelerationMercuryZ = getAcceleration(forceVecZ, mercuryM);

    mercury.vx += accelerationMercuryX * deltaT;
    mercury.vy += accelerationMercuryY * deltaT;
    mercury.vz += accelerationMercuryZ * deltaT;

    mercury.x += mercury.vx * deltaT;
    mercury.y += mercury.vy * deltaT;
    mercury.z += mercury.vz * deltaT;
}

void getMercuryOrbit(Sun &sun, Mercury &mercury, double deltaT, double &mercuryOrbit)
{
    double mercuryBaseX = mercury.x;
    double mercuryBaseY = mercury.y;
    double mercuryBaseZ = mercury.z;

    do
    {
        calculPositionMercury(sun, mercury, deltaT);
        if (mercury.y > mercuryOrbit) mercuryOrbit = mercury.y;
    } while (mercuryBaseX != mercury.x && mercuryBaseY != mercury.y && mercuryBaseZ != mercury.z);
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