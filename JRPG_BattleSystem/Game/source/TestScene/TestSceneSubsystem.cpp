#include "TestScene/TestSceneSubsystem.h"
#include <iostream>

void TestSceneSubsystem::Initialize()
{
	std::cout << "TestSceneSubsystem::Initialize " + name << std::endl;
}

void TestSceneSubsystem::Deinitialize()
{
	std::cout << "TestSceneSubsystem::Deinitialize " + name << std::endl;
}