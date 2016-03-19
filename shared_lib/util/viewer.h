/*=====================================================================================
                                viewer.h

    Description:  This is a viewer class for data visualization
        
    Created by Chen Chen on 03/18/2016
=====================================================================================*/

#ifndef VIEWER_H
#define VIEWER_H

#include <iostream> 

#include "headers.h"
#include "axis.h"
#include "camera.h"
#include "grid.h"
#include "resource_manager.h"

class Viewer { 
public: 
    Viewer(); 
    virtual ~Viewer(); 

    void draw();
    static vector<bool> keys;
    static Camera* camera;
    static double lastXPos, lastYPos;
    static bool leftMousePressed;
    static bool rightMousePressed;

private: 
    void initParams();
    void initWindow();
    void setupCallback();
    void initGLContext();

    void setupBackground();

    // Default window size
    int m_width = 1200;
    int m_height = 800;
    int m_defaultOpenGLVersionMajor = 4;
    int m_defaultOpenGLVersionMinor = 0;

    GLFWwindow* m_window = nullptr;

    unique_ptr<Grid> m_grid;
    unique_ptr<Axis> m_axis;
    unique_ptr<RenderableObject> m_background;

    Transform m_trans;

    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void MousePositionCallback(GLFWwindow* window, double xpos, double ypos);
    static void MouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset);
}; 

#endif /* end of include guard: VIEWER_H */
