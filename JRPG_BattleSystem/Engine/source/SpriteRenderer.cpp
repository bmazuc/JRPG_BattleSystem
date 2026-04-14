#include "SpriteRenderer.h"

#include <GL/glew.h>
#include <glm/ext/matrix_transform.hpp>

#include "Sprite.h"
#include "Shader.h"
#include <glm/ext/matrix_clip_space.hpp>

SpriteRenderer::~SpriteRenderer()
{
    delete shader;
    shader = nullptr;
}

void SpriteRenderer::InitShader(const char* vShaderFile, const char* fShaderFile)
{
    shader = new Shader(vShaderFile, fShaderFile);
}

void SpriteRenderer::Render(SDL_Window* window)
{
    if (shader)
    {
        shader->Use();
        for (int idx = 0; idx < sprites.size(); ++idx)
        {
            RenderSprite(sprites[idx], window);
        }
    }
}

void SpriteRenderer::InitRenderData(glm::vec2 viewportBaseResolution)
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

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    if (shader)
    {
        shader->Use();
        shader->SetInteger("image", 0);
        glm::mat4 projection = glm::ortho(0.0f, viewportBaseResolution.x, viewportBaseResolution.y, 0.0f, -1.0f, 1.0f);
        shader->SetMatrix4("projection", projection);
    }

}

void SpriteRenderer::RenderSprite(Sprite* sprite, SDL_Window* window)
{
    if (sprite)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(sprite->GetPosition(), 0.0f));

        model = glm::translate(model, glm::vec3(0.5f * sprite->GetSize().x, 0.5f * sprite->GetSize().y, 0.0f));
        model = glm::rotate(model, glm::radians(sprite->GetRotate()), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, glm::vec3(-0.5f * sprite->GetSize().x, -0.5f * sprite->GetSize().y, 0.0f));

        model = glm::scale(model, glm::vec3(sprite->GetSize(), 1.0f));

        shader->SetMatrix4("model", model);
        shader->SetVector3f("spriteColor", sprite->GetColor());

        glActiveTexture(GL_TEXTURE0);
        sprite->GetTexture()->Render();

        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
}

