/*=====================================================================================
                                grid.h

    Description:  Grid lines

    Created by Chen Chen on 03/08/2016
=====================================================================================*/

#ifndef GRID_H
#define GRID_H

#include "headers.h"
#include "renderable_object.h"
#include "shader.h"

class Grid {
public:
    Grid();
    virtual ~Grid() {}

    void toggle();
    void render(unique_ptr<Shader>& shader);
    void updateVBO();

private:
    void createVertices();
    bool m_show = true;
    unique_ptr<RenderableObject> m_lineVBO;
    int m_gridSize = 10;
};

#endif /* end of include guard: GRID_H */
