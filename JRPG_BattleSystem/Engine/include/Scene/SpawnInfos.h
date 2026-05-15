#ifndef __SPAWN_INFO_H_INCLUDED__
#define __SPAWN_INFO_H_INCLUDED__

#include "Core/Math/Transform2D.h"

class Actor;
class Widget;
class SceneComponent;

/**
 * Base data used to describe how an object should be spawned in a scene.
 * Contains transform information and defines whether it is applied in world space or local space.
 */
struct SpawnInfo
{
public:
	SpawnInfo(TransformSpace _transformSpace, glm::vec2 _location, float _rotate, glm::vec2 _scale)
		: transformSpace(_transformSpace), location(_location), rotate(_rotate), scale(_scale) {
	}

	virtual ~SpawnInfo() = 0;

	glm::vec2 location = glm::vec2(0.0f, 0.0f);
	float rotate = 0.0f;
	glm::vec2 scale = glm::vec2(1.0f, 1.0f);

	// Defines whether transform is applied in world or local space
	TransformSpace transformSpace = TransformSpace::World;
};

/**
 * Spawn information specific to Actor objects.
 * Adds parent relationship support to define hierarchy at spawn time.
 */
struct ActorSpawnInfo : SpawnInfo
{
public:
	ActorSpawnInfo(Actor* _parent = nullptr, TransformSpace _transformSpace = TransformSpace::World, glm::vec2 _location = glm::vec2(0.0f, 0.0f), float _rotate = 0.0f, glm::vec2 _scale = glm::vec2(1.0f, 1.0f))
		: parent(_parent), SpawnInfo(_transformSpace, _location, _rotate, _scale) {
	}

	~ActorSpawnInfo() = default;

	// Optional parent actor for hierarchy attachment
	Actor* parent = nullptr;
};

/**
 * Spawn information specific to SceneComponent objects.
 * Adds parent relationship support to define hierarchy at spawn time.
 */
struct SceneComponentSpawnInfo : SpawnInfo
{
public:
	SceneComponentSpawnInfo(SceneComponent* _parent = nullptr, TransformSpace _transformSpace = TransformSpace::Local, glm::vec2 _location = glm::vec2(0.0f, 0.0f), float _rotate = 0.0f, glm::vec2 _scale = glm::vec2(1.0f, 1.0f))
		: parent(_parent), SpawnInfo(_transformSpace, _location, _rotate, _scale) {
	}

	~SceneComponentSpawnInfo() = default;

	// Optional parent SceneComponent for UI hierarchy
	SceneComponent* parent = nullptr;
};

/**
 * Spawn information specific to widgets.
 * Allows UI hierarchy definition at creation time.
 */
struct UISpawnInfo : SpawnInfo
{
public:
	UISpawnInfo(Widget* _parent = nullptr, TransformSpace _transformSpace = TransformSpace::World, glm::vec2 _location = glm::vec2(0.0f, 0.0f), float _rotate = 0.0f, glm::vec2 _scale = glm::vec2(1.0f, 1.0f))
		: parent(_parent), SpawnInfo(_transformSpace, _location, _rotate, _scale) {
	}

	~UISpawnInfo() = default;

	// Optional parent widget for UI hierarchy
	Widget* parent = nullptr;
};

#endif // __SPAWN_INFO_H_INCLUDED__