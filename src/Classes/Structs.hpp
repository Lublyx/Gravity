#pragma once
#include <Planets/Earth/Earth.hpp>
#include <Planets/Sun/Sun.hpp>
#include <Planets/Mars/Mars.hpp>
#include <Planets/Mercury/Mercury.hpp>
#include <Planets/Venus/Venus.hpp>

struct Planets
{
    IPlanets sun = Sun();
    IPlanets earth = Earth();
    IPlanets mars = Mars();
    IPlanets mercury = Mercury();
    IPlanets venus = Venus();
};

