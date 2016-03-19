#include "shader.h"
#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader()
    : m_vFileName(NULL),
      m_cFileName(NULL),
      m_eFileName(NULL),
      m_gFileName(NULL),
      m_fFileName(NULL),
      m_id(0),
      m_vertProg(0),
      m_contProg(0),
      m_evalProg(0),
      m_geomProg(0),
      m_fragProg(0) {
    if (!m_id) m_id = glCreateProgram();
}

Shader::Shader(const char *vFileName, const char *fFileName)
    : m_vFileName(NULL),
      m_cFileName(NULL),
      m_eFileName(NULL),
      m_gFileName(NULL),
      m_fFileName(NULL),
      m_id(0),
      m_vertProg(0),
      m_contProg(0),
      m_evalProg(0),
      m_geomProg(0),
      m_fragProg(0) {
    if (!m_id) m_id = glCreateProgram();

    attachVertexShader(vFileName);
    attachFragmentShader(fFileName);

    link();
}

Shader::Shader(const char *vFileName, const char *gFileName,
               const char *fFileName)
    : m_vFileName(NULL),
      m_cFileName(NULL),
      m_eFileName(NULL),
      m_gFileName(NULL),
      m_fFileName(NULL),
      m_id(0),
      m_vertProg(0),
      m_contProg(0),
      m_evalProg(0),
      m_geomProg(0),
      m_fragProg(0) {
    if (!m_id) m_id = glCreateProgram();

    attachVertexShader(vFileName);
    attachGeometryShader(gFileName);
    attachFragmentShader(fFileName);

    link();
}

Shader::Shader(const char *vFileName, const char *tcFileName,
               const char *teFileName, const char *gFileName,
               const char *fFileName)
    : m_vFileName(NULL),
      m_cFileName(NULL),
      m_eFileName(NULL),
      m_gFileName(NULL),
      m_fFileName(NULL),
      m_id(0),
      m_vertProg(0),
      m_contProg(0),
      m_evalProg(0),
      m_geomProg(0),
      m_fragProg(0) {
    if (!m_id) m_id = glCreateProgram();

    attachVertexShader(vFileName);
    attachControlShader(tcFileName);
    attachEvaluationShader(teFileName);
    attachGeometryShader(gFileName);
    attachFragmentShader(fFileName);

    link();
}

Shader::~Shader() { cleanUp(); }

void Shader::bind() const { glUseProgram(m_id); }

void Shader::release() const { glUseProgram(0); }

void Shader::link() const {
    glLinkProgram(m_id);
    char *logstr = new char[2048];
    GLint success;
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_id, 2048, NULL, logstr);
        std::cout << "ERROR::SHADER::link() Link-time error: " << logstr
                  << std::endl;
        delete[] logstr;
    }
}

void Shader::attachVertexShader(const char *fileName) {
    if (fileName) {
        m_vFileName = fileName;
        const char *source = readFile(fileName);

        if (source) {
            m_vertProg = compile(source, GL_VERTEX_SHADER, fileName);
            glAttachShader(m_id, m_vertProg);

            // std::cout << "\tSHADER::attachVertexShader(): attached:     " <<
            // fileName << std::endl;
        } else {
            std::cout << "ERROR::SHADER::attachVertexShader(): not found: "
                      << fileName << std::endl;
        }
    }
}

void Shader::attachControlShader(const char *fileName) {
    if (fileName) {
        m_cFileName = fileName;
        const char *source = readFile(fileName);

        if (source) {
            m_contProg = compile(source, GL_TESS_CONTROL_SHADER, fileName);
            glAttachShader(m_id, m_contProg);

            // std::cout << "\tSHADER::attachControlShader(): attached:    " <<
            // fileName << std::endl;
        } else {
            std::cout << "ERROR::SHADER::attachControlShader(): not found: "
                      << fileName << std::endl;
        }
    }
}

void Shader::attachEvaluationShader(const char *fileName) {
    if (fileName) {
        m_eFileName = fileName;
        const char *source = readFile(fileName);

        if (source) {
            m_evalProg = compile(source, GL_TESS_EVALUATION_SHADER, fileName);
            glAttachShader(m_id, m_evalProg);

            // std::cout << "\tSHADER::attachEvaluationShader(): attached:" <<
            // fileName << std::endl;
        } else {
            std::cout << "ERROR::SHADER::attachEvaluationShader(): not found:"
                      << fileName << std::endl;
        }
    }
}

