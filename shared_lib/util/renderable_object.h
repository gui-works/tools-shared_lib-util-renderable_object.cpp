/*=====================================================================================
                                renderable_object.h
Description:
    This class take data, and render them according to the drawing method
(m_primitiveMode): GL_POINTS, GL_TRIANGLES, etc.
    IMPORTANT NOTES:
        - RenderableObject assumes the following vertex layout. You should
follow this rule in every shader you create. Otherwise, RenderableObject cannot
setup the vertex layout correctly.
            #define VERT_POSITION	0
            #define VERT_NORMAL     1
            #define VERT_COLOR		2
            #define VERT_TEXTURE    3

            layout(location = VERT_POSITION) in vec3 VertexPosition;
            layout(location = VERT_NORMAL)   in vec3 VertexNormal;
            layout(location = VERT_COLOR)    in vec4 VertexColor;
            layout(location = VERT_TEXTURE)  in vec4 VertexTexture;

        - RenderableObject DOES NOT take care of shader setup! You need to do it
in corresponding object class which current RenderableObject belongs to.

        - Each RenderableObject handles ONLY ONE drawing mode: GL_TRIANGLES,
GL_POINTS, GL_LINESTRIPS, etc.

    To use RenderableObjec
        1) Add a RenderableObject member in your class: e.g., RenderableObject*
m_pointVBO = new RenderableObject;
        2) Transfer data to RenderableObject, e.g.,
            m_pointVBO->setData(pointData, GL_POINTS);
            m_triangleVBO->setData(triangleData, m_triangleIndices,
GL_TRIANGLES);
        3) After setting up correct shader, call
            m_pointVBO->render();
            m_triangleVBO->render();

    Created by Chen Chen on 09/30/2015
=====================================================================================*/

#ifndef RENDERABLE_OBJECT_H
#define RENDERABLE_OBJECT_H

#include "headers.h"

class RenderableObject {
public:
    struct Vertex {
        glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);     // Coordinate
        glm::vec3 Normal = glm::vec3(0.0f, 0.0f, 0.0f);       // Normal vector
        glm::vec4 Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);  // RGBA color
        glm::vec4 TexCoords =
            glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);  // Texture coordinate
    };

public:
    RenderableObject();
    ~RenderableObject();

    RenderableObject(RenderableObject&& x) = default;
    RenderableObject& operator=(RenderableObject&& x) = default;

    void render();
    void render(int first, int count); // Draw part of the data

    // Setup vertex data
    // Without element buffer
    void setData(vector<Vertex> data, GLenum primitiveMode,
                 GLenum usage = GL_STATIC_DRAW);

    // With element buffer
    void setData(vector<Vertex> data, vector<GLuint> indices,
                 GLenum primitiveMode, GLenum usage = GL_STATIC_DRAW);

private:
    // Disable copying
    RenderableObject(const RenderableObject&);
    RenderableObject& operator=(const RenderableObject&);

    // Private functions bind/release vao
    void bind();
    void release();

    // Data
    vector<Vertex> m_vertices;
    bool m_useIndexBuffer;
    vector<GLuint> m_indices;

    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;

    GLenum m_usage;          // GL_STATIC_DRAW, GL_DYNAMIC_DRAW, etc.
    GLenum m_primitiveMode;  // GL_POINTS, GL_LINES, etc.

    int m_nVertices;
};

#endif
