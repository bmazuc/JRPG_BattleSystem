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
	void LoadBMP(const char* file);
	void LoadPNG(const char* file);

	void BindTexture();

private:
	void CreateTexture(SDL_Surface* surface);
	GLenum GetGLFormat(SDL_PixelFormat format);

	GLuint texture;
};

#endif // __TEXTURE_H_INCLUDED__