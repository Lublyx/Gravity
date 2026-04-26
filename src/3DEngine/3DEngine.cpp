#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Classes/Structs.hpp>


void RenderObject(glm::mat4 projection, glm::mat4 view, GLuint shaderProg, double scale, Planets &planets)
{

    planets.sun.render(projection, view, shaderProg, scale);
    planets.earth.render(projection, view, shaderProg, scale);
    planets.mars.render(projection, view, shaderProg, scale);
    planets.mercury.render(projection, view, shaderProg, scale);
    planets.venus.render(projection, view, shaderProg, scale);
}