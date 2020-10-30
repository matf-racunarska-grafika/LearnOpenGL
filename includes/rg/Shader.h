//
// Created by matf-rg on 30.10.20..
//

#ifndef PROJECT_BASE_SHADER_H
#define PROJECT_BASE_SHADER_H

#include <string>
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <rg/Error.h>
std::string readFileContents(std::string path) {
    std::ifstream in(path);
    std::stringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}

class Shader {
    unsigned int m_Id;
public:
    Shader(std::string vertexShaderPath, std::string fragmentShaderPath) {
        // build and compile our shader program
        // ------------------------------------
        // vertex shader
        std::string vsString = readFileContents(vertexShaderPath);
        ASSERT(!vsString.empty(), "Vertex shader source is empty!");
        const char* vertexShaderSource = vsString.c_str();
        int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // fragment shader
        int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        std::string fsString = readFileContents(fragmentShaderPath);
        ASSERT(!fsString.empty(), "Fragment shader empty!");
        const char* fragmentShaderSource = fsString.c_str();
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        // check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // link shaders
        int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        // check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        m_Id = shaderProgram;
    }

    void use() {
        ASSERT(m_Id > 0, "Use of unidefned or delete program!");
        glUseProgram(m_Id);
    }

    void setUniform4f(std::string name, float x, float y, float z, float w) {
        int uniformId = glGetUniformLocation(m_Id, name.c_str());
        glUniform4f(uniformId, x, y, z, w);
    }

    void setUniform1i(std::string name, int value) {
        int uniformId = glGetUniformLocation(m_Id, name.c_str());
        glUniform1i(uniformId, value);
    }

    void deleteProgram() {
        glDeleteProgram(m_Id);
        m_Id = 0;
    }


    void setUniform1f(std::string name, double value) {
        int uniformId = glGetUniformLocation(m_Id, name.c_str());
        glUniform1f(uniformId, value);
    }
};


#endif //PROJECT_BASE_SHADER_H
