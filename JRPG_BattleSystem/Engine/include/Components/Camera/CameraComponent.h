#ifndef __CAMERA_COMPONENT_H_INCLUDED__
#define __CAMERA_COMPONENT_H_INCLUDED__

#include "Components/SceneComponent.h"

/**
 *	Represents a camera viewpoint.
 */
class CameraComponent : public SceneComponent
{
public:
	float GetZoom() const { return zoom; }
	void SetZoom(float newZoom) { zoom = newZoom; }

private:
	float zoom = 1;
};

#endif // __CAMERA_COMPONENT_H_INCLUDED__