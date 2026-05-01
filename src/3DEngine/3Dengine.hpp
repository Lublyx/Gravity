#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Classes/Structs.hpp>


void RenderObject(glm::mat4 projection, glm::mat4 view, GLuint shaderProg, double scale, Planets &planets);

void freeView3d(GLFWwindow *window, glm::vec3 &camPos, glm::vec3 direction, glm::vec3 right, double deltaT);

GLuint initProgram();