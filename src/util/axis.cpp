#include "axis.h"

Axis::Axis() : m_triangleVBO(new RenderableObject) { createVertices(); }

void Axis::render(unique_ptr<Shader>& shader) { m_triangleVBO->render(); }

void Axis::updateVBO() { createVertices(); }

void Axis::createVertices() {
    vector<RenderableObject::Vertex> triangleData;
    vector<GLuint> triangleIndices;

    float length = 0.05f;
    float thickness = 0.001f;

    glm::vec3 x_dir(1.0f, 0.0f, 0.0f);
    glm::vec3 y_dir(0.0f, 1.0f, 0.0f);
    glm::vec3 z_dir(0.0f, 0.0f, 1.0f);
    glm::vec4 r_color(1.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 g_color(0.0f, 1.0f, 0.0f, 1.0f);
    glm::vec4 b_color(0.0f, 0.0f, 1.0f, 1.0f);

    int start_idx;
    // x axis
    RenderableObject::Vertex xv1, xv2, xv3, xv4, xv5, xv6, xv7, xv8;
    xv1.Color = r_color;
    xv2.Color = r_color;
    xv3.Color = r_color;
    xv4.Color = r_color;
    xv5.Color = r_color;
    xv6.Color = r_color;
    xv7.Color = r_color;
    xv8.Color = r_color;
    xv1.Position =                  thickness * y_dir + thickness * z_dir;
    xv2.Position = length * x_dir + thickness * y_dir + thickness * z_dir;
    xv3.Position = length * x_dir + thickness * y_dir - thickness * z_dir;
    xv4.Position =                  thickness * y_dir - thickness * z_dir;
    xv5.Position =                - thickness * y_dir + thickness * z_dir;
    xv6.Position = length * x_dir - thickness * y_dir + thickness * z_dir;
    xv7.Position = length * x_dir - thickness * y_dir - thickness * z_dir;
    xv8.Position =                - thickness * y_dir - thickness * z_dir;
    start_idx = triangleData.size();
    triangleData.push_back(xv1);
    triangleData.push_back(xv2);
    triangleData.push_back(xv3);
    triangleData.push_back(xv4);
    triangleData.push_back(xv5);
    triangleData.push_back(xv6);
    triangleData.push_back(xv7);
    triangleData.push_back(xv8);

    triangleIndices.push_back(start_idx);
    triangleIndices.push_back(start_idx + 1);
    triangleIndices.push_back(start_idx + 2);
    triangleIndices.push_back(start_idx);
    triangleIndices.push_back(start_idx + 2);
    triangleIndices.push_back(start_idx + 3);

    triangleIndices.push_back(start_idx + 4);
    triangleIndices.push_back(start_idx + 6);
    triangleIndices.push_back(start_idx + 5);
    triangleIndices.push_back(start_idx + 4);
    triangleIndices.push_back(start_idx + 7);
    triangleIndices.push_back(start_idx + 6);

    triangleIndices.push_back(start_idx);
    triangleIndices.push_back(start_idx + 4);
    triangleIndices.push_back(start_idx + 5);
    triangleIndices.push_back(start_idx);
    triangleIndices.push_back(start_idx + 5);
    triangleIndices.push_back(start_idx + 1);

    triangleIndices.push_back(start_idx + 3);
    triangleIndices.push_back(start_idx + 6);
    triangleIndices.push_back(start_idx + 7);
    triangleIndices.push_back(start_idx + 3);
    triangleIndices.push_back(start_idx + 2);
    triangleIndices.push_back(start_idx + 6); 

    triangleIndices.push_back(start_idx + 1);
    triangleIndices.push_back(start_idx + 5);
    triangleIndices.push_back(start_idx + 6);
    triangleIndices.push_back(start_idx + 1);
    triangleIndices.push_back(start_idx + 6);
    triangleIndices.push_back(start_idx + 2);
    
    // y axis
    RenderableObject::Vertex yv1, yv2, yv3, yv4, yv5, yv6, yv7, yv8;
    yv1.Color = g_color;
    yv2.Color = g_color;
    yv3.Color = g_color;
    yv4.Color = g_color;
    yv5.Color = g_color;
    yv6.Color = g_color;
    yv7.Color = g_color;
    yv8.Color = g_color;
    yv1.Position =                  thickness * z_dir + thickness * x_dir;
    yv2.Position = length * y_dir + thickness * z_dir + thickness * x_dir;
    yv3.Position = length * y_dir + thickness * z_dir - thickness * x_dir;
    yv4.Position =                  thickness * z_dir - thickness * x_dir;
    yv5.Position =                - thickness * z_dir + thickness * x_dir;
    yv6.Position = length * y_dir - thickness * z_dir + thickness * x_dir;
    yv7.Position = length * y_dir - thickness * z_dir - thickness * x_dir;
    yv8.Position =                - thickness * z_dir - thickness * x_dir;
    start_idx = triangleData.size();
    triangleData.push_back(yv1);
    triangleData.push_back(yv2);
    triangleData.push_back(yv3);
    triangleData.push_back(yv4);
    triangleData.push_back(yv5);
    triangleData.push_back(yv6);
    triangleData.push_back(yv7);
    triangleData.push_back(yv8);

    triangleIndices.push_back(start_idx);
    triangleIndices.push_back(start_idx + 1);
    triangleIndices.push_back(start_idx + 2);
    triangleIndices.push_back(start_idx);
    triangleIndices.push_back(start_idx + 2);
    triangleIndices.push_back(start_idx + 3);

    triangleIndices.push_back(start_idx + 4);
    triangleIndices.push_back(start_idx + 6);
    triangleIndices.push_back(start_idx + 5);
    triangleIndices.push_back(start_idx + 4);
    triangleIndices.push_back(start_idx + 7);
    triangleIndices.push_back(start_idx + 6);

    triangleIndices.push_back(start_idx);
    triangleIndices.push_back(start_idx + 4);
    triangleIndices.push_back(start_idx + 5);
    triangleIndices.push_back(start_idx);
    triangleIndices.push_back(start_idx + 5);
    triangleIndices.push_back(start_idx + 1);

    triangleIndices.push_back(start_idx + 3);
    triangleIndices.push_back(start_idx + 6);
    triangleIndices.push_back(start_idx + 7);
    triangleIndices.push_back(start_idx + 3);
    triangleIndices.push_back(start_idx + 2);
    triangleIndices.push_back(start_idx + 6); 

    triangleIndices.push_back(start_idx + 1);
    triangleIndices.push_back(start_idx + 5);
    triangleIndices.push_back(start_idx + 6);
    triangleIndices.push_back(start_idx + 1);
    triangleIndices.push_back(start_idx + 6);
    triangleIndices.push_back(start_idx + 2); 
    
    // z axis
    RenderableObject::Vertex zv1, zv2, zv3, zv4, zv5, zv6, zv7, zv8;
    zv1.Color = b_color;
    zv2.Color = b_color;
    zv3.Color = b_color;
    zv4.Color = b_color;
    zv5.Color = b_color;
    zv6.Color = b_color;
    zv7.Color = b_color;
    zv8.Color = b_color;
    zv1.Position =                  thickness * x_dir + thickness * y_dir;
    zv2.Position = length * z_dir + thickness * x_dir + thickness * y_dir;
    zv3.Position = length * z_dir + thickness * x_dir - thickness * y_dir;
    zv4.Position =                  thickness * x_dir - thickness * y_dir;
    zv5.Position =                - thickness * x_dir + thickness * y_dir;
    zv6.Position = length * z_dir - thickness * x_dir + thickness * y_dir;
    zv7.Position = length * z_dir - thickness * x_dir - thickness * y_dir;
    zv8.Position =                - thickness * x_dir - thickness * y_dir;
    start_idx = triangleData.size();
    triangleData.push_back(zv1);
    triangleData.push_back(zv2);
    triangleData.push_back(zv3);
    triangleData.push_back(zv4);
    triangleData.push_back(zv5);
    triangleData.push_back(zv6);
    triangleData.push_back(zv7);
    triangleData.push_back(zv8);

    triangleIndices.push_back(start_idx);
    triangleIndices.push_back(start_idx + 1);
    triangleIndices.push_back(start_idx + 2);
    triangleIndices.push_back(start_idx);
    triangleIndices.push_back(start_idx + 2);
    triangleIndices.push_back(start_idx + 3);

    triangleIndices.push_back(start_idx + 4);
    triangleIndices.push_back(start_idx + 6);
    triangleIndices.push_back(start_idx + 5);
    triangleIndices.push_back(start_idx + 4);
    triangleIndices.push_back(start_idx + 7);
    triangleIndices.push_back(start_idx + 6);

    triangleIndices.push_back(start_idx);
    triangleIndices.push_back(start_idx + 4);
    triangleIndices.push_back(start_idx + 5);
    triangleIndices.push_back(start_idx);
    triangleIndices.push_back(start_idx + 5);
    triangleIndices.push_back(start_idx + 1);

    triangleIndices.push_back(start_idx + 3);
    triangleIndices.push_back(start_idx + 6);
    triangleIndices.push_back(start_idx + 7);
    triangleIndices.push_back(start_idx + 3);
    triangleIndices.push_back(start_idx + 2);
    triangleIndices.push_back(start_idx + 6); 

    triangleIndices.push_back(start_idx + 1);
    triangleIndices.push_back(start_idx + 5);
    triangleIndices.push_back(start_idx + 6);
    triangleIndices.push_back(start_idx + 1);
    triangleIndices.push_back(start_idx + 6);
    triangleIndices.push_back(start_idx + 2); 

    m_triangleVBO->setData(triangleData, triangleIndices, GL_TRIANGLES);
}