void Shader::attachGeometryShader(const char *fileName) {
    if (fileName) {
        m_gFileName = fileName;
        const char *source = readFile(fileName);

        if (source) {
            m_geomProg = compile(source, GL_GEOMETRY_SHADER, fileName);
            glAttachShader(m_id, m_geomProg);

            // std::cout << "\tSHADER::attachGeometryShader(): attached:  " <<
            // fileName << std::endl;
        } else {
            std::cout << "ERROR::SHADER::attachGeometryShader(): not found: "
                      << fileName << std::endl;
        }
    }
}

void Shader::attachFragmentShader(const char *fileName) {
    if (fileName) {
        m_fFileName = fileName;
        const char *source = readFile(fileName);

        if (source) {
            m_fragProg = compile(source, GL_FRAGMENT_SHADER, fileName);
            glAttachShader(m_id, m_fragProg);

            // std::cout << "\tSHADER::attachFragmentShader(): attached:  " <<
            // fileName << std::endl;
        } else {
            std::cout << "ERROR::SHADER::attachFragmentShader(): not found: "
                      << fileName << std::endl;
        }
    }
}

void Shader::attachDefault() {
    const char *vertSrc =
        "#version 400 core                                                 "
        "            \n"
        "                                                                  "
        "            \n"
        "#define VERT_POSITION 0                                           "
        "            \n"
        "#define VERT_NORMAL   1                                           "
        "            \n"
        "#define VERT_COLOR	   2                                    "
        "                   \n"
        "#define VERT_TEXTURE  3                                           "
        "            \n"
        "                                                                  "
        "            \n"
        "uniform mat4x4 matModel;                                          "
        "            \n"
        "uniform mat4x4 matView;                                           "
        "            \n"
        "uniform mat4x4 matProjection;                                     "
        "            \n"
        "                                                                  "
        "            \n"
        "layout(location = VERT_POSITION) in vec4 Position;                "
        "            \n"
        "layout(location = VERT_NORMAL)   in vec4 Normal;                  "
        "            \n"
        "layout(location = VERT_COLOR)    in vec4 Color;                   "
        "            \n"
        "layout(location = VERT_TEXTURE)  in vec4 Texture;                 "
        "            \n"
        "                                                                  "
        "            \n"
        "out vec4 VertColor;                                               "
        "            \n"
        "                                                                  "
        "            \n"
        "void main()                                                       "
        "            \n"
        "{	                                                               "
        " "
        "           \n"
        "    VertColor    = Color;                           	        "
        "               \n"
        "    gl_Position = matProjection * matView * matModel * "
        "vec4(Position.xyz, 1); \n"
        "}                                                                 "
        "            \n";

    const char *fragSrc =
        "#version 400 core           \n"
        "                            \n"
        "in vec4 VertColor;          \n"
        "                            \n"
        "void main()                 \n"
        "{                           \n"
        "   gl_FragColor = VertColor;\n"
        "}                           \n";

    attachShaderFromSource(vertSrc, GL_VERTEX_SHADER);
    attachShaderFromSource(fragSrc, GL_FRAGMENT_SHADER);
}

void Shader::attachShaderFromSource(const char *source, unsigned int type) {
    if (source) {
        if (type == GL_VERTEX_SHADER) {
            m_vertProg = compile(source, type, source);
            glAttachShader(m_id, m_vertProg);
        }

        if (type == GL_TESS_CONTROL_SHADER) {
            m_contProg = compile(source, type, source);
            glAttachShader(m_id, m_contProg);
        }

        if (type == GL_TESS_EVALUATION_SHADER) {
            m_evalProg = compile(source, type, source);
            glAttachShader(m_id, m_evalProg);
        }

        if (type == GL_GEOMETRY_SHADER) {
            m_geomProg = compile(source, type, source);
            glAttachShader(m_id, m_geomProg);
        }

        if (type == GL_FRAGMENT_SHADER) {
            m_fragProg = compile(source, type, source);
            glAttachShader(m_id, m_fragProg);
        }
    }
}

GLuint Shader::id() const { return m_id; }

void Shader::seti(const char *label, int arg) {
    glUniform1i(glGetUniformLocation(m_id, label), arg);
}

void Shader::setf(const char *label, float arg) {
    glUniform1f(glGetUniformLocation(m_id, label), arg);
}

void Shader::set2i(const char *label, int arg1, int arg2) {
    glUniform2i(glGetUniformLocation(m_id, label), arg1, arg2);
}

void Shader::set2f(const char *label, float arg1, float arg2) {
    glUniform2f(glGetUniformLocation(m_id, label), arg1, arg2);
}

void Shader::set2f(const char *label, const glm::vec2 &v) {
    glUniform2f(glGetUniformLocation(m_id, label), v.x, v.y);
}

void Shader::set3i(const char *label, int arg1, int arg2, int arg3) {
    glUniform3i(glGetUniformLocation(m_id, label), arg1, arg2, arg3);
}

