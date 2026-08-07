#include "Rendering/Renderer.h"

#include <GL/glew.h>

#include "Components/Camera/CameraComponent.h"
#include "Core/Resource/ResourceManager.h"
#include "Graphics/Font.h"
#include "Rendering/Material.h"
#include "Graphics/Texture.h"
#include "Rendering/Shader.h"
#include "UI/Text.h"
#include "World/World.h"
#include "World/Level/Level.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

void Renderer::Init()
{
    InitRenderData();
    textShader = &ResourceManager::GetShader("text");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::InitRenderData()
{
    // configure VAO/VBO
    unsigned int VBO;
    float vertices[] = {
        // pos      // tex
        -0.5f, 0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.0, 1.0f,
        0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 1.0f, 0.0f
    };

    // Generate quad VAO
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Generate text VAO & VBO

    glGenVertexArrays(1, &textVAO);
    glGenBuffers(1, &textVBO);

    glBindVertexArray(textVAO);
    glBindBuffer(GL_ARRAY_BUFFER, textVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    glBindVertexArray(0);
}

void Renderer::RenderWorld(World* world, glm::vec2 viewportBaseResolution)
{
    RenderQueue queue;
    world->BuildRenderQueue(queue);

    RenderScene(queue.worldBuckets, world->GetActiveLevel()->GetScene()->GetActiveCamera(), viewportBaseResolution);
    RenderUI(queue.uiItems, viewportBaseResolution);

    queue.Clear();
}

void Renderer::RenderScene(RenderBucket& buckets, CameraComponent* camera, glm::vec2 viewportBaseResolution)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (camera)
    {
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::scale(view, glm::vec3(camera->GetZoom(), camera->GetZoom(), 1.0f));
        view = glm::rotate(view, glm::radians(-camera->GetWorldRotate()), glm::vec3(0.0f, 0.0f, 1.0f));
        view = glm::translate(view, glm::vec3(-camera->GetWorldPosition(), 0.0f));

        glm::mat4 projection = glm::ortho(0.0f, viewportBaseResolution.x, viewportBaseResolution.y, 0.0f, -1.0f, 1.0f);

        for (auto it = buckets.begin(); it != buckets.end(); ++it)
        {
            int zOrder = it->first;
            std::vector<RenderItem*>& items = it->second;

            for (RenderItem* item : items)
            { 
                if (RenderTextureItem* textureItem = dynamic_cast<RenderTextureItem*>(item))
                {
                    RenderMaterial(textureItem, view, projection);
                }
            }
        }
    }
}

void Renderer::RenderUI(std::vector<RenderItem*>& uiItems, glm::vec2 viewportBaseResolution)
{
    glm::mat4 projection = glm::ortho(0.0f, viewportBaseResolution.x, viewportBaseResolution.y, 0.0f, -1.0f, 1.0f);

    for (RenderItem* item : uiItems)
    {
        if (RenderTextureItem* textureItem = dynamic_cast<RenderTextureItem*>(item))
        {
            RenderMaterial(textureItem, glm::mat4(1.0f), projection);
        }
        else if (RenderTextItem* textItem = dynamic_cast<RenderTextItem*>(item))
        {
            RenderText(textItem, projection);
        }
    }
}

void Renderer::RenderMaterial(RenderTextureItem* item, glm::mat4 view, glm::mat4 projection)
{
    if (!item->material)
    {
        return;
    }

    Shader* shader = item->material->GetShader();
    if (!shader)
    {
        return;
    }

    glm::mat4 model = glm::scale(item->world, glm::vec3(item->size, 1.0f));

    shader->Use();
    shader->SetInteger("image", 0);
    shader->SetMatrix4("view", view);
    shader->SetMatrix4("model", model);
    shader->SetMatrix4("projection", projection);
    shader->SetVector4f("spriteColor", item->material->GetColor());

    DrawTexture(item->material->GetTexture());
}

void Renderer::DrawTexture(Texture* texture)
{
    if (texture)
    {
        glActiveTexture(GL_TEXTURE0);
        texture->BindTexture();

        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
}

void Renderer::RenderText(RenderTextItem* item, glm::mat4 projection)
{
    Font* font = item->font;
    if (!font)
    {
        return;
    }

    textShader->Use();

    textShader->SetMatrix4("projection", projection);
    textShader->SetVector4f("textColor", item->color);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(textVAO);

    glm::vec2 position = glm::vec2(item->world[3]);
    float x = position.x;
    float y = position.y;

    float fontSize = (float)font->GetSize();
    if (fontSize == 0.0f)
    {
        fontSize = 0.01f;
    }

    glm::vec2 scale;
    scale.x = glm::length(glm::vec2(item->world[0]));
    scale.y = glm::length(glm::vec2(item->world[1]));

    if (item->scaleMode == TextScaleMode::Uniform)
    {
        float uniformScale = std::min(scale.x, scale.y);
        scale = glm::vec2(uniformScale, uniformScale);
    }
    
    glm::vec2 finalScale = scale * (item->size/ fontSize);

    std::string content = item->content;
    if (item->isCenterX)
    {
        float totalWidth = 0.0f;

        for (char c : content)
        {
            Glyph g = font->GetGlyph(c);
            totalWidth += (g.advance >> 6) * finalScale.x;
        }

        x -= totalWidth * 0.5f;
        y -= font->GetGlyph('H').size.y * finalScale.y * 0.5f;
    }

    for (char c : content)
    {
        Glyph g = font->GetGlyph(c);

        float xpos = x + g.bearing.x * finalScale.x;
        float ypos = y + (font->GetGlyph('H').bearing.y - g.bearing.y) * finalScale.y;

        float w = g.size.x * finalScale.x;
        float h = g.size.y * finalScale.y;

        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f },
            { xpos,     ypos,       0.0f, 0.0f },

            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f }
        };

        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, g.textureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, textVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (g.advance >> 6) * finalScale.x; // bitshift by 6 to get value in pixels (2^6 = 64)
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}