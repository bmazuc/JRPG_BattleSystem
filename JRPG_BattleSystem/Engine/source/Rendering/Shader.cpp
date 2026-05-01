#include "Rendering/Shader.h"

#include <sstream>
#include <fstream>

#include <GL/glew.h>
#include <SDL3/SDL.h>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char* vShaderFile, const char* fShaderFile)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;

    try
    {
        // open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "VSync not supported: %s", e.what());
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    Compile(vShaderCode, fShaderCode);
}

void Shader::Compile(const char* vertexSource, const char* fragmentSource)
{
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexSource, NULL);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentSource, NULL);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    CheckCompileErrors(ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::Use()
{
	glUseProgram(ID);
}

void Shader::CheckCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "ERROR::SHADER_COMPILATION_ERROR of type:: %s \n %s", type, infoLog);
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "ERROR::PROGRAM_LINKING_ERROR of type:: %s \n %s", type, infoLog);
        }
    }
}

void Shader::SetFloat(const char* name, float value)
{
    glUniform1f(glGetUniformLocation(this->ID, name), value);
}

void Shader::SetInteger(const char* name, int value)
{
    glUniform1i(glGetUniformLocation(this->ID, name), value);
}

void Shader::SetVector2f(const char* name, float x, float y)
{
    glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}

void Shader::SetVector2f(const char* name, const glm::vec2& value)
{
    glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}

void Shader::SetVector3f(const char* name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}

void Shader::SetVector3f(const char* name, const glm::vec3& value)
{
    glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}

void Shader::SetVector4f(const char* name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}

void Shader::SetVector4f(const char* name, const glm::vec4& value)
{
    glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4(const char* name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, false, glm::value_ptr(matrix));
}
