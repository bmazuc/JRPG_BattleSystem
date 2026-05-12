#ifndef __SHADER_H_INCLUDED__
#define __SHADER_H_INCLUDED__

#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

/**
 * Wrapper around an OpenGL shader program.
 *
 * Handles:
 * - compilation (vertex + fragment shaders)
 * - program linking
 * - uniform updates
 */
class Shader
{
public:
	/**
	 * Creates and compiles a shader program.
	 *
	 * @param vShaderFile Vertex shader source file.
	 * @param fShaderFile Fragment shader source file.
	 */
	Shader(const char* vShaderFile, const char* fShaderFile);

	/**
	 * Activates this shader for rendering.
	 */
	void Use();

	/**
	 * Uniforms setters
	 */

	void SetFloat(const char* name, float value);
	void SetInteger(const char* name, int value);
	void SetVector2f(const char* name, float x, float y);
	void SetVector2f(const char* name, const glm::vec2& value);
	void SetVector3f(const char* name, float x, float y, float z);
	void SetVector3f(const char* name, const glm::vec3& value);
	void SetVector4f(const char* name, float x, float y, float z, float w);
	void SetVector4f(const char* name, const glm::vec4& value);
	void SetMatrix4(const char* name, const glm::mat4& matrix);

private:
	/**
	 * Compiles and links shader sources into a program.
	 */
	void Compile(const char* vertexSource, const char* fragmentSource);
	
	/**
	 * Checks and logs shader compilation/linking errors.
	 */
	void CheckCompileErrors(unsigned int shader, std::string type);

	unsigned int ID = 0;
};

#endif // __SHADER_H_INCLUDED__