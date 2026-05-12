#ifndef __TEXTURE_H_INCLUDED__
#define __TEXTURE_H_INCLUDED__

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

/**
 * Wrapper around an OpenGL texture resource.
 */
class Texture
{
public:
	/**
	 * Loads a texture from a BMP file.
	 */
	void LoadBMP(const char* file);

	/**
	 * Loads a texture from a PNG file.
	 */
	void LoadPNG(const char* file);


	/**
	 * Binds the texture for rendering.
	 */
	void BindTexture();

private:
	/**
	 * Creates an OpenGL texture from an SDL surface.
	 */
	void CreateTexture(SDL_Surface* surface);

	/**
	 * Converts an SDL pixel format to its OpenGL equivalent.
	 */
	GLenum GetGLFormat(SDL_PixelFormat format);

	// OpenGL texture identifier.
	GLuint texture = 0;
};

#endif // __TEXTURE_H_INCLUDED__