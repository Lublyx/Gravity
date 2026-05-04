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
#include <vector>
#include <iostream>

enum PlanetsSelection
{
    eSun,
    eMercury,
    eVenus,
    eEarth,
    eMars,
    eJupiter,
    eSaturn,
    eUranus,
    eNeptune,
};

struct Planets
{
private:
    std::vector<IPlanets> planets = {Sun(), Mercury(), Venus(), Earth(), Mars(), Jupiter(), Saturn(), Uranus(), Neptune()};
    size_t cpt = 0;

public:
    IPlanets sun = planets[eSun];
    IPlanets mercury = planets[eMercury];
    IPlanets venus = planets[eVenus];
    IPlanets earth = planets[eEarth];
    IPlanets mars = planets[eMars];
    IPlanets jupiter = planets[eJupiter];
    IPlanets saturn = planets[eSaturn];
    IPlanets uranus = planets[eUranus];
    IPlanets neptune = planets[eNeptune];
    IPlanets currentPlanet = planets[eSun];

    void Next()
    {
        currentPlanet = cpt < planets.size() - 1 ? planets[++cpt] : planets[cpt];
    }

    void Previous()
    {
        currentPlanet = cpt > (size_t)0 ? planets[--cpt] : planets[cpt];
    }

    void Update()
    {
        planets[eSun] = sun;
        planets[eMercury] = mercury;
        planets[eVenus] = venus;
        planets[eEarth] = earth;
        planets[eMars] = mars;
        planets[eJupiter] = jupiter;
        planets[eSaturn] = saturn;
        planets[eUranus] = uranus;
        planets[eNeptune] = neptune;
        currentPlanet = planets[cpt];
    }

    void Reset()
    {
        currentPlanet = planets[eSun];
        cpt = 0;
    }

    void Init()
    {
        sun.init();
        mercury.init();
        venus.init();
        earth.init();
        mars.init();
        jupiter.init();
        saturn.init();
        uranus.init();
        neptune.init();
    }
};
