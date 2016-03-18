#include "renderable_object.h"
#include <stdio.h>

RenderableObject::RenderableObject()
    : m_useIndexBuffer(false),
      m_vao(0),
      m_vbo(0),
      m_ebo(0),
      m_nVertices(0),
      m_primitiveMode(GL_POINTS),
      m_usage(GL_STATIC_DRAW) {
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);
}

RenderableObject::~RenderableObject() {
    if (m_vao != GL_INVALID_VALUE) glDeleteVertexArrays(1, &m_vao);

    if (m_vbo != GL_INVALID_VALUE) glDeleteBuffers(1, &m_vbo);

    if (m_ebo != GL_INVALID_VALUE) glDeleteBuffers(1, &m_ebo);
}

void RenderableObject::bind() { glBindVertexArray(m_vao); }

void RenderableObject::release() { glBindVertexArray(0); }

void RenderableObject::render() {
    if (m_nVertices == 0) {
        return;
    }

    glBindVertexArray(m_vao);
    if (!m_useIndexBuffer) {
        glDrawArrays(m_primitiveMode, 0, m_nVertices);
    } else {
        glDrawElements(m_primitiveMode, m_nVertices, GL_UNSIGNED_INT, 0);
    }
    glBindVertexArray(0);
}

void RenderableObject::render(int first, int count) {
    if (m_nVertices == 0) {
        return;
    }
    if (first + count >= m_nVertices) {
        return;
    }

    glBindVertexArray(m_vao);
    if (!m_useIndexBuffer) {
        glDrawArrays(m_primitiveMode, first, count);
    } else {
        glDrawElements(m_primitiveMode, count, GL_UNSIGNED_INT,
                       (GLvoid*)(first * sizeof(GLuint)));
    }
    glBindVertexArray(0);
}

/*=====================================================================================
        Transfer data to VBO

        - usage: GL_STATIC_DRAW, GL_DYNAMIC_DRAW
        - primitiveMode: GL_POINTS, GL_LINES, GL_TRIANGLES, etc.

=====================================================================================*/
void RenderableObject::setData(vector<Vertex> data, GLenum primitiveMode,
                               GLenum usage) {
    m_vertices = std::move(data);

    m_useIndexBuffer = false;
    m_nVertices = m_vertices.size();
    m_primitiveMode = primitiveMode;
    m_usage = usage;

    this->bind();
    // Bind vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);

    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex),
                 &m_vertices[0], m_usage);

    // Set the vertex attribute pointers
    // Vertex Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    // Vertex Normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (GLvoid*)offsetof(Vertex, Normal));
    // Vertex Color
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (GLvoid*)offsetof(Vertex, Color));
    // Vertex Texture Coords
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (GLvoid*)offsetof(Vertex, TexCoords));

    this->release();
}

void RenderableObject::setData(vector<Vertex> data, vector<GLuint> indices,
                               GLenum primitiveMode, GLenum usage) {
    this->m_vertices = std::move(data);
    this->m_indices = std::move(indices);

    m_useIndexBuffer = true;
    m_nVertices = m_indices.size();
    m_primitiveMode = primitiveMode;
    m_usage = usage;

    this->bind();
    // Bind vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);

    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex),
                 &m_vertices[0], m_usage);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint),
                 &m_indices[0], m_usage);

    // Set the vertex attribute pointers
    // Vertex Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    // Vertex Normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (GLvoid*)offsetof(Vertex, Normal));
    // Vertex Color
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (GLvoid*)offsetof(Vertex, Color));
    // Vertex Texture Coords
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (GLvoid*)offsetof(Vertex, TexCoords));

    this->release();
}
