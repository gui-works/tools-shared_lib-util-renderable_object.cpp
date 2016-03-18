#ifndef SHADER_H
#define SHADER_H

#include "headers.h"

class Shader {
public:
    Shader();
    Shader(const char *vFileName, const char *fFileName);

    Shader(const char *vFileName, const char *gFileName, const char *fFileName);

    Shader(const char *vFileName, const char *tcFileName,
           const char *teFileName, const char *gFileName, const char *fFileName);

    virtual ~Shader();

    GLuint id() const;

    void bind() const;
    void release() const;
    void link() const;

    void attachVertexShader(const char *fileName);
    void attachControlShader(const char *fileName);
    void attachEvaluationShader(const char *fileName);
    void attachGeometryShader(const char *fileName);
    void attachFragmentShader(const char *fileName);
    void attachDefault();
    void attachShaderFromSource(const char *source, unsigned int type);

    // Setup Uniforms
    void seti(const char *label, int arg);
    void setf(const char *label, float arg);
    void set2i(const char *label, int arg1, int arg2);
    void set2f(const char *label, float arg1, float arg2);
    void set2f(const char *label, const glm::vec2 &v);
    void set3i(const char *label, int arg1, int arg2, int arg3);
    void set3f(const char *label, float arg1, float arg2, float arg3);
    void set3f(const char *label, const glm::vec3 &v);
    void set4i(const char *label, int arg1, int arg2, int arg3, int arg4);
    void set4f(const char *label, float arg1, float arg2, float arg3,
               float arg4);
    void set4f(const char *label, const glm::vec4 &v);
    void set3iv(const char *label, const int *args);
    void set3fv(const char *label, const float *args);
    void set4fv(const char *label, const float *args);
    void setMatrix(const char *label, const float *m, bool transpose = false);
    void setMatrix(const char *label, const double *m, bool transpose = false);
    void setMatrix(const char *label, const glm::mat4 &mat,
                   bool transpose = false);
    void setMatrix(const char *label, const glm::mat3 &mat,
                   bool transpose = false);

    // Setup Subroutines
    // - shadertype: GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, etc.
    void selectSubroutine(const char *label, GLenum shadertype);

private:
    GLuint m_id;

    const char *m_vFileName;
    const char *m_cFileName;
    const char *m_eFileName;
    const char *m_gFileName;
    const char *m_fFileName;

    unsigned int m_vertProg;
    unsigned int m_contProg;
    unsigned int m_evalProg;
    unsigned int m_geomProg;
    unsigned int m_fragProg;

    const char *readFile(const char *fileName);
    unsigned int compile(const char *source, unsigned int type,
                         const char *filename);
    void cleanUp();

    string m_shaderCode;
};

#endif
