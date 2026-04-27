#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>
#include <cstdlib>

struct RenderStars
{
    GLuint VAO, VBO;
    std::vector<float> stars;

    void initStars()
    {
        srand(42);
        for (int i = 0; i < 3000; i++)
        {
            float theta = ((rand() % 10000) / 10000.0f) * 2.0f * M_PI;
            float phi = ((rand() % 10000) / 10000.0f) * M_PI;
            float r = 6001.0f;

            float x = r * sin(phi) * cos(theta);
            float y = r * cos(phi);
            float z = r * sin(phi) * sin(theta);

            stars.push_back(x);
            stars.push_back(y);
            stars.push_back(z);
        }

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, stars.size() * sizeof(float), stars.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

        glEnable(GL_PROGRAM_POINT_SIZE);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
    }

    void draw()
    {
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, stars.size() / 3);
        glBindVertexArray(0);
    }
};
