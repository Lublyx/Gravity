#include <Classes/Class.hpp>
#include <GravityEngine/GravityEngine.hpp>
#include <Planets/Earth/Earth.hpp>
#include <iostream>
#include <cmath>

const double G = 6.674e-11;
// constante gravitationel
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

    planets.earth.calculPosition(planets.sun, planets.earth, deltaT);

    // planets. calculPositionMars(planets.sun, planets.mars, deltaT);

    // calculPositionMercury(planets.sun, planets.mercury, deltaT);
}



// void calculPositionMars(IPlanets &sun, IPlanets &mars, double deltaT)
// {
//     double vecXMarsSun = getPlanetVectorX(sun, mars.x);
//     double vecYMarsSun = getPlanetVectorY(sun, mars.y);
//     double vecZMarsSun = getPlanetVectorZ(sun, mars.z);

//     double r = getPlanetSunDistance(vecXMarsSun, vecYMarsSun, vecZMarsSun);

//     double forceVecX = getVectorForce(vecXMarsSun, r, marsM);
//     double forceVecY = getVectorForce(vecYMarsSun, r, marsM);
//     double forceVecZ = getVectorForce(vecZMarsSun, r, marsM);

//     mars.vx += getAcceleration(forceVecX, marsM, deltaT);
//     mars.vy += getAcceleration(forceVecY, marsM, deltaT);
//     mars.vz += getAcceleration(forceVecZ, marsM, deltaT);

//     mars.x += mars.vx * deltaT;
//     mars.y += mars.vy * deltaT;
//     mars.z += mars.vz * deltaT;
// }

// void getMarsOrbit(IPlanets &sun, IPlanets &mars, double deltaT, double &marsOrbit)
// {
//     double marsBaseX = mars.x;
//     double marsBaseY = mars.y;
//     double marsBaseZ = mars.z;

//     do
//     {
//         calculPositionMars(sun, mars, deltaT);
//         if (mars.y > marsOrbit) marsOrbit = mars.y;
//     } while (marsBaseX != mars.x && marsBaseY != mars.y && marsBaseZ != mars.z);
// }

// void calculPositionMercury(IPlanets &sun, IPlanets &mercury, double deltaT)
// {
//     double vecXMercurySun = getPlanetVectorX(sun, mercury.x);
//     double vecYMercurySun = getPlanetVectorY(sun, mercury.y);
//     double vecZMercurySun = getPlanetVectorZ(sun, mercury.z);

//     double r = getPlanetSunDistance(vecXMercurySun, vecYMercurySun, vecZMercurySun);

//     double forceVecX = getVectorForce(vecXMercurySun, r, mercuryM);
//     double forceVecY = getVectorForce(vecYMercurySun, r, mercuryM);
//     double forceVecZ = getVectorForce(vecZMercurySun, r, mercuryM);

//     mercury.vx += getAcceleration(forceVecX, mercuryM, deltaT);
//     mercury.vy += getAcceleration(forceVecY, mercuryM, deltaT);
//     mercury.vz += getAcceleration(forceVecZ, mercuryM, deltaT);

//     mercury.x += mercury.vx * deltaT;
//     mercury.y += mercury.vy * deltaT;
//     mercury.z += mercury.vz * deltaT;
// }

// void getMercuryOrbit(IPlanets &sun, IPlanets &mercury, double deltaT, double &mercuryOrbit)
// {
//     double mercuryBaseX = mercury.x;
//     double mercuryBaseY = mercury.y;
//     double mercuryBaseZ = mercury.z;

//     do
//     {
//         calculPositionMercury(sun, mercury, deltaT);
//         if (mercury.y > mercuryOrbit) mercuryOrbit = mercury.y;
//     } while (mercuryBaseX != mercury.x && mercuryBaseY != mercury.y && mercuryBaseZ != mercury.z);
// }

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