#pragma once

#include "Class.hpp"

void calculePosition(Sun& sun, Earth& earth, Mars& mars, double deltaT);

void calculePositionEarth(Sun &sun, Earth &earth, double deltaT);

void calculePositionMars(Sun &sun, Mars &mars, double deltaT);

double getAcceleration(double forceVec, double planetM);

double getPlanetSunDistance(double vecX, double vecY, double vecZ);

double getPlanetVectorX(Sun &sun, double planetX);

double getPlanetVectorY(Sun &sun, double planetY);

double getPlanetVectorZ(Sun &sun, double planetZ);

double getVectorForce(double vector, double r, double planetM);

