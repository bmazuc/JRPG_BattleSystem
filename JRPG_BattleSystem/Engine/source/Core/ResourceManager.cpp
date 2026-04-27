#include "Core/ResourceManager.h"

#include <stdexcept>

std::map<std::string, Shader*> ResourceManager::shaders;
std::map<std::string, Texture*> ResourceManager::textures;

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

    auto def = textures.find("missing");
    if (def != textures.end())
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Texture not found: %s, using default", name.c_str());
        return *(def->second);
    }

    throw std::runtime_error("Default texture missing!");
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
