#pragma once
#include <RenderSphere.hpp>
#include <RenderOrbit.hpp>

class Sun
{
public:
    double x;
    double y;
    double z;
    Sun();
};

class Earth
{
public:
    double x;
    double y;
    double z;
    double vx;
    double vy;
    double vz;
    Earth();
};

class Mars
{
public:
    double x;
    double y;
    double z;
    double vx;
    double vy;
    double vz;
    Mars();
};

struct RenderMesh
{
    RenderSphere sunSphere;
    RenderSphere earthSphere;
    RenderSphere marsSphere;
    RenderOrbit orbit;
};

struct Orbits
{
    double earthOrbit = 0.0f;
    double marsOrbit = 0.0f;
};

struct Planets
{
    Sun sun;
    Earth earth;
    Mars mars;
};

