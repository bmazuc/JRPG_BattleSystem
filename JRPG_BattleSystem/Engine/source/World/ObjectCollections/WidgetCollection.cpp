#include "World/ObjectCollections/WidgetCollection.h"
#include "UI/UserWidget.h"

void WidgetCollection::Construct()
{
    InitObject([](Widget* widget)
        {
            if (UserWidget* userWidget = dynamic_cast<UserWidget*>(widget))
            {
                userWidget->NativeConstruct();
            }
        });
}

void WidgetCollection::Update(float deltaTime)
{
    ForEach([deltaTime](Widget* widget)
        {
            if (UserWidget* userWidget = dynamic_cast<UserWidget*>(widget))
            {
                userWidget->Update(deltaTime);
            }
        });
}

void WidgetCollection::BeginDestroyObject(Widget* widget)
{
    widget->NativeBeginDestroy();
}