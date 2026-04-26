#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Renders/RenderSphere.hpp>
#include <Renders/RenderOrbit.hpp>
#include <Planets/IPlanets.hpp>
#include <GravityEngine/GravityEngine.hpp>

IPlanets::IPlanets(){
    orbitToRender.init();
}

void IPlanets::calculPosition(IPlanets &sun, IPlanets &planet, double deltaT)
{
    double vecX = getPlanetVectorX(sun.x, planet.x);
    double vecY = getPlanetVectorY(sun.y, planet.y);
    double vecZ = getPlanetVectorZ(sun.z, planet.z);

    double r = getPlanetSunDistance(vecX, vecY, vecZ);

    double forceVecX = getVectorForce(vecX, r, masse);
    double forceVecY = getVectorForce(vecY, r, masse);
    double forceVecZ = getVectorForce(vecZ, r, masse);

    planet.vx += getAcceleration(forceVecX, masse, deltaT);
    planet.vy += getAcceleration(forceVecY, masse, deltaT);
    planet.vz += getAcceleration(forceVecZ, masse, deltaT);

    planet.x += planet.vx * deltaT;
    planet.y += planet.vy * deltaT;
    planet.z += planet.vz * deltaT;
}

void IPlanets::getOrbit(IPlanets &sun, IPlanets &planet, double deltaT)
{
    double BaseX = planet.x;
    double BaseY = planet.y;
    double BaseZ = planet.z;

    do
    {
        calculPosition(sun, planet, deltaT);
        if (planet.y > orbit)
            orbit = planet.y;
    } while (BaseX != planet.x && BaseY != planet.y && BaseZ != planet.z);
}

void IPlanets::render(glm::mat4 projection, glm::mat4 view, GLuint shaderProg, double scale)
{
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x / scale, y / scale, z / scale));

    glm::mat4 MVP = projection * view * model;

    glUniformMatrix4fv(glGetUniformLocation(shaderProg, "uMVP"), 1, GL_FALSE, glm::value_ptr(MVP));
    glUniform3f(glGetUniformLocation(shaderProg, "uColor"), r, g, b);
    sphere.draw();
    renderOrbit(projection, view, shaderProg, scale);
}

void IPlanets::renderOrbit(glm::mat4 projection, glm::mat4 view, GLuint shaderProg, double scale){
    glm::mat4 modelOrbit = glm::scale(glm::mat4(1.0f),
                                           glm::vec3(orbit / scale, orbit / scale, orbit / scale));
    glm::mat4 MVP = projection * view * modelOrbit;

    glUniformMatrix4fv(glGetUniformLocation(shaderProg, "uMVP"), 1, GL_FALSE, glm::value_ptr(MVP));
    glUniform3f(glGetUniformLocation(shaderProg, "uColor"), r, g, b);
    orbitToRender.draw();
}
