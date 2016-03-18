/*=====================================================================================
                  camera_manager.h

Description:  Camera Manager Class
    - Two modes:
        1) Perspective: zoom by moving in the z-direction;
        2) Orthogonal: zoom by changing the projection matrix.

Created by Chen Chen on 09/28/2015
=====================================================================================*/

#ifndef CAMERA_MANAGER_H_
#define CAMERA_MANAGER_H_

#include "headers.h"

class Camera {
public:
    enum CameraMovement { FORWARD, BACKWARD, LEFT, RIGHT };

    Camera();
    ~Camera();

    void update();
    void resize(float width, float height);

    // Toggle Camera Mode
    void toggleCameraMode();

    // Camera Information
    void currentMatrices(Transform& trans);

    void topView();
    void rightView();
    void normalView();

    // Keyboard / Mouse response
    void onMouseMove(float dx, float dy, int button);
    void onMouseWheel(int yoffset, double tx = 0.0f,
                      double ty = 0.0f);  // tx and ty are used for zooming into
                                          // mouse location
    void onKeyPress(int keyId);
    void onKeyRelease(int keyId);

    void increaseSpeed();  // Increase cameras' moving speed
    void decreaseSpeed();  // Decrease cameras' moving speed

    float currentCamFov();
    float currentCamNcp();
    float currentCamFcp();

private:
    enum Config { PERSPECTIVE = 0, ORTHOGONAL = 1 };

    // Compute current projection, view matrices, and store them in m_projection
    // and m_view
    void computeViewProjection();

    // Camera parameters
    // Default camera always look at 0, rotation and translation is applied to
    // model. Zooming is applied to camera's position.
    Config m_conf;
    float m_aspect;
    float m_fov;
    float m_ncp;
    float m_fcp;
    float m_maxZoom;
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;

    float m_modelZRot;
    float m_modelXRot;
    glm::vec3 m_modelTranslate;

    // Helper matrices, only used internally when m_useCam = false
    glm::mat4 m_projection;
    glm::mat4 m_view;

    float m_mouseSensitivity;
    float m_camSpeed;

    // Axis rotation
    glm::mat4 m_axisRotation;
};

#endif /* end of include guard: CAMERA_MANAGER_H_ */
