#pragma once

class IPlanets
{
public:
    double x;
    double y;
    double z;
    double vx;
    double vy;
    double vz;
    double masse;
    double orbit;

    virtual void calculPosition(IPlanets &sun, IPlanets &planet, double deltaT);
    virtual void getOrbit(IPlanets &sun, IPlanets &planet, double deltaT);
};