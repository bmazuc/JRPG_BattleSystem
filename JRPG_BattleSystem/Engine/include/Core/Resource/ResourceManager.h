#ifndef __RESOURCE_MANAGER_H_INCLUDED__
#define __RESOURCE_MANAGER_H_INCLUDED__

#include "Graphics/Texture.h"
#include "Rendering/Shader.h"
#include "Graphics/Font.h"

#include <map>
#include <string>

/**
 * Static resource manager responsible for loading and caching assets.
 */
class ResourceManager
{
public:
    static std::map<std::string, Shader*> shaders;
    static std::map<std::string, Texture*> textures;
 
    static std::map<std::string, Font*> fonts;

    /*
     * Load and compile a shader program.
     * @param vShaderFile vertex shader file
     * @param fShaderFile fragment shader file
     * @param name the key used to register the shader
     * @return the loaded shader
     */
    static Shader& LoadShader(const char* vShaderFile, const char* fShaderFile, std::string name);
    /*
     * Retrieves a shader by name.
     * Returns the default shader if not found.
     */
    static Shader& GetShader(std::string name);

    /*
     * Load a png texture.
     * @param file texture file
     * @param name the key used to register the font
     * @return the loaded texture
     */
    static Texture& LoadPNGTexture(const char* file, std::string name);
    /*
     * Load a bmp texture.
     * @param file texture file
     * @param name the key used to register the font
     * @return the loaded texture
     */
    static Texture& LoadBMPTexture(const char* file, std::string name);
    /*
     * Retrieves a texture by name.
     * Returns the default texture if not found.
     */
    static Texture& GetTexture(std::string name);

    /*
     * Load a font with FreeType.
     * @param file font file
     * @param size pixel font size
     * @param name the key used to register the font
     * @return the loaded font
     */
    static Font& LoadFont(const char* file, unsigned int size, std::string name);
    /*
     * Retrieves a font by name.
     * Returns the default font if not found.
     */
    static Font& GetFont(std::string name);

    // Clear all loaded resources.
    static void Clear();

private:
    // private constructor, that is we do not want any actual resource manager objects.
    ResourceManager() {}

    // Initialiaze FreeType
    static void InitFreeType();

    // An handle to a FreeType library instance.
    static FT_Library ft;
    // Are freetype already initialized ?
    static bool ftInitialized;
};

#endif // __RESOURCE_MANAGER_H_INCLUDED__