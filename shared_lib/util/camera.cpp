#include "camera.h"

Camera::Camera() : m_conf(PERSPECTIVE), m_camSpeed(10.0f) {
    float scale = params::inst().scale;
    m_aspect = params::inst().windowSize.x / params::inst().windowSize.y;
    m_fov = 45.0f;
    m_ncp = 1.0f;
    m_fcp = 10.0f * params::inst().scale;
    m_mouseSensitivity = 0.1f;

    // Normal
    m_position = glm::vec3(1.5f * scale, -0.5f * scale, 0.8f * scale);
    m_up = glm::vec3(0.0f, 0.0f, 1.0f);

    m_front = glm::normalize(-m_position);
    m_right = glm::cross(m_front, m_up);
    m_modelZRot = 0.0f;
    m_modelXRot = 0.0f;
    m_maxZoom = 0.05f * scale;

    m_camSpeed = 1.0f;
}

Camera::~Camera() {}

void Camera::resize(float width, float height) { m_aspect = width / height; }

void Camera::toggleCameraMode() {
    if (m_conf == PERSPECTIVE) {
        m_conf = ORTHOGONAL;
    } else {
        m_conf = PERSPECTIVE;
    }
}

void Camera::computeViewProjection() {
    if (m_conf == PERSPECTIVE) {
        // Perspective Camera
        m_projection = glm::perspective(m_fov, m_aspect, m_ncp, m_fcp);

        glm::mat4 rotate(1.0f);
        rotate = glm::rotate(rotate, glm::radians(m_modelXRot), m_right);
        rotate = glm::rotate(rotate, glm::radians(m_modelZRot),
                             glm::vec3(0.0f, 0.0f, 1.0f));

        // View matrix
        glm::mat4 trans(1.0f);
        trans = glm::translate(trans, m_modelTranslate);
        m_view =
            trans * glm::lookAt(m_position, glm::vec3(0.0f), m_up) * rotate;

        // Axis (Lower left corner) transformation
        glm::mat4 axisTrans(1.0f);
        axisTrans = glm::translate(axisTrans, glm::vec3(-0.9f, -0.9f, 0.0f));
        glm::mat4 tmpMat = m_projection *
                           glm::lookAt(m_position, glm::vec3(0.0f), m_up) *
                           rotate;
        glm::mat3 tmpMat1 = glm::mat3(tmpMat);
        m_axisRotation = axisTrans * glm::mat4(tmpMat1);
    } else {
        float length = glm::length(m_position);
        float orthoWidth, orthoHeight;
        orthoWidth = abs(length);
        orthoHeight = abs(length);

        float orthoLeft = -orthoWidth / 1.8f * m_aspect;
        float orthoRight = orthoWidth / 1.8f * m_aspect;
        float orthoBottom = -orthoHeight / 1.8f;
        float orthoTop = orthoHeight / 1.8f;

        m_projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop,
                                  -m_fcp, m_fcp);

        glm::mat4 rotate(1.0f);
        rotate = glm::rotate(rotate, glm::radians(m_modelXRot), m_right);
        rotate = glm::rotate(rotate, glm::radians(m_modelZRot),
                             glm::vec3(0.0f, 0.0f, 1.0f));

        // View matrix
        glm::mat4 trans(1.0f);
        trans = glm::translate(trans, m_modelTranslate);
        m_view =
            trans * glm::lookAt(m_position, glm::vec3(0.0f), m_up) * rotate;

        // Axis (Lower left corner) transformation
        glm::mat4 axisTrans(1.0f);
        axisTrans = glm::translate(axisTrans, glm::vec3(-0.9f, -0.9f, 0.0f));
        glm::mat4 tmpMat = m_projection *
                           glm::lookAt(m_position, glm::vec3(0.0f), m_up) *
                           rotate * length;
        glm::mat3 tmpMat1 = glm::mat3(tmpMat);
        m_axisRotation = axisTrans * glm::mat4(tmpMat1);
    }
}

void Camera::currentMatrices(Transform& trans) {
    computeViewProjection();
    // Update trans
    trans.matView = m_view;
    trans.matProjection = m_projection;
    trans.matViewProjection = m_projection * m_view;
    trans.matAxisRotation = m_axisRotation;
}

void Camera::topView() {
    float length = glm::length(m_position);
    m_position = glm::vec3(0.0f, 0.0f, length);
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    m_front = glm::normalize(-m_position);
    m_right = glm::cross(m_front, m_up);
    m_modelXRot = 0.0f;
    m_modelZRot = 0.0f;
}

void Camera::rightView() {
    float length = glm::length(m_position);
    m_position = glm::vec3(length, 0.0f, 0.0f);
    m_up = glm::vec3(0.0f, 0.0f, 1.0f);
    m_front = glm::normalize(-m_position);
    m_right = glm::cross(m_front, m_up);
    m_modelXRot = 0.0f;
    m_modelZRot = 0.0f;
}

void Camera::normalView() {
    float length = glm::length(m_position);
    glm::vec3 dir = glm::vec3(1.5f, -0.5f, 0.8f);
    m_position = length * glm::normalize(dir);
    m_up = glm::vec3(0.0f, 0.0f, 1.0f);
    m_front = glm::normalize(-m_position);
    m_right = glm::cross(m_front, m_up);
    m_modelXRot = 0.0f;
    m_modelZRot = 0.0f;
}

// Keyboard / Mouse Response
// button = 0: left button
// button = 1: right button
void Camera::onMouseMove(float dx, float dy, int button) {
    if (button == 1) {
        // Right button
        m_modelTranslate.x += (m_mouseSensitivity * dx);
        m_modelTranslate.y -= (m_mouseSensitivity * dy);
    } else {
        // Left button
        m_modelZRot -= (m_mouseSensitivity * dx);
        m_modelXRot -= (m_mouseSensitivity * dy);
        clamp(m_modelZRot, -360.0f, 360.0f);
        clamp(m_modelXRot, -360.0f, 360.0f);
    }
}

void Camera::onMouseWheel(int yoffset, double tx, double ty) {
    float delta = abs(yoffset);
    if (delta < 0.01) {
        delta = 0.01;
    }

    if (yoffset > 0) {
        /*m_zoom += delta;*/
        m_position += delta * m_front;
    } else {
        /*m_zoom -= delta;*/
        m_position -= delta * m_front;
    }
    if (glm::dot(-m_position, m_front) < m_maxZoom) {
        m_position = -m_maxZoom * m_front;
    }
}

void Camera::onKeyPress(int keyId) {}

void Camera::onKeyRelease(int keyId) {}

void Camera::increaseSpeed() { m_camSpeed *= 2; }

void Camera::decreaseSpeed() { m_camSpeed /= 2; }

float Camera::currentCamFov() { return m_fov; }

float Camera::currentCamNcp() { return m_ncp; }

float Camera::currentCamFcp() { return m_fcp; }
