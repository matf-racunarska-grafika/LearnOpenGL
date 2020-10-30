//
// Created by spaske on 22.10.20..
//

#ifndef PROJECT_BASE_ERROR_H
#define PROJECT_BASE_ERROR_H

#include <iostream>
#include <glad/glad.h>

#define BREAK_IF_FALSE(x) if (!(x)) __builtin_trap()
#define ASSERT(x, msg) do { if (!(x)) { std::cerr << msg << '\n'; BREAK_IF_FALSE(false); } } while(0)
#define GLCALL(x) \
do{ rg::clearAllOpenGlErrors(); x; BREAK_IF_FALSE(rg::wasPreviousOpenGLCallSuccessful(__FILE__, __LINE__, #x)); } while (0)

namespace rg {

    
void clearAllOpenGlErrors();
const char* openGLErrorToString(GLenum error);
bool wasPreviousOpenGLCallSuccessful(const char* file, int line, const char* call);

    void clearAllOpenGlErrors() {
        while (glGetError() != GL_NO_ERROR) {
            ;
        }
    }
    const char* openGLErrorToString(GLenum error) {
        switch(error) {
            case GL_NO_ERROR: return "GL_NO_ERROR";
            case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
            case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
            case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
            case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
        }
        ASSERT(false, "Passed something that is not an error code");
        return "THIS_SHOULD_NEVER_HAPPEN";
    }
    bool wasPreviousOpenGLCallSuccessful(const char* file, int line, const char* call) {
        bool success = true;
        while (GLenum error = glGetError()) {
            std::cerr << "[OpenGL error] " << error << " " << openGLErrorToString(error)
            << "\nFile: " << file
            << "\nLine: " << line
            << "\nCall: " << call
            << "\n\n";
            success = false;
        }
        return success;
    }

};
#endif //PROJECT_BASE_ERROR_H
