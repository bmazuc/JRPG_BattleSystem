#ifndef __COMPONENT_H_INCLUDED__
#define __COMPONENT_H_INCLUDED__

class GameObject;

class Component
{
public:
	virtual ~Component() = default;

	GameObject* GetOwner() const { return owner; }
	void SetOwner(GameObject* _owner) { owner = _owner; }

private:
	GameObject* owner;
};

#endif // __COMPONENT_H_INCLUDED__
