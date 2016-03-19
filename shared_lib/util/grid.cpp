#include "grid.h"

Grid::Grid() : m_lineVBO(new RenderableObject) { createVertices(); }

void Grid::toggle() { m_show = !m_show; }

void Grid::render(unique_ptr<Shader>& shader) {
    if (m_show) {
        m_lineVBO->render();
    }
}

void Grid::updateVBO() { createVertices(); }

void Grid::createVertices() {
    vector<RenderableObject::Vertex> lineData;
    double scale = params::inst().scale;
    double delta = scale / m_gridSize;
    float color_value = 0.38f;
    for (int i = -m_gridSize; i <= m_gridSize; ++i) {
        RenderableObject::Vertex xp1, xp2, yp1, yp2;
        // x-axis lines
        xp1.Position = glm::vec3(-scale, i * delta, 0.0f);
        xp2.Position = glm::vec3(scale, i * delta, 0.0f);
        if (i == 0) {
            xp1.Color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
            xp2.Color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        } else {
            xp1.Color = glm::vec4(color_value, color_value, color_value, 1.0f);
            xp2.Color = glm::vec4(color_value, color_value, color_value, 1.0f);
        }
        // y-axis lines
        yp1.Position = glm::vec3(i * delta, -scale, 0.0f);
        yp2.Position = glm::vec3(i * delta, scale, 0.0f);
        if (i == 0) {
            yp1.Color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
            yp2.Color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        } else {
            yp1.Color = glm::vec4(color_value, color_value, color_value, 1.0f);
            yp2.Color = glm::vec4(color_value, color_value, color_value, 1.0f);
        }
        lineData.push_back(xp1);
        lineData.push_back(xp2);
        lineData.push_back(yp1);
        lineData.push_back(yp2);
    }
    m_lineVBO->setData(lineData, GL_LINES);
}
