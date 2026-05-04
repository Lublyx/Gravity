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
    int maxPoints = 0;
    std::vector<glm::vec3> orbitPoint;

    void init(double maxPoint)
    {
        maxPoints = maxPoint;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, maxPoints * 3 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
    }

    void addPoint(double x, double y, double z)
    {
        orbitPoint.push_back(glm::vec3(x, y, z));
        if ((int)orbitPoint.size() > maxPoints)
        {
            orbitPoint.erase(orbitPoint.begin());
        }
    }

    void draw()
    {
        std::vector<float>vertices;

        for (glm::vec3 vec : orbitPoint){
            vertices.push_back(vec.x);
            vertices.push_back(vec.y);
            vertices.push_back(vec.z);
        }

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());

        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_STRIP, 0, vertices.size() / 3);
        glBindVertexArray(0);
    }
};
