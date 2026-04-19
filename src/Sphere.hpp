#pragma once
#include <vector>
#include <cmath>

struct Sphere
{
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    Sphere(float radius, int sectors, int rings)
    {
        for (int i = 0; i <= rings; i++)
        {
            float phi = M_PI * i / rings;
            for (int j = 0; j <= sectors; j++)
            {
                float theta = 2.0f * M_PI * j / sectors;
                float x = radius * sin(phi) * cos(theta);
                float y = radius * cos(phi);
                float z = radius * sin(phi) * sin(theta);

                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);
            }
        }

        for (int i = 0; i < rings; i++)
        {
            for (int j = 0; j < sectors; j++)
            {
                int a = i * (sectors +1) + j;
                int b = a + sectors +1;

                indices.push_back(a);
                indices.push_back(b);
                indices.push_back(a+1);

                indices.push_back(b);
                indices.push_back(b+1);
                indices.push_back(a+1);
            }
        }
    }
};
