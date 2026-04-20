#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <Sphere.hpp>
#include <vector>
#include <cmath>

struct RenderOrbit
{
    GLuint VAO, VBO;
    int vertexCount;

    void init(int segment = 64)
    {
        vertexCount = segment;
        std::vector<float> vertices;

        for (int i = 0; i < segment; i++)
        {
            float theta = 2.0f * M_PI * i/segment;

            vertices.push_back(cos(theta));
            vertices.push_back(sin(theta));
            vertices.push_back(0.0f);
        }        


        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);


        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
    }

    void draw()
    {
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
        glBindVertexArray(0);
    }
};