void Shader::set3f(const char *label, float arg1, float arg2, float arg3) {
    glUniform3fv(glGetUniformLocation(m_id, label), 1,
                 glm::value_ptr(glm::vec3(arg1, arg2, arg3)));
}

void Shader::set3f(const char *label, const glm::vec3 &v) {
    glUniform3f(glGetUniformLocation(m_id, label), v.x, v.y, v.z);
}

void Shader::set4i(const char *label, int arg1, int arg2, int arg3, int arg4) {
    glUniform4i(glGetUniformLocation(m_id, label), arg1, arg2, arg3, arg4);
}

void Shader::set4f(const char *label, float arg1, float arg2, float arg3,
                   float arg4) {
    glUniform4f(glGetUniformLocation(m_id, label), arg1, arg2, arg3, arg4);
}

void Shader::set4f(const char *label, const glm::vec4 &v) {
    glUniform4f(glGetUniformLocation(m_id, label), v.x, v.y, v.z, v.w);
}

void Shader::set3iv(const char *label, const int *args) {
    glUniform3iv(glGetUniformLocation(m_id, label), 1, args);
}

void Shader::set3fv(const char *label, const float *args) {
    glUniform3fv(glGetUniformLocation(m_id, label), 1, args);
}

void Shader::set4fv(const char *label, const float *args) {
    glUniform4fv(glGetUniformLocation(m_id, label), 1, args);
}

void Shader::setMatrix(const char *label, const float *m, bool transpose) {
    glUniformMatrix4fv(glGetUniformLocation(m_id, label), 1, transpose, m);
}

void Shader::setMatrix(const char *label, const double *m, bool transpose) {
    float fm[] = {(float)m[0],  (float)m[1],  (float)m[2],  (float)m[3],
                  (float)m[4],  (float)m[5],  (float)m[6],  (float)m[7],
                  (float)m[8],  (float)m[9],  (float)m[10], (float)m[11],
                  (float)m[12], (float)m[13], (float)m[14], (float)m[15]};
    glUniformMatrix4fv(glGetUniformLocation(m_id, label), 1, transpose, fm);
}

void Shader::setMatrix(const char *label, const glm::mat4 &mat,
                       bool transpose) {
    glUniformMatrix4fv(glGetUniformLocation(m_id, label), 1, transpose,
                       glm::value_ptr(mat));
}

void Shader::setMatrix(const char *label, const glm::mat3 &mat,
                       bool transpose) {
    glUniformMatrix3fv(glGetUniformLocation(m_id, label), 1, transpose,
                       glm::value_ptr(mat));
}

/*=====================================================================================
        Private Functions
=====================================================================================*/
const char *Shader::readFile(const char *fileName) {
    m_shaderCode.clear();
    std::ifstream shaderFile;
    if (fileName) {
        shaderFile.open(fileName);
        std::stringstream shaderStream;

        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        m_shaderCode = shaderStream.str();
    }

    if (m_shaderCode.empty()) {
        return nullptr;
    } else {
        return m_shaderCode.c_str();
    }
}

unsigned int Shader::compile(const char *source, unsigned int type,
                             const char *filename) {
    GLuint id = glCreateShader(type);
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);

    int c = 0;

    glGetShaderiv(id, GL_COMPILE_STATUS, &c);

    if (!c) {
        char *logstr = new char[2048];
        glGetShaderInfoLog(id, 2048, NULL, logstr);
        printf("SHADER::Error compiling shader file %s:\n%s\n", filename,
               logstr);
        delete[] logstr;
        // exit(-1);
        return 0;
    }

    return id;
}

void Shader::cleanUp() {
    if (m_id) {
        if (m_vertProg) {
            glDetachShader(m_id, m_vertProg);
            glDeleteShader(m_vertProg);
            m_vertProg = 0;
        }

        if (m_contProg) {
            glDetachShader(m_id, m_contProg);
            glDeleteShader(m_contProg);
            m_contProg = 0;
        }

        if (m_evalProg) {
            glDetachShader(m_id, m_evalProg);
            glDeleteShader(m_evalProg);
            m_evalProg = 0;
        }

        if (m_geomProg) {
            glDetachShader(m_id, m_geomProg);
            glDeleteShader(m_geomProg);
            m_geomProg = 0;
        }

        if (m_fragProg) {
            glDetachShader(m_id, m_fragProg);
            glDeleteShader(m_fragProg);
            m_fragProg = 0;
        }

        glDeleteProgram(m_id);
        m_id = 0;
    }
}

void Shader::selectSubroutine(const char *label, GLenum shadertype) {
    GLuint index = glGetSubroutineIndex(m_id, shadertype, label);
    glUniformSubroutinesuiv(shadertype, 1, &index);
}
