#include "TestScene/TestActorComponent.h"
#include <iostream>

void TestActorComponent::BeginPlay()
{
	std::cout << "TestActorComponent::BeginPlay " + name << std::endl;
}