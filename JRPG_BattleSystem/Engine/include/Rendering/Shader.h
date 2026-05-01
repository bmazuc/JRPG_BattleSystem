#ifndef __SHADER_H_INCLUDED__
#define __SHADER_H_INCLUDED__

#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

/*
 *	OpenGL shader wrapper.
 *	Manage :
 *	- load and compilation (vertex + fragment)
 *	- OpenGL program use.
 *	- Uniforms sending
 * 
 *	Only vertex and fragment shaders are handle. Could be improve
 *  by adding geometry shader handling.
 */
class Shader
{
public:
	Shader(const char* vShaderFile, const char* fShaderFile);

	// sets the current shader as active
	void Use();

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
	void Compile(const char* vertexSource, const char* fragmentSource);
	// utility function for checking shader compilation/linking errors.
	void CheckCompileErrors(unsigned int shader, std::string type);

	unsigned int ID;
};

#endif // __SHADER_H_INCLUDED__