#pragma once
#include <Renders/RenderSphere.hpp>
#include <Renders/RenderOrbit.hpp>
#include <Planets/Earth/Earth.hpp>
#include <Planets/Sun/Sun.hpp>


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

class Mercury
{
public:
    double x;
    double y;
    double z;
    double vx;
    double vy;
    double vz;
    Mercury();
};

class Venus
{
public:
    double x;
    double y;
    double z;
    double vx;
    double vy;
    double vz;
    Venus();
};

struct RenderMesh
{
    RenderSphere sunSphere;
    RenderSphere earthSphere;
    RenderSphere marsSphere;
    RenderSphere mercurySphere;
    RenderOrbit orbit;
};

struct Orbits
{
    double earthOrbit = 0.0f;
    double marsOrbit = 0.0f;
    double mercuryrbit = 0.0f;
};

struct Planets
{
    IPlanets sun = Sun();
    IPlanets earth = Earth();
    // IPlanets mars = Mars();
    // IPlanets mercury = Mercury();
    // IPlanets venus = Venus();
};

