#ifndef __RESOURCE_MANAGER_H_INCLUDED__
#define __RESOURCE_MANAGER_H_INCLUDED__

#include "Graphics/Texture.h"
#include "Rendering/Shader.h"
#include "Graphics/Font.h"

#include <map>
#include <string>

/*
 *  Static resource manager.
 *  Load resources from files, global access from std::string,
 *  auto fallback toward "default" (load in Engine class), resources
 *  global clear
 */
class ResourceManager
{
public:
    // List of loaded shaders
    static std::map<std::string, Shader*> shaders;
    // List of loaded textures
    static std::map<std::string, Texture*> textures;
    // List of loaded fonts
    static std::map<std::string, Font*> fonts;

    /*
     *  Load and compile a shader.
     *  @param vShaderFile vertex shader file
     *  @param fShaderFile fragment shader file
     *  @param name the key used to register the shader
     *  @return the loaded shader
     */
    static Shader& LoadShader(const char* vShaderFile, const char* fShaderFile, std::string name);
    /*
     *  Find a shader by its key.
     *  @param name the key used to register the shader
     *  @return the shader or default one if shader didn't exist
     */
    static Shader& GetShader(std::string name);

    /*
     *  Load a png texture.
     *  @param file texture file
     *  @param name the key used to register the font
     *  @return the loaded texture
     */
    static Texture& LoadPNGTexture(const char* file, std::string name);
    /*
     *  Load a bmp texture.
     *  @param file texture file
     *  @param name the key used to register the font
     *  @return the loaded texture
     */
    static Texture& LoadBMPTexture(const char* file, std::string name);
    /*
     *  Find a texture by its key.
     *  @param name the key used to register the texture
     *  @return the texture or default one if texture didn't exist
     */
    static Texture& GetTexture(std::string name);

    /*
     *  Load a font with FreeType.
     *  @param file font file
     *  @param size pixel font size
     *  @param name the key used to register the font
     *  @return the loaded font
     */
    static Font& LoadFont(const char* file, unsigned int size, std::string name);
    /*
     *  Find a font by its key.
     *  @param name the key used to register the font
     *  @return the font or default one if font didn't exist
     */
    static Font& GetFont(std::string name);

    /*
     *  Clear all loaded resources.
     */
    static void Clear();

private:
    // private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
    ResourceManager() {}

    // Initialiaze FreeType
    static void InitFreeType();

    // An handle to a FreeType library instance.
    static FT_Library ft;
    // Are freetype already initialized ?
    static bool ftInitialized;
};

#endif // __RESOURCE_MANAGER_H_INCLUDED__