#ifndef __CAMERA_COMPONENT_H_INCLUDED__
#define __CAMERA_COMPONENT_H_INCLUDED__

#include "Components/Component.h"

#include <glm/vec2.hpp>

class CameraComponent : public Component
{
public:
	glm::vec2 GetPosition() const { return position; }
	float GetRotate() const { return rotate; }
	float GetZoom() const { return zoom; }

	void SetPosition(glm::vec2 _position) { position = _position; }
	void SetRotate(float _rotate) { rotate = _rotate; }
	void SetZoom(float _zoom) { zoom = _zoom; }

private:
	glm::vec2 position = glm::vec2(0, 0);
	float rotate = 0;
	float zoom = 1;
};

#endif // __CAMERA_COMPONENT_H_INCLUDED__