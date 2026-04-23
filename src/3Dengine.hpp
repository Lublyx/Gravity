#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Class.hpp>

void RenderObject(glm::mat4 projection, glm::mat4 view, GLuint shaderProg, double scale, RenderMesh meshes, Orbits orbits, Planets &planets);