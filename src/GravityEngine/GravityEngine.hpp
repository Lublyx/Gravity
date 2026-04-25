#pragma once

#include <Classes/Structs.hpp>

void calculPosition(Planets &planets, double deltaT);

void calculOrbit(Planets &planets, double deltaT);

double getAcceleration(double forceVec, double planetM, double deltaT);

double getPlanetSunDistance(double vecX, double vecY, double vecZ);

double getPlanetVectorX(double sunX, double planetX);

double getPlanetVectorY(double sunY, double planetY);

double getPlanetVectorZ(double sunZ, double planetZ);

double getVectorForce(double vector, double r, double planetM);