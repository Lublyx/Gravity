#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <Classes/Sphere.hpp>
#include <vector>
#include <cmath>

struct RenderOrbit
{
    GLuint VAO, VBO;
    int vertexCount = 128;

    void init()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * sizeof(float), nullptr, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
    }

    void update(std::vector<float> vertices, int segment){
        vertexCount = segment;
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());
    }

    void draw()
    {
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
        glBindVertexArray(0);
    }
};
