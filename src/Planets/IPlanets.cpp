#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Renders/RenderSphere.hpp>
#include <Renders/RenderOrbit.hpp>
#include <Planets/IPlanets.hpp>
#include <GravityEngine/GravityEngine.hpp>

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
    // double BaseX = planet.x;
    // double BaseY = planet.y;
    // double BaseZ = planet.z;

    // do
    // {
    //     if (planet.y > orbit)
    // } while (BaseX != planet.x && BaseY != planet.y && BaseZ != planet.z);

    while (planet.y > orbit)
    {
        orbit = planet.y;
        calculPosition(sun, planet, deltaT);
    }
}

void IPlanets::updateOrbit(IPlanets &sun, double scale, int segment)
{
    double vecX = getPlanetVectorX(sun.x, x);
    double vecY = getPlanetVectorY(sun.y, y);
    double vecZ = getPlanetVectorZ(sun.z, z);

    std::vector<float> vertices;

    double r = getPlanetSunDistance(vecX, vecY, vecZ) / scale;

    glm::dvec3 pos = glm::normalize(glm::dvec3(x, y, z));
    glm::dvec3 vel = glm::normalize(glm::dvec3(vx, vy, vz));

    glm::dvec3 normal = glm::normalize(glm::cross(pos, vel));

    glm::dvec3 axisX = pos;                                       
    glm::dvec3 axisY = glm::normalize(glm::cross(normal, axisX));

    for (int i = 0; i < segment; i++)
    {
        float theta = 2.0f * M_PI * i / segment;

        glm::dvec3 point = r * (cos(theta) * axisX + sin(theta) * axisY);

        vertices.push_back((float)point.x);
        vertices.push_back((float)point.y);
        vertices.push_back((float)point.z);
    }

    // orbitToRender.update(vertices, segment);
}

void IPlanets::render(glm::mat4 projection, glm::mat4 view, GLuint shaderProg, double scale)
{
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x / scale, y / scale, z / scale));

    glm::mat4 MVP = projection * view * model;

    glUniformMatrix4fv(glGetUniformLocation(shaderProg, "uMVP"), 1, GL_FALSE, glm::value_ptr(MVP));
    glUniform3f(glGetUniformLocation(shaderProg, "uColor"), r, g, b);
    sphere.draw();
    orbitToRender.addPoint(x / scale, y / scale, z / scale);

    renderOrbit(projection, view, shaderProg, scale);
}

void IPlanets::renderOrbit(glm::mat4 projection, glm::mat4 view, GLuint shaderProg, double /*scale*/)
{

    glm::mat4 modelOrbit = glm::mat4(1.0f);

    glm::mat4 MVP = projection * view * modelOrbit;

    glUniformMatrix4fv(glGetUniformLocation(shaderProg, "uMVP"), 1, GL_FALSE, glm::value_ptr(MVP));
    glUniform3f(glGetUniformLocation(shaderProg, "uColor"), r, g, b);
    orbitToRender.draw();
}

void IPlanets::init(double scale, IPlanets &sun)
{
    double vecX = getPlanetVectorX(sun.x, x);
    double vecY = getPlanetVectorY(sun.y, y);
    double vecZ = getPlanetVectorZ(sun.z, z);

    double maxPoint = 2 * M_PI * (getPlanetSunDistance(vecX, vecY, vecZ) / scale);  
    sphere.init(sphereSize);
    orbitToRender.init(maxPoint);
}
