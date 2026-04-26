#pragma once
#include <Planets/Earth/Earth.hpp>
#include <Planets/Sun/Sun.hpp>
#include <Planets/Mars/Mars.hpp>
#include <Planets/Mercury/Mercury.hpp>
#include <Planets/Venus/Venus.hpp>
#include <Planets/Jupiter/Jupiter.hpp>
#include <Planets/Neptune/Neptune.hpp>
#include <Planets/Saturn/Saturn.hpp>
#include <Planets/Uranus/Uranus.hpp>

struct Planets
{
    IPlanets sun = Sun();
    IPlanets earth = Earth();
    IPlanets mars = Mars();
    IPlanets mercury = Mercury();
    IPlanets venus = Venus();
    IPlanets jupiter = Jupiter();
    IPlanets neptune = Neptune();
    IPlanets saturn = Saturn();
    IPlanets uranus = Uranus();
};

