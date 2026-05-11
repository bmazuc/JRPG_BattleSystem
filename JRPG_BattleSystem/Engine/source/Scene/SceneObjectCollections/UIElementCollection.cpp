#include "Scene/SceneObjectCollections/UIElementCollection.h"

void UIElementCollection::BeginPlay()
{
    Iterate([](UIElement* element)
        {
            element->BeginPlay();
        });
}

void UIElementCollection::Update(float deltaTime)
{
    Iterate([deltaTime](UIElement* element)
        {
            element->Update(deltaTime);
        });
}

void UIElementCollection::InitObject(UIElement* element)
{
    element->BeginPlay();
}