
#include "Objects2.h"

#include <Core/Engine.h>


Mesh* Objects2::CreatePowerBar()
{
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, 0, 0)),
		VertexFormat(glm::vec3(0, LENGTH / 2, 0)),
		VertexFormat(glm::vec3(LENGTH, 0, 0)),
		VertexFormat(glm::vec3(LENGTH, LENGTH / 2, 0))
	};

	std::vector<unsigned short> indices = { 0, 1, 2, 1, 2, 3 };
	std::string name;

	Mesh* bar = new Mesh("powerBar");
	bar->InitFromData(vertices, indices);
	return bar;
}

Mesh* Objects2::CreateBarBox()
{
	std::vector<VertexFormat> vertices;

	std::vector<unsigned short> indices;

	for(int i = 0; i < 5; i++) {
		vertices.emplace_back(glm::vec3((i + 1) * LENGTH / 5, 0, 0));
		vertices.emplace_back(glm::vec3(i * LENGTH / 5, LENGTH / 2, 0));
		indices.push_back(2 * i);
		indices.push_back(2 * i + 1);
	};

	vertices.emplace_back(glm::vec3(LENGTH, LENGTH / 2, 0));
	vertices.emplace_back(glm::vec3(0, 0, 0));

	// dreptunghi incadrator
	{
		indices.push_back(1);
		indices.push_back(10);

		indices.push_back(1);
		indices.push_back(11);

		indices.push_back(8);
		indices.push_back(10);

		indices.push_back(8);
		indices.push_back(11);
	}

	Mesh* bar = new Mesh("barBox");
	bar->InitFromData(vertices, indices);
	bar->SetDrawMode(GL_LINES);
	return bar;
}

Mesh* Objects2::CreateSphere() {
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;

	float x, y, z, xy;                          // vertex position
	float nx, ny, nz, lengthInv = 0.5f;			// vertex normal
	float s, t;                                 // vertex texCoord
	float sectorCount = 72;
	float stackCount = 24;

	float sectorStep = 2 * 3.14f / sectorCount;
	float stackStep = 3.14f / stackCount;
	float sectorAngle, stackAngle;

	for (int i = 0; i <= stackCount; ++i)
	{
		stackAngle = 3.14f / 2 - i * stackStep;			// starting from pi/2 to -pi/2
		xy = 0.5f * cosf(stackAngle);					// r * cos(u)
		z = 0.5f * sinf(stackAngle);					// r * sin(u)

		// add (sectorCount+1) vertices per stack
		// the first and last vertices have same position and normal, but different tex coords
		for (int j = 0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorStep;           // starting from 0 to 2pi

			// vertex position (x, y, z)
			x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
			y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
			vertices.push_back(glm::vec3(x, y, z));

			// normalized vertex normal (nx, ny, nz)
			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;
			normals.push_back(glm::vec3(nx, ny, nz));

			// vertex tex coord (s, t) range between [0, 1]
			s = (float)j / sectorCount;
			t = (float)i / stackCount;
			texCoords.push_back(glm::vec2(s, t));
		}
	}

	std::vector<GLushort> indices;
	std::vector<GLushort> lineIndices;
	GLushort k1, k2;
	for (GLushort i = 0; i < stackCount; ++i)
	{
		k1 = i * (sectorCount + 1);     // beginning of current stack
		k2 = k1 + sectorCount + 1;      // beginning of next stack

		for (GLushort j = 0; j < sectorCount; ++j, ++k1, ++k2)
		{
			// 2 triangles per sector excluding first and last stacks
			// k1 => k2 => k1+1
			if (i != 0)
			{
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}

			// k1+1 => k2 => k2+1
			if (i != (stackCount - 1))
			{
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}

			// store indices for lines
			// vertical lines for all stacks, k1 => k2
			lineIndices.push_back(k1);
			lineIndices.push_back(k2);
			if (i != 0)  // horizontal lines except 1st stack, k1 => k+1
			{
				lineIndices.push_back(k1);
				lineIndices.push_back(k1 + 1);
			}
		}
	}

	Mesh* sphere = new Mesh("planet");
	sphere->InitFromData(vertices, normals, texCoords, indices);
	return sphere;
}

Mesh* Objects2::CreateSimpleQuad() {
	std::vector<glm::vec3> vertices
	{
		glm::vec3(0.5f,   0.5f, 0.0f),	// Top Right
		glm::vec3(0.5f,  -0.5f, 0.0f),	// Bottom Right
		glm::vec3(-0.5f, -0.5f, 0.0f),	// Bottom Left
		glm::vec3(-0.5f,  0.5f, 0.0f),	// Top Left
	};

	std::vector<glm::vec3> normals
	{
		glm::vec3(0, 1, 1),
		glm::vec3(1, 0, 1),
		glm::vec3(1, 0, 0),
		glm::vec3(0, 1, 0)
	};

	// TODO : Complete texture coordinates for the square
	std::vector<glm::vec2> textureCoords
	{
		glm::vec2(0.f, 0.f),
		glm::vec2(0.f, 1.f),
		glm::vec2(1.f, 1.f),
		glm::vec2(1.f, 0.f)
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 3,
		1, 2, 3
	};

	Mesh* mesh = new Mesh("quad");
	mesh->InitFromData(vertices, normals, textureCoords, indices);
	return mesh;
}
