#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Classes/Class.hpp>

void initMeshes(RenderMesh &meshes)
{
    meshes.sunSphere.init(15);
    meshes.earthSphere.init(3);
    meshes.marsSphere.init(2);
    meshes.mercurySphere.init(1.3);
    meshes.orbit.init();
}

void RenderObject(glm::mat4 projection, glm::mat4 view, GLuint shaderProg, double scale, RenderMesh meshes, Orbits orbits, Planets &planets)
{

    glm::mat4 modelSun = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    glm::mat4 MVP = projection * view * modelSun;

    glUniformMatrix4fv(glGetUniformLocation(shaderProg, "uMVP"), 1, GL_FALSE, glm::value_ptr(MVP));
    glUniform3f(glGetUniformLocation(shaderProg, "uColor"), 1.0f, 0.9f, 0.2f);
    meshes.sunSphere.draw();

    glm::mat4 modelEarth = glm::translate(glm::mat4(1.0f),
                                          glm::vec3(planets.earth.x / scale, planets.earth.y / scale, planets.earth.z / scale));
    MVP = projection * view * modelEarth;

    glUniformMatrix4fv(glGetUniformLocation(shaderProg, "uMVP"), 1, GL_FALSE, glm::value_ptr(MVP));
    glUniform3f(glGetUniformLocation(shaderProg, "uColor"), 0.20f, 0.65f, 0.89f);
    meshes.earthSphere.draw();

    glm::mat4 modelMars = glm::translate(glm::mat4(1.0f),
                                         glm::vec3(planets.mars.x / scale, planets.mars.y / scale, planets.mars.z / scale));
    MVP = projection * view * modelMars;

    glUniformMatrix4fv(glGetUniformLocation(shaderProg, "uMVP"), 1, GL_FALSE, glm::value_ptr(MVP));
    glUniform3f(glGetUniformLocation(shaderProg, "uColor"), 0.91f, 0.31f, 0.18f);
    meshes.marsSphere.draw();

    glm::mat4 modelMercury = glm::translate(glm::mat4(1.0f),
                                            glm::vec3(planets.mercury.x / scale, planets.mercury.y / scale, planets.mercury.z / scale));
    MVP = projection * view * modelMercury;

    glUniformMatrix4fv(glGetUniformLocation(shaderProg, "uMVP"), 1, GL_FALSE, glm::value_ptr(MVP));
    glUniform3f(glGetUniformLocation(shaderProg, "uColor"), 0.73f, 0.72f, 0.75f);
    meshes.mercurySphere.draw();

    glm::mat4 modelOrbitEarth = glm::scale(glm::mat4(1.0f),
                                           glm::vec3(orbits.earthOrbit / scale, orbits.earthOrbit / scale, orbits.earthOrbit / scale));
    MVP = projection * view * modelOrbitEarth;

    glUniformMatrix4fv(glGetUniformLocation(shaderProg, "uMVP"), 1, GL_FALSE, glm::value_ptr(MVP));
    glUniform3f(glGetUniformLocation(shaderProg, "uColor"), 0.20f, 0.65f, 0.89f);
    meshes.orbit.draw();

    glm::mat4 modelOrbitMars = glm::scale(glm::mat4(1.0f),
                                          glm::vec3(orbits.marsOrbit / scale, orbits.marsOrbit / scale, orbits.marsOrbit / scale));
    MVP = projection * view * modelOrbitMars;

    glUniformMatrix4fv(glGetUniformLocation(shaderProg, "uMVP"), 1, GL_FALSE, glm::value_ptr(MVP));
    glUniform3f(glGetUniformLocation(shaderProg, "uColor"), 0.91f, 0.31f, 0.18f);
    meshes.orbit.draw();

    glm::mat4 modelOrbitMercury = glm::scale(glm::mat4(1.0f),
                                             glm::vec3(orbits.mercuryrbit / scale, orbits.mercuryrbit / scale, orbits.mercuryrbit / scale));
    MVP = projection * view * modelOrbitMercury;

    glUniformMatrix4fv(glGetUniformLocation(shaderProg, "uMVP"), 1, GL_FALSE, glm::value_ptr(MVP));
    glUniform3f(glGetUniformLocation(shaderProg, "uColor"), 0.73f, 0.72f, 0.75f);
    meshes.orbit.draw();
}