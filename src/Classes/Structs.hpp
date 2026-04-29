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
    Sun sun = Sun();
    Earth earth = Earth();
    Mars mars = Mars();
    Mercury mercury = Mercury();
    Venus venus = Venus();
    Jupiter jupiter = Jupiter();
    Neptune neptune = Neptune();
    Saturn saturn = Saturn();
    Uranus uranus = Uranus();
};

