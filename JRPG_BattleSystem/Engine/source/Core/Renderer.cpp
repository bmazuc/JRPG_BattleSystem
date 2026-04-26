#include "Core/Renderer.h"
#include "Scene/Scene.h"
#include "Components/CameraComponent.h"

#include <GL/glew.h>
#include <glm/ext/matrix_transform.hpp>

#include "Graphics/Sprite.h"
#include "Components/SpriteRendererComponent.h"
#include "Core/Shader.h"
#include <glm/ext/matrix_clip_space.hpp>

Renderer::~Renderer()
{
    buckets.clear();

    delete shader;
    shader = nullptr;
}

void Renderer::Init(const char* vShaderFile, const char* fShaderFile, glm::vec2 viewportBaseResolution)
{
    shader = new Shader(vShaderFile, fShaderFile);

    InitRenderData(viewportBaseResolution);
}

void Renderer::InitRenderData(glm::vec2 viewportBaseResolution)
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

void Renderer::Render(Scene* scene, SDL_Window* window)
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

        shader->SetMatrix4("view", view);

        for (auto it = buckets.begin(); it != buckets.end(); ++it)
        {
            int layer = it->first;
            std::vector<SpriteRendererComponent*>& sprites = it->second;

            for (SpriteRendererComponent* s : sprites)
            {
                DrawSprite(s, window);
            }
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
                Sprite* sprite = spriteRenderer->GetSprite();
                buckets[sprite->GetLayer()].push_back(spriteRenderer);
            }
        }
    }
}

void Renderer::DrawSprite(SpriteRendererComponent* sprite, SDL_Window* window)
{
    if (sprite)
    {
        Sprite* s = sprite->GetSprite();

        glm::mat4 model = sprite->GetTransform().world;
        model = glm::scale(model, glm::vec3(s->GetSize(), 1.0f));

        shader->SetMatrix4("model", model);
        shader->SetVector3f("spriteColor", s->GetColor());

        glActiveTexture(GL_TEXTURE0);
        s->GetTexture()->Render();

        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
}

