#pragma once

#include <Classes/Class.hpp>

void calculPosition(Planets &planets, double deltaT);

void calculPositionEarth(Sun &sun, Earth &earth, double deltaT);

void getEarthOrbit(Sun &sun, Earth &earth, double deltaT, double &earthOrbit);

void calculPositionMars(Sun &sun, Mars &mars, double deltaT);

void getMarsOrbit(Sun &sun, Mars &mars, double deltaT, double &earthOrbit);

double getAcceleration(double forceVec, double planetM, double deltaT);

double getPlanetSunDistance(double vecX, double vecY, double vecZ);

double getPlanetVectorX(double sunX, double planetX);

double getPlanetVectorY(double sunY, double planetY);

double getPlanetVectorZ(double sunZ, double planetZ);

double getVectorForce(double vector, double r, double planetM);

void calculPositionMercury(Sun &sun, Mercury &mercury, double deltaT);

void getMercuryOrbit(Sun &sun, Mercury &mercury, double deltaT, double &mercuryOrbit);