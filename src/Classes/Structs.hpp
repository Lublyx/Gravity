#pragma once
#include <Renders/RenderSphere.hpp>
#include <Renders/RenderOrbit.hpp>
#include <Planets/Earth/Earth.hpp>
#include <Planets/Sun/Sun.hpp>
#include <Planets/Mars/Mars.hpp>
#include <Planets/Mercury/Mercury.hpp>
#include <Planets/Venus/Venus.hpp>

struct RenderMesh
{
    RenderSphere sunSphere;
    RenderSphere earthSphere;
    RenderSphere marsSphere;
    RenderSphere mercurySphere;
    RenderSphere venusSphere;
    RenderOrbit orbit;
};

struct Planets
{
    IPlanets sun = Sun();
    IPlanets earth = Earth();
    IPlanets mars = Mars();
    IPlanets mercury = Mercury();
    IPlanets venus = Venus();
};

