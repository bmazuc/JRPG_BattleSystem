#ifndef __AUTO_DESTROY_IMAGE_H_INCLUDED__
#define __AUTO_DESTROY_IMAGE_H_INCLUDED__

#include "UI/Image.h"

class AutoDestroyImage : public Image
{
public:
	void Update(float deltaTime) override;

private:
	float timer = 0.0f;
};

#endif // __AUTO_DESTROY_IMAGE_H_INCLUDED__