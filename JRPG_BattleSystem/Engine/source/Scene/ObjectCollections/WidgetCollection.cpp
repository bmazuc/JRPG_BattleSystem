#include "Scene/ObjectCollections/WidgetCollection.h"
#include "UI/UserWidget.h"

void WidgetCollection::Construct()
{
    Iterate([](Widget* widget)
        {
            if (UserWidget* userWidget = dynamic_cast<UserWidget*>(widget))
            {
                userWidget->Construct();
            }
        });
}

void WidgetCollection::Update(float deltaTime)
{
    Iterate([deltaTime](Widget* widget)
        {
            if (UserWidget* userWidget = dynamic_cast<UserWidget*>(widget))
            {
                userWidget->Update(deltaTime);
            }
        });
}

void WidgetCollection::InitObject(Widget* widget)
{
    if (UserWidget* userWidget = dynamic_cast<UserWidget*>(widget))
    {
        userWidget->Construct();
    }
}

void WidgetCollection::BeginDestroyObject(Widget* widget)
{
    widget->BeginDestroy();
}