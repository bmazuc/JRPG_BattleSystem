#ifndef __WIDGET_ORDER_PROVIDER_H_INCLUDED__
#define __WIDGET_ORDER_PROVIDER_H_INCLUDED__

#include "World/SpatialGraph/ISpatialNodeOrderProvider.h"

/**
 * Provides ordering rules for UI Widgets.
 * Controls rendering traversal order based on z-order and insertion order.
 */
class WidgetOrderProvider : public ISpatialNodeOrderProvider
{
public:
	bool Less(const SpatialNode* a, const SpatialNode* b) const override;
};

#endif // __WIDGET_ORDER_PROVIDER_H_INCLUDED__