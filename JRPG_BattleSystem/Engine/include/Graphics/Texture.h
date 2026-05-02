#ifndef __TEXTURE_H_INCLUDED__
#define __TEXTURE_H_INCLUDED__

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

/*
 *	Represent an OpenGL texture.
 *	Can be load from BMP or PNG.
 */
class Texture
{
public:
	/*
	 *  Load the texture from a BMP file.
	 *  @param file texture file
	 */
	void LoadBMP(const char* file);
	/*
	 *  Load the texture from a PNG file.
	 *  @param file texture file
	 */
	void LoadPNG(const char* file);

	// Bind texture for rendering
	void BindTexture();

private:
	/*
	 *	Create the texture from a SDL surface ( A collection of pixels used in software blitting)
	 *	@param surface the SDL surface
	 */
	void CreateTexture(SDL_Surface* surface);
	/*
	 *	Convert a SDL format to an OpenGL format.
	 *	@param format the SDL format
	 *	@return OpenGL format
	 */
	GLenum GetGLFormat(SDL_PixelFormat format);

	// texture name for OpenGL
	GLuint texture;
};

#endif // __TEXTURE_H_INCLUDED__