#include "Core/Resource/ResourceManager.h"

#include <stdexcept>

std::map<std::string, Shader*> ResourceManager::shaders;
std::map<std::string, Texture*> ResourceManager::textures;
std::map<std::string, Font*> ResourceManager::fonts;

FT_Library ResourceManager::ft;
bool ResourceManager::ftInitialized = false;

void ResourceManager::Clear()
{
    for (auto& it : shaders)
    {
        delete it.second;
        it.second = nullptr;
    }

    shaders.clear();

    for (auto& it : textures)
    {
        delete it.second;
        it.second = nullptr;
    }

    textures.clear();

    for (auto& it : fonts)
    {
        delete it.second;
        it.second = nullptr;
    }

    fonts.clear();

    if (ftInitialized)
    {
        FT_Done_FreeType(ft);
    }
}

Shader& ResourceManager::GetShader(std::string name)
{
    auto it = shaders.find(name);
    if (it != shaders.end())
    {
        return *it->second;
    }

    auto def = shaders.find("default");
    if (def != shaders.end())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Shader not found: %s, using default", name.c_str());
        return *(def->second);
    }

    throw std::runtime_error("Default shader missing!");
}

Texture& ResourceManager::GetTexture(std::string name)
{
    auto it = textures.find(name);
    if (it != textures.end())
    {
        return *it->second;
    }

    auto def = textures.find("default");
    if (def != textures.end())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Texture not found: %s, using default", name.c_str());
        return *(def->second);
    }

    throw std::runtime_error("Default texture missing!");
}

Font& ResourceManager::GetFont(std::string name)
{
    auto it = fonts.find(name);
    if (it != fonts.end())
    {
        return *it->second;
    }

    auto def = fonts.find("default");
    if (def != fonts.end())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Font not found: %s, using default", name.c_str());
        return *(def->second);
    }

    throw std::runtime_error("Default font missing!");
}

Shader& ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, std::string name)
{
    Shader* shader = new Shader(vShaderFile, fShaderFile);
    shaders[name] = shader;
    return *shader;
}

Texture& ResourceManager::LoadPNGTexture(const char* file, std::string name)
{
    Texture* texture = new Texture();
    texture->LoadPNG(file);
    textures[name] = texture;
    return *texture;
}

Texture& ResourceManager::LoadBMPTexture(const char* file, std::string name)
{
    Texture* texture = new Texture();
    texture->LoadBMP(file);
    textures[name] = texture;
    return *texture;
}

Font& ResourceManager::LoadFont(const char* file, unsigned int size, std::string name)
{
    InitFreeType();

    Font* font = new Font();
    font->Load(ft, file, size);

    fonts[name] = font;
    return *font;
}

void ResourceManager::InitFreeType()
{
    if (!ftInitialized)
    {
        if (FT_Init_FreeType(&ft))
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to init FreeType");
        }
        ftInitialized = true;
    }
}