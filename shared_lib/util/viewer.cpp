#include "viewer.h"
#include <pcl/common/common.h>
#include <pcl/search/search.h>

vector<bool> Viewer::keys(1024, false);
Camera* Viewer::camera = nullptr;
double Viewer::lastXPos = 0.0f;
double Viewer::lastYPos = 0.0f;
bool Viewer::leftMousePressed = false;
bool Viewer::rightMousePressed = false;

Viewer::Viewer() {
    initWindow();
    initGLContext();
    setupCallback();

    // Load default resources
    ResourceManager::inst().loadShader("../shader/Default.vert.glsl",
                                       "../shader/Default.frag.glsl",
                                       "default");
    initParams();
    m_grid.reset(new Grid);
    m_axis.reset(new Axis);
    m_background.reset(new RenderableObject);
    m_pointVBO.reset(new RenderableObject);
    if (camera == nullptr) {
        camera = new Camera;
    }
    camera->resize(m_width, m_height);
    setupBackground();
}

Viewer::~Viewer() {
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    glfwDestroyWindow(m_window);
    if (camera != nullptr) {
        delete camera;
    }
}

void Viewer::clear() {
    m_pointData.clear();
    resetBBOX();
}

void Viewer::addPointCloud(pcl::PointCloud<pcl::PointXYZI>::Ptr& cloud,
                           glm::vec4 color) {
    for (size_t i = 0; i < cloud->size(); ++i) {
        pcl::PointXYZI& pt = cloud->at(i);
        m_pointData.push_back(Eigen::Vector3d(pt.x, pt.y, pt.z));
        m_pointColor.push_back(color);
    }
    pcl::PointXYZI min_pt, max_pt;
    pcl::getMinMax3D(*cloud, min_pt, max_pt);
    updateBBOX(min_pt.x, max_pt.x, min_pt.y, max_pt.y, min_pt.z, max_pt.z);
}

void Viewer::updateVBO() {
    vector<RenderableObject::Vertex> vertexData;

    // Add m_pointData
    for (size_t i = 0; i < m_pointData.size(); ++i) {
        RenderableObject::Vertex vpt;
        vpt.Position = convertToDisplayCoord(
            m_pointData[i][0], m_pointData[i][1], m_pointData[i][2]);
        vpt.Color = m_pointColor[i];
        vertexData.push_back(vpt);
    }

    m_pointVBO->setData(vertexData, GL_POINTS);
}

void Viewer::draw() {
    unique_ptr<Shader>& default_shader =
        ResourceManager::inst().getShader("default");
    camera->resize(m_width, m_height);
    // Main loop
    while (!glfwWindowShouldClose(m_window)) {
        // Check if any events have been activiated (key pressed, mouse moved
        // etc.) and call corresponding response functions
        glfwPollEvents();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera->currentMatrices(m_trans);
        default_shader->bind();
        default_shader->selectSubroutine("renderPlain", GL_FRAGMENT_SHADER);
        default_shader->setf("gamma", params::inst().gamma);

        // Draw background
        default_shader->setMatrix("matModel", glm::mat4(1.0f));
        default_shader->setMatrix("matViewProjection", glm::mat4(1.0f));
        default_shader->setf("gamma", params::inst().gamma);
        m_background->render();

        // Draw grid
        default_shader->setMatrix("matModel", glm::mat4(1.0f));
        default_shader->setMatrix("matViewProjection",
                                  m_trans.matViewProjection);
        m_grid->render(default_shader);

        // Draw data
        if (params::inst().boundBox.updated) {
            updateVBO();
            params::inst().boundBox.updated = false;
        }
        m_pointVBO->render();

        // Draw axis
        default_shader->setMatrix("matModel", glm::mat4(1.0f));
        default_shader->setMatrix("matViewProjection", m_trans.matAxisRotation);
        m_axis->render(default_shader);

        default_shader->release();

        // Swap the screen buffers
        glfwSwapBuffers(m_window);
    }
}

void Viewer::initParams() {
    // Initialize global parameters
    params::inst().windowSize = glm::vec2(m_width, m_height);
    params::inst().polygonMode = 0;
    params::inst().gridRenderMode = 0;
    params::inst().scale = 100.0f;
}

void Viewer::initWindow() {
    std::cout << "Using OpenGL Version " << m_defaultOpenGLVersionMajor << "."
              << m_defaultOpenGLVersionMinor << std::endl;
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /*glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    m_window =
        glfwCreateWindow(m_width, m_height, "OpenGL Viewer", nullptr, nullptr);
    if (m_window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(m_window);
    // Set this to true so GLEW knows to use a modern approach to retrieving
    // function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        exit(1);
    }
}

void Viewer::setupCallback() {
    // Setup GLFW callback
    glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);
    glfwSetKeyCallback(m_window, KeyboardCallback);
    glfwSetMouseButtonCallback(m_window, MouseButtonCallback);
    glfwSetCursorPosCallback(m_window, MousePositionCallback);
    glfwSetScrollCallback(m_window, MouseWheelCallback);
}

void Viewer::initGLContext() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glfwGetFramebufferSize(m_window, &m_width, &m_height);
}

void Viewer::setupBackground() {
    vector<RenderableObject::Vertex> quadData;
    RenderableObject::Vertex vbl, vbr, vtl, vtr;
    double z = 0.999999f;  // a hack here
    vbl.Position = glm::vec3(-1.0, -1.0, z);
    vbr.Position = glm::vec3(1.0, -1.0, z);
    vtl.Position = glm::vec3(-1.0, 1.0, z);
    vtr.Position = glm::vec3(1.0, 1.0, z);

    glm::vec4 bottom_color(0.1f, 0.1f, 0.1f, 0.3f);
    glm::vec4 top_color(0.33f, 0.36f, 0.6f, 1.0f);
    vbl.Color = bottom_color;
    vbr.Color = bottom_color;
    vtl.Color = top_color;
    vtr.Color = top_color;
    quadData.push_back(vbl);
    quadData.push_back(vbr);
    quadData.push_back(vtr);
    quadData.push_back(vtl);
    vector<GLuint> quadIndices{0, 1, 2, 0, 2, 3};
    m_background->setData(quadData, quadIndices, GL_TRIANGLES);
}

void Viewer::FramebufferSizeCallback(GLFWwindow* window, int width,
                                     int height) {
    params::inst().windowSize = glm::vec2(width, height);
    glViewport(0, 0, width, height);
}

void Viewer::KeyboardCallback(GLFWwindow* window, int key, int scancode,
                              int action, int mode) {
    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (action == GLFW_PRESS)
        keys[key] = true;
    else if (action == GLFW_RELEASE)
        keys[key] = false;
}

void Viewer::MouseButtonCallback(GLFWwindow* window, int button, int action,
                                 int mods) {
    switch (action) {
        case GLFW_PRESS:
            if (button == GLFW_MOUSE_BUTTON_LEFT) {
                leftMousePressed = true;
            }
            if (button == GLFW_MOUSE_BUTTON_RIGHT) {
                rightMousePressed = true;
            }
            break;
        case GLFW_RELEASE:
            if (button == GLFW_MOUSE_BUTTON_LEFT) {
                leftMousePressed = false;
            }
            if (button == GLFW_MOUSE_BUTTON_RIGHT) {
                rightMousePressed = false;
            }
            break;
        default:
            break;
    }
}

void Viewer::MousePositionCallback(GLFWwindow* window, double xpos,
                                   double ypos) {
    if (leftMousePressed || rightMousePressed) {
        double xoffset = xpos - lastXPos;
        double yoffset = ypos - lastYPos;
        float MAX_DIFF = 30.0f;
        float dx = clamp(xoffset, -MAX_DIFF, MAX_DIFF);
        float dy = clamp(yoffset, -MAX_DIFF, MAX_DIFF);

        // Left button for rotation, right button for translation
        int state = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL);
        if (leftMousePressed) {
            if (state == GLFW_PRESS) {
                camera->onMouseMove(xoffset, yoffset, 1);
            } else {
                camera->onMouseMove(xoffset, yoffset, 0);
            }
        } else if (rightMousePressed) {
            camera->onMouseMove(xoffset, yoffset, 1);
        }
    }
    lastXPos = xpos;
    lastYPos = ypos;
}

void Viewer::MouseWheelCallback(GLFWwindow* window, double xoffset,
                                double yoffset) {
    double dy = clamp(10.0f * yoffset, -10, 10);
    camera->onMouseWheel(dy, 0.0f, 0.0f);
}
