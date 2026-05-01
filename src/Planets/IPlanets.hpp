#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Renders/RenderSphere.hpp>
#include <Renders/RenderOrbit.hpp>


class IPlanets
{
private:
    RenderOrbit orbitToRender;
    void renderOrbit(glm::mat4 projection, glm::mat4 view, GLuint shaderProg, double scale);

public:
    double x;
    double y;
    double z;
    double vx;
    double vy;
    double vz;
    double r;
    double g;
    double b;
    double masse;
    double orbit;
    int sphereSize;
    RenderSphere sphere;

    virtual void calculPosition(IPlanets &sun, IPlanets &planet, double deltaT);
    virtual void getOrbit(IPlanets &sun, IPlanets &planet, double deltaT);
    void render(glm::mat4 projection, glm::mat4 view, GLuint shaderProg, double scale);
};