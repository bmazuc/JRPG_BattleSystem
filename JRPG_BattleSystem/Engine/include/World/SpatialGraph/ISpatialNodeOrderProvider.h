#ifndef __SPATIAL_NODE_ORDER_PROVIDER_H_INCLUDED__
#define __SPATIAL_NODE_ORDER_PROVIDER_H_INCLUDED__

class SpatialNode;

/**
 * Defines ordering rules for SpatialNode siblings during traversal.
 */
class ISpatialNodeOrderProvider
{
public:
	virtual ~ISpatialNodeOrderProvider() = default;
	/**
	 * Returns true if 'a' should be ordered before 'b' among sibling SpatialNodes
	 */
	virtual bool Less(const SpatialNode* a, const SpatialNode* b) const = 0;
};

#endif // __SPATIAL_NODE_ORDER_PROVIDER_H_INCLUDED__