/*=====================================================================================
                                axis.h

    Description:  Axis in the lower-left corner
        
    Created by Chen Chen on 03/12/2016
=====================================================================================*/

#ifndef AXIS_H_IWBALZF4
#define AXIS_H_IWBALZF4

#include "headers.h"
#include "renderable_object.h"
#include "shader.h"

class Axis { 
public: 
    Axis(); 
    virtual ~Axis(){}

    void render(unique_ptr<Shader>& shader);
    void updateVBO();

private: 
    void createVertices();
    unique_ptr<RenderableObject> m_triangleVBO;
}; 

#endif /* end of include guard: AXIS_H_IWBALZF4 */

