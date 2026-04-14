#include "Texture.h"

void Texture::LoadBMP(const char* file)
{
	CreateTexture(SDL_LoadBMP(file));
}

void Texture::LoadPNG(const char* file)
{
	CreateTexture(SDL_LoadPNG(file));
}

void Texture::CreateTexture(SDL_Surface* surface)
{
    if (surface)
    {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        GLenum format = GetGLFormat(surface->format);

        glTexImage2D(GL_TEXTURE_2D, 0, format,
            surface->w, surface->h,
            0, format,
            GL_UNSIGNED_BYTE,
            surface->pixels);

        SDL_DestroySurface(surface);
    }
}

GLenum Texture::GetGLFormat(SDL_PixelFormat format)
{
    switch (format) {
    case SDL_PIXELFORMAT_RGBA32:
        return GL_RGBA;

    case SDL_PIXELFORMAT_RGB24:
        return GL_RGB;

    case SDL_PIXELFORMAT_BGRA32:
        return GL_BGRA;

    case SDL_PIXELFORMAT_BGR24:
        return GL_BGR;

    default:
        return GL_RGBA; // fallback safe
    }
}

void Texture::Render()
{
    glBindTexture(GL_TEXTURE_2D, texture);
}