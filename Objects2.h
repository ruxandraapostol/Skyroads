
#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

#define LENGTH (0.5f)

namespace Objects2
{
	// Create square with given bottom left corner, length and color
	Mesh* CreatePowerBar();
	Mesh* CreateBarBox();
	Mesh* CreateSphere();
	Mesh* CreateSimpleQuad();
	Mesh* CreateAllien();
}

