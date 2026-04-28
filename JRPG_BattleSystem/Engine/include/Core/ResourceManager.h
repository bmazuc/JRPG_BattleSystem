#ifndef __RESOURCE_MANAGER_H_INCLUDED__
#define __RESOURCE_MANAGER_H_INCLUDED__

#include "Graphics/Texture.h"
#include "Core/Shader.h"
#include "Graphics/Font.h"

#include <map>
#include <string>

class ResourceManager
{
public:
    static std::map<std::string, Shader*> shaders;
    static std::map<std::string, Texture*> textures;
    static std::map<std::string, Font*> fonts;

    static Shader& LoadShader(const char* vShaderFile, const char* fShaderFile, std::string name);
    static Shader& GetShader(std::string name);

    static Texture& LoadPNGTexture(const char* file, std::string name);
    static Texture& LoadBMPTexture(const char* file, std::string name);
    static Texture& GetTexture(std::string name);

    static Font& LoadFont(const char* file, unsigned int size, std::string name);
    static Font& GetFont(std::string name);

    static void Clear();

private:
    // private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
    ResourceManager() {}

    static void InitFreeType();

    static FT_Library ft;
    static bool ftInitialized;
};

#endif // __RESOURCE_MANAGER_H_INCLUDED__