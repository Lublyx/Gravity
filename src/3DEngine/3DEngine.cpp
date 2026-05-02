#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>

#include <Classes/Structs.hpp>
#include <Renders/RenderOrbit.hpp>
#include <Renders/RenderSphere.hpp>

void RenderObject(glm::mat4 projection, glm::mat4 view, GLuint shaderProg, double scale, Planets &planets)
{
    planets.sun.render(projection, view, shaderProg, scale);
    planets.earth.render(projection, view, shaderProg, scale);
    planets.mars.render(projection, view, shaderProg, scale);
    planets.mercury.render(projection, view, shaderProg, scale);
    planets.venus.render(projection, view, shaderProg, scale);
    planets.jupiter.render(projection, view, shaderProg, scale);
    planets.neptune.render(projection, view, shaderProg, scale);
    planets.saturn.render(projection, view, shaderProg, scale);
    planets.uranus.render(projection, view, shaderProg, scale);
}

void updateOrbit(Planets &planets, double scale)
{
    planets.earth.updateOrbit(planets.sun, scale);
    planets.mars.updateOrbit(planets.sun, scale);
    planets.mercury.updateOrbit(planets.sun, scale);
    planets.venus.updateOrbit(planets.sun, scale);
    planets.jupiter.updateOrbit(planets.sun, scale);
    planets.neptune.updateOrbit(planets.sun, scale);
    planets.saturn.updateOrbit(planets.sun, scale);
    planets.uranus.updateOrbit(planets.sun, scale);
}

void freeView3d(GLFWwindow *window, glm::vec3 &camPos, glm::vec3 direction, glm::vec3 right, double deltaT)
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        camPos += direction * 0.001f * (float)deltaT;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        camPos -= right * 0.001f * (float)deltaT;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        camPos -= direction * 0.001f * (float)deltaT;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        camPos += right * 0.001f * (float)deltaT;
    }
}

//  Shaders
static const char *VERTEX_SHADER_SRC = R"glsl(
    #version 330 core
    layout(location = 0) in vec3 aPos;

    uniform mat4 uMVP;
    uniform float uPointSize;

    void main()
    {
        gl_Position = uMVP * vec4(aPos, 1.0);
        gl_PointSize = uPointSize;
    }
)glsl";

static const char *FRAGMENT_SHADER_SRC = R"glsl(
    #version 330 core
    out vec4 FragColor;

    uniform vec3 uColor;

    void main()
    {
        FragColor = vec4(uColor, 1.0);
    }
)glsl";

//  Compilation d'un shader
static GLuint compileShader(GLenum type, const char *src)
{
    GLuint id = glCreateShader(type);
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    GLint ok = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &ok);
    if (!ok)
    {
        char log[512];
        glGetShaderInfoLog(id, 512, nullptr, log);
        std::cerr << "[Shader Error] " << log << "\n";
        glDeleteShader(id);
        return 0;
    }
    return id;
}

static GLuint createProgram(const char *vertSrc, const char *fragSrc)
{
    GLuint vert = compileShader(GL_VERTEX_SHADER, vertSrc);
    GLuint frag = compileShader(GL_FRAGMENT_SHADER, fragSrc);

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vert);
    glAttachShader(prog, frag);
    glLinkProgram(prog);

    GLint ok = 0;
    glGetProgramiv(prog, GL_LINK_STATUS, &ok);
    if (!ok)
    {
        char log[512];
        glGetProgramInfoLog(prog, 512, nullptr, log);
        std::cerr << "[Program Error] " << log << "\n";
    }

    glDeleteShader(vert);
    glDeleteShader(frag);
    return prog;
}

GLuint initProgram()
{
    return createProgram(VERTEX_SHADER_SRC, FRAGMENT_SHADER_SRC);
}