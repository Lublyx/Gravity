#include <Planets/IPlanets.hpp>
#include <GravityEngine/GravityEngine.hpp>

void IPlanets::calculPosition(IPlanets &sun, IPlanets &planet, double deltaT)
{
    double vecX = getPlanetVectorX(sun.x, planet.x);
    double vecY = getPlanetVectorY(sun.y, planet.y);
    double vecZ = getPlanetVectorZ(sun.z, planet.z);

    double r = getPlanetSunDistance(vecX, vecY, vecZ);

    double forceVecX = getVectorForce(vecX, r, masse);
    double forceVecY = getVectorForce(vecY, r, masse);
    double forceVecZ = getVectorForce(vecZ, r, masse);

    planet.vx += getAcceleration(forceVecX, masse, deltaT);
    planet.vy += getAcceleration(forceVecY, masse, deltaT);
    planet.vz += getAcceleration(forceVecZ, masse, deltaT);

    planet.x += planet.vx * deltaT;
    planet.y += planet.vy * deltaT;
    planet.z += planet.vz * deltaT;
}

void IPlanets::getOrbit(IPlanets &sun, IPlanets &planet, double deltaT)
{
    double BaseX = planet.x;
    double BaseY = planet.y;
    double BaseZ = planet.z;

    do
    {
        calculPosition(sun, planet, deltaT);
        if (planet.y > orbit)
            orbit = planet.y;
    } while (BaseX != planet.x && BaseY != planet.y && BaseZ != planet.z);
}
