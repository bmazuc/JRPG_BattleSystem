#include "UI/WidgetOrderProvider.h"
#include "UI/Widget.h"

bool WidgetOrderProvider::Less(const SpatialNode* a, const SpatialNode* b) const
{
    const Widget* wa = static_cast<const Widget*>(a->GetOwner());
    const Widget* wb = static_cast<const Widget*>(b->GetOwner());

    if (wa->GetZOrder() != wb->GetZOrder())
    {
        return wa->GetZOrder() < wb->GetZOrder();
    }
    return wa->GetInsertionOrder() < wb->GetInsertionOrder();
}