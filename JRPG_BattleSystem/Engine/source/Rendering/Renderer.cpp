#include "Rendering/Renderer.h"
#include "Scene/Scene.h"
#include "Components/Camera/CameraComponent.h"

#include <GL/glew.h>
#include <glm/ext/matrix_transform.hpp>

#include "Components/Rendering/SpriteRendererComponent.h"
#include "Rendering/Shader.h"
#include <glm/ext/matrix_clip_space.hpp>

#include "UI/Image.h"
#include "Rendering/Material.h"
#include "Graphics/Font.h"
#include "UI/Text.h"
#include "Core/Resource/ResourceManager.h"

Renderer::~Renderer()
{
    buckets.clear();
}

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

void Renderer::RenderWorld(Scene* scene, glm::vec2 viewportBaseResolution)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    CameraComponent* camera = scene->GetActiveCamera();
    if (camera)
    {
        Build(scene);

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::scale(view, glm::vec3(camera->GetZoom(), camera->GetZoom(), 1.0f));
        view = glm::rotate(view, glm::radians(-camera->GetRotate()), glm::vec3(0.0f, 0.0f, 1.0f));
        view = glm::translate(view, glm::vec3(-camera->GetPosition(), 0.0f));

        glm::mat4 projection = glm::ortho(0.0f, viewportBaseResolution.x, viewportBaseResolution.y, 0.0f, -1.0f, 1.0f);

        for (auto it = buckets.begin(); it != buckets.end(); ++it)
        {
            int layer = it->first;
            std::vector<SpriteRendererComponent*>& spriteRenderers = it->second;

            for (SpriteRendererComponent* spriteRenderer : spriteRenderers)
            {
                if (!spriteRenderer)
                {
                    continue;
                }
                
                glm::mat4 model = glm::scale(spriteRenderer->GetTransform().world, glm::vec3(spriteRenderer->GetSize(), 1.0f));
                RenderMaterial(spriteRenderer->GetMaterial(), view, model, projection);
            }
        }
    }
}

void Renderer::RenderUI(Scene* scene, glm::vec2 windowSize)
{
    glm::mat4 projection = glm::ortho(0.0f, windowSize.x, windowSize.y, 0.0f, -1.0f, 1.0f);

    std::vector<UIElement*> uiElements = scene->GetUIElements();
    for (UIElement* element : uiElements)
    {
        if (Image* image = dynamic_cast<Image*>(element))
        {
            glm::mat4 model = glm::scale(image->GetWorld(), glm::vec3(image->GetSize(), 1.0f));
            RenderMaterial(image->GetMaterial(), glm::mat4(1.0f), model, projection);
        }
        else if (Text* text = dynamic_cast<Text*>(element))
        {
            RenderText(text, projection);
        }
    }
}

void Renderer::Build(Scene* scene)
{
    buckets.clear();

    std::vector<Actor*> gameObjects = scene->GetActors();
    for (Actor* gameObject : gameObjects)
    {
        if (gameObject)
        {
            SpriteRendererComponent* spriteRenderer = gameObject->GetComponent<SpriteRendererComponent>();

            if (spriteRenderer)
            {
                buckets[spriteRenderer->GetLayer()].push_back(spriteRenderer);
            }
        }
    }
}

void Renderer::RenderMaterial(Material* material, glm::mat4 view, glm::mat4 model, glm::mat4 projection)
{
    if (!material)
    {
        return;
    }

    Shader* shader = material->GetShader();
    if (!shader)
    {
        return;
    }

    shader->Use();
    shader->SetInteger("image", 0);
    shader->SetMatrix4("view", view);
    shader->SetMatrix4("model", model);
    shader->SetMatrix4("projection", projection);
    shader->SetVector3f("spriteColor", material->GetColor());

    DrawTexture(material->GetTexture());
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

void Renderer::RenderText(Text* text, glm::mat4 projection)
{
    Font* font = text->GetFont();
    if (!font)
    {
        return;
    }

    textShader->Use();

    textShader->SetMatrix4("projection", projection);
    textShader->SetVector3f("textColor", text->GetColor());

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(textVAO);

    glm::vec2 position = text->GetWorldPosition();
    float x = position.x;
    float y = position.y;

    float fontSize = (float)font->GetSize();
    if (fontSize == 0.0f)
    {
        fontSize = 0.01f;
    }

    glm::vec2 scale = text->GetWorldScale();

    if (text->GetScaleMode() == TextScaleMode::Uniform)
    {
        float uniformScale = std::min(scale.x, scale.y);
        scale = glm::vec2(uniformScale, uniformScale);
    }
    
    glm::vec2 finalScale = scale * (text->GetSize()/ fontSize);

    std::string content = text->GetContent();
    if (text->IsCenter())
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