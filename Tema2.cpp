#include "Tema2.h"

#include <vector>
#include <string>
#include <iostream>
#include <random>

#include <Core/Engine.h>
#include <random>
#include <time.h>

using namespace std;


Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::CreateMap() {

	srand(time(0));

	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 3; j++) {
			mapMatrix[i][j] = 1;
			if (i < 7) {
				diamondMatrix[i][j] = 0;
			}
			else {
				diamondMatrix[i][j] = rand() % 3;
			}
		}
	}

	bool prev = true;
	for (int i = 15; i < 21; i++) {
		int nrOfZeros = 0;

		bool cont = false;
		for (int j = 0; j < 3; j++) {
			int randomNumber = rand() % 1000 + 1;
			diamondMatrix[i][j] = rand() % 3;
			if (randomNumber % 2 == 0 || mapMatrix[i - 1][j] < 0) {
				mapMatrix[i][j] = 1;
				if ((j > 0 && mapMatrix[i - 1][j - 1] != 0) || mapMatrix[i - 1][j] != 0 ||
					(j < 2 && mapMatrix[i - 1][j + 1] != 0) || mapMatrix[i - 2][j] != 0) {
					cont = true;
				}

				if (randomNumber % 3 == 0) {
					mapMatrix[i][j] = 2;
				}
				if (randomNumber % 5 == 0) {
					mapMatrix[i][j] = 3;
				}
				if (randomNumber % 17 == 0) {
					mapMatrix[i][j] = 4;
				}
				if (randomNumber % 37 == 0) {
					mapMatrix[i][j] = 5;
				}

 				if ((randomNumber % 7 == 0) && (mapMatrix[i - 1][j] != 0)
					&& (mapMatrix[i - 1][j] > 0) && (mapMatrix[i - 1][j] != 5)) {
					mapMatrix[i][j] *= -1;
				}
			}
			else {
				nrOfZeros++;
				mapMatrix[i][j] = 0;
			}
		}

		// ma asigur ca nu am 2 randuri consecutive goale
		if (nrOfZeros == 3) {
			if (prev) {
				prev = false;
			}
			else {
				i--;
			}
		}
		else if (!cont) {
			i--;
		}
	}
}

void Tema2::DrawComets(int i, float distance, int sens, float deltaTimeSeconds) {
	{
		planetAngular += 0.12 * deltaTimeSeconds;
		planet1Angular += 0.1 * deltaTimeSeconds;
		planet2Angular += 0.03 * deltaTimeSeconds;

		string name = "planet" + to_string(planets[i].x).substr(0, 1); 
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(sens * 3, 0, -i + 1.5 + distance);
		modelMatrix *= Transform3D::RotateOX(planetAngular);
		modelMatrix *= Transform3D::Scale(0.5f, 0.5f, 0.5f);
		RenderSimpleMesh(meshes["planet"], shaders["MyShader"], modelMatrix, glm::vec3(0, 0, 0), mapTextures[name]);

		name = "planet" + to_string(planets[i].y).substr(0, 1);
		glm:: mat4 earthMatrix = glm::mat4(1);
		earthMatrix *= Transform3D::Translate(sens * 3, 0, -i + 1.5 + distance);
		earthMatrix *= Transform3D::RotateOY(planet1Angular);
		earthMatrix *= Transform3D::Translate(- sens * 0.5, 0, 0);
		earthMatrix *= Transform3D::Scale(0.3f, 0.3f, 0.3f);
		RenderSimpleMesh(meshes["planet"], shaders["MyShader"], earthMatrix, glm::vec3(0, 0, 0), mapTextures[name]);

		name = "planet" + to_string(planets[i].z).substr(0, 1);
		earthMatrix = glm::mat4(1);
		earthMatrix *= Transform3D::Translate(sens * 3, 0, -i + 1.5 + distance);
		earthMatrix *= Transform3D::RotateOZ(planet2Angular);
		earthMatrix *= Transform3D::Translate(-sens * 0.5, 0, 0);
		earthMatrix *= Transform3D::Scale(0.3f, 0.3f, 0.3f);
		RenderSimpleMesh(meshes["planet"], shaders["MyShader"], earthMatrix, glm::vec3(0, 0, 0), mapTextures[name]);
	}

}

void Tema2::Init()
{
	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
	renderCameraTarget = false;
	camera = new CameraTema2::Camera();
	camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

	// create texture
	{
		const string textureLoc = "Source/Laboratoare/Tema2/Texture/";
		{
			Texture2D* texture = new Texture2D();
			texture->Load2D((textureLoc + "cosmos.png").c_str(), GL_REPEAT);
			mapTextures["cosmos"] = texture;
		}

		{
			Texture2D* texture = new Texture2D();
			texture->Load2D((textureLoc + "planet1.png").c_str(), GL_REPEAT);
			mapTextures["planet1"] = texture;
		}


		{
			Texture2D* texture = new Texture2D();
			texture->Load2D((textureLoc + "planet2.png").c_str(), GL_REPEAT);
			mapTextures["planet2"] = texture;
		}


		{
			Texture2D* texture = new Texture2D();
			texture->Load2D((textureLoc + "planet3.png").c_str(), GL_REPEAT);
			mapTextures["planet3"] = texture;
		}

		{
			Texture2D* texture = new Texture2D();
			texture->Load2D((textureLoc + "planet4.png").c_str(), GL_REPEAT);
			mapTextures["planet4"] = texture;
		}

		{
			Texture2D* texture = new Texture2D();
			texture->Load2D((textureLoc + "planet5.png").c_str(), GL_REPEAT);
			mapTextures["planet5"] = texture;
		}

		{
			Texture2D* texture = new Texture2D();
			texture->Load2D((textureLoc + "planet6.png").c_str(), GL_REPEAT);
			mapTextures["planet6"] = texture;
		}

		{
			Texture2D* texture = new Texture2D();
			texture->Load2D((textureLoc + "green.png").c_str(), GL_REPEAT);
			mapTextures["green"] = texture;
		}

		{
			Texture2D* texture = new Texture2D();
			texture->Load2D((textureLoc + "yellow2.jpg").c_str(), GL_REPEAT);
			mapTextures["yellow"] = texture;
		}

		{
			Texture2D* texture = new Texture2D();
			texture->Load2D((textureLoc + "orange.jpg").c_str(), GL_REPEAT);
			mapTextures["orange"] = texture;
		}

		{
			Texture2D* texture = new Texture2D();
			texture->Load2D((textureLoc + "red.jpg").c_str(), GL_REPEAT);
			mapTextures["red"] = texture;
		}

		{
			Texture2D* texture = new Texture2D();
			texture->Load2D((textureLoc + "purple.jpg").c_str(), GL_REPEAT);
			mapTextures["purple"] = texture;
		}

		{
			Texture2D* texture = new Texture2D();
			texture->Load2D((textureLoc + "alien.jpg").c_str(), GL_REPEAT);
			mapTextures["alien"] = texture;
		}

		{
			Texture2D* texture = new Texture2D();
			texture->Load2D((textureLoc + "diamond.jpg").c_str(), GL_REPEAT);
			mapTextures["diamond"] = texture;
		}
	}


	// create text
	{
		Text = new TextRenderer(window->GetResolution().x, window->GetResolution().y);
		Text->Load("Source/TextRenderer/Fonts/Arial.ttf", 25);
	}

	// create objects

	{
		{
			Mesh* mesh = Objects2::CreateSphere();
			AddMeshToList(mesh);
		}

		{
			Mesh* mesh = new Mesh("sphere");
			mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
			meshes[mesh->GetMeshID()] = mesh;
		}

		{
			Mesh* mesh = new Mesh("box");
			mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
			meshes[mesh->GetMeshID()] = mesh;
		}

		{
			Mesh* powerBar = Objects2::CreatePowerBar();
			AddMeshToList(powerBar);

			Mesh* boxBar = Objects2::CreateBarBox();
			AddMeshToList(boxBar);
		}

		{
			Mesh* quad = Objects2::CreateSimpleQuad();
			AddMeshToList(quad);
		}
	}


	// create shades
	{
		Shader* shader = new Shader("MyShader");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;

		Shader* shader2 = new Shader("SphereShader");
		shader2->AddShader("Source/Laboratoare/Tema2/ShaderSphere/VertexShader.glsl", GL_VERTEX_SHADER);
		shader2->AddShader("Source/Laboratoare/Tema2/ShaderSphere/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader2->CreateAndLink();
		shaders[shader2->GetName()] = shader2;
	}


	//Light & material properties
	{
		materialShininess = 300;
		materialKd = 0.1;
		materialKs = 0.1;
	}


	// variabile joc
	{
		firstPerson = false;
		speed = 2;
		distance = 0;

		jumpUp = false;
		jumpRight = false;
		jumpLeft = false;
		fall = false;

		jumpUpAngle = 0;
		jumpLeftAngle = 0;
		jumpRightAngle = 0;

		scaleFactor = 0.5f;
		sphereCoordonate.y = 0;
		sphereCoordonate.x = 0;
		rotateAngleSphere = 0;
		position = 1;
		power = 100;
		stopTime = 0;
		noiseTime = 0;
		level = 1;
		count = 0;

		planetAngular = 0;
		planet1Angular = 0;
		planet2Angular = 0;
		for (int i = 0; i < 21; i ++) {
			planets[i] = glm::vec3(rand() % 5 + 1, rand() % 5 + 1, rand() % 5 + 1);
			planetDistance[i] = 0;
		}
		alien = false;
		score = 0;
	}

	CreateMap();
}

void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::CheckPowerUp(int i, int j) {
		if (mapMatrix[i][j] == 2) {
			power = min(power + 10 - 0.2f * level, 100.f);
			noiseTime += 1;
		}
		else if (mapMatrix[i][j] == 3) {
			power = max(power - 5 - 0.5f * level , 0.f);
			noiseTime += 1;
		}
		else if (mapMatrix[i][j] == 5) {
			power = 0.f;
			noiseTime += 1;
		}
		else if (mapMatrix[i][j] == 4) {
			stopTime = 5;
			noiseTime += 5;
		}
}


void Tema2::Update(float deltaTimeSeconds)
{ 

	// fundal
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(-1, -2, -20);
		modelMatrix *= Transform3D::Scale(70, 50, 10);
		RenderSimpleMesh(meshes["quad"], shaders["MyShader"], modelMatrix, glm::vec3(0, 0, 1), mapTextures["cosmos"]);

	}

	// nivel  
	{
		string payload = "NIVELUL " + to_string(level);
		Text->RenderText(payload, 0, 15, 1, glm::vec3(1, 1, 1));

		payload = "SCOR: " + to_string(score).substr(0, size(to_string(score)) - 4);
		Text->RenderText(payload, (camera->position.x + 1150 - 10 * payload.size()), 15, 1.0f, glm::vec3(1.0, 1.0, 1.0));
	}

	// powerBar
	{
		if (power == 0) {
			exit(1);
		}

		float powerRaport = power / 100;
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = Transform3D::Translate(camera->position.x + 4, camera->position.y + 1.045, camera->position.z - 5);
		modelMatrix *= Transform3D::Scale(1, 0.5, 1);
		RenderSimpleMesh(meshes["barBox"], shaders["MyShader"], modelMatrix, glm::vec3(0.8, 0.9, 0.9), NULL);

		modelMatrix = Transform3D::Translate(camera->position.x + 4, camera->position.y + 1.045, camera->position.z - 5);
		modelMatrix *= Transform3D::Scale(powerRaport, 0.5, 1);
		RenderSimpleMesh(meshes["powerBar"], shaders["MyShader"], modelMatrix, glm::vec3(0.1, 1, 0.2), NULL);


		modelMatrix = Transform3D::Translate(camera->position.x + 4, camera->position.y + 1.045, camera->position.z - 5);
		modelMatrix *= Transform3D::Scale(1 - powerRaport, 0.5, 1);
		RenderSimpleMesh(meshes["powerBar"], shaders["MyShader"], modelMatrix, glm::vec3(0.8, 0.7, 0.7), NULL);
	}

	//  harta
	{
		// daca am cazut piesele nu se mai misca
		if (!fall && !alien) {
			distance += (speed + level * 0.2 - 0.2) *  deltaTimeSeconds;
		}

		for (int i = 0; i < 21; i += 2) {
			planetDistance[i] += (speed + level * 0.2 - 0.2) * deltaTimeSeconds;
			if (-i + planetDistance[i] > 1) {
				planetDistance[i] = -20 + i;
			}
			DrawComets(i, planetDistance[i], 1, deltaTimeSeconds);
			DrawComets(i, planetDistance[i], -1, deltaTimeSeconds);
		}

		// creare lumina banuti
		{
			for (int i = 0; i < 21; i++) {
				for (int j = 0; j < 3; j++) {
					if (mapMatrix[i][j] < 0) {
						lightPositionAllien[i * 9 + j * 3] = j - 1;
						lightPositionAllien[i * 9 + j * 3 + 1] = 0.4;
						lightPositionAllien[i * 9 + j * 3 + 2] = -i + 1 + distance;


						lightDirectionAllien[i * 9 + j * 3] = 0;
						lightDirectionAllien[i * 9 + j * 3 + 1] = -1;
						lightDirectionAllien[i * 9 + j * 3 + 2] = 0.6;
					}
					else {
						lightPositionAllien[i * 9 + j * 3] = -99999;
						lightPositionAllien[i * 9 + j * 3 + 1] = -99999;
						lightPositionAllien[i * 9 + j * 3 + 2] = 99999;


						lightDirectionAllien[i * 9 + j * 3] = 0;
						lightDirectionAllien[i * 9 + j * 3 + 1] = 0;
						lightDirectionAllien[i * 9 + j * 3 + 2] = 0;
					}

					if (mapMatrix[i][j] != 0 && diamondMatrix[i][j] != 0) {
						lightPosition[i * 9 + j * 3] = j - 1;
						lightPosition[i * 9 + j * 3 + 1] = diamondMatrix[i][j] - 0.8;
						lightPosition[i * 9 + j * 3 + 2] = -i + 1 + distance;


						lightDirection[i * 9 + j * 3] = 0;
						lightDirection[i * 9 + j * 3 + 1] = -1;
						lightDirection[i * 9 + j * 3 + 2] = 0;
					}
					else {
						lightPosition[i * 9 + j * 3] = -99999;
						lightPosition[i * 9 + j * 3 + 1] = -99999;
						lightPosition[i * 9 + j * 3 + 2] = 99999;


						lightDirection[i * 9 + j * 3] = 0;
						lightDirection[i * 9 + j * 3 + 1] = 0;
						lightDirection[i * 9 + j * 3 + 2] = 0;
					}
				}
			}
		}

		// miscarea placilor
		for (int i = 0; i < 21; i++) {
			for (int j = 0; j < 3; j++) {
				if (mapMatrix[i][j] != 0) {
					if (diamondMatrix[i][j] != 0) {
						glm::mat4 dMatrix = glm::mat4(1);
						dMatrix *= Transform3D::Translate(j - 1, diamondMatrix[i][j] - 0.8, -i + 1 + distance);
						dMatrix *= Transform3D::RotateOY(planet1Angular);
						dMatrix *= Transform3D::Scale(0.2, 0.2, 0.1);
						RenderSimpleMesh(meshes["sphere"], shaders["MyShader"], dMatrix, glm::vec3(0.5, 0.9, 0.5), mapTextures["diamond"]);
					}

					glm::mat4 modelMatrix = glm::mat4(1);
					modelMatrix *= Transform3D::Translate(j - 1, 0, -i + 1 + distance);
					modelMatrix *= Transform3D::Scale(1, 0.1, 1);

					if (abs(mapMatrix[i][j]) == 1) {
						RenderSimpleMesh(meshes["box"], shaders["MyShader"], modelMatrix, glm::vec3(0.5, 0.9, 0.9), NULL);
					}
					else if (abs(mapMatrix[i][j]) == 2) {
						RenderSimpleMesh(meshes["box"], shaders["MyShader"], modelMatrix, glm::vec3(0.5, 0.9, 0.5), mapTextures["green"]);
					}
					else if (abs(mapMatrix[i][j]) == 3) {
						RenderSimpleMesh(meshes["box"], shaders["MyShader"], modelMatrix, glm::vec3(1, 0.9, 0.4), mapTextures["yellow"]);
					}
					else if (abs(mapMatrix[i][j]) == 4) {
						RenderSimpleMesh(meshes["box"], shaders["MyShader"], modelMatrix, glm::vec3(0.9, 0.4, 0.1), mapTextures["orange"]);
					}
					else if (abs(mapMatrix[i][j]) == 5) {
						RenderSimpleMesh(meshes["box"], shaders["MyShader"], modelMatrix, glm::vec3(0.9, 0, 0.2), mapTextures["red"]);
					}
					else if (abs(mapMatrix[i][j]) == 10) {
						RenderSimpleMesh(meshes["box"], shaders["MyShader"], modelMatrix, glm::vec3(0.5, 0.3, 0.6), mapTextures["purple"]);
					}

					if (mapMatrix[i][j] < 0) {
						glm::mat4 alienMatrix = glm::mat4(1);
						alienMatrix *= Transform3D::Translate(j - 1, 0.4, -i + 1 + distance);
						alienMatrix *= Transform3D::Scale(0.7, 0.7, 0.7);
						RenderSimpleMesh(meshes["quad"], shaders["MyShader"], alienMatrix, glm::vec3(0, 0, 1), mapTextures["alien"]);
					}
				}
			}
		}

		// disparitia din scena
		if (distance > 1) {
			distance = 0;
			power -= level;
			count++;

			if (count == level * (level + 2) * 10) {
				level++;
			}

			if (stopTime != 0) {
				stopTime--;
			}

			// mut piesele existente in matrice
			for (int i = 0; i < 20; i++) {
				for (int j = 0; j < 3; j++) {
					diamondMatrix[i][j] = diamondMatrix[i + 1][j];
					mapMatrix[i][j] = mapMatrix[i + 1][j];
				}
			}

			// adaug ultima linie
			bool check = true;
			while (check) {
				int nrOfZeros = 0;
				for (int j = 0; j < 3; j++) {
					diamondMatrix[20][j] = rand() % 3;
					int randomNumber = rand() % 1000 + 1;
					if (randomNumber % 2 == 0 || mapMatrix[19][j] < 0) {
						mapMatrix[20][j] = 1;
						if ((j > 0 && mapMatrix[19][j - 1] != 0) || mapMatrix[19][j] != 0 ||
							(j < 2 && mapMatrix[19][j + 1] != 0) || mapMatrix[18][j] != 0) {
							check = false;
						}
						if (randomNumber % 3 == 0) {
							mapMatrix[20][j] = 2;
						}
						if (randomNumber % 5 == 0) {
							mapMatrix[20][j] = 3;
						}
						if (randomNumber % 17 == 0) {
							mapMatrix[20][j] = 4;
						}
						if (randomNumber % 37 == 0) {
							mapMatrix[20][j] = 5;
						}
						if ((randomNumber % 7 == 0) && (mapMatrix[19][j] != 0)
							&& (mapMatrix[19][j] > 0) && (mapMatrix[19][j] != 5)) {
							mapMatrix[20][j] *= -1;
						}
					}
					else {
						nrOfZeros++;
						mapMatrix[20][j] = 0;
					}
				}

				if (nrOfZeros == 3) {
					for (int j = 0; j < 3; j++) {
						if (mapMatrix[20][j] != 0) {
							check = false;
						}
					}
				}
			}
		}
	}


	// sfera
	{
		// daca am cazut nu mai pot sari si pun animatia
		if (!fall && !alien) {
			// sar in sus
			if (jumpUp) {
				jumpUpAngle += 3 * deltaTimeSeconds;
				sphereCoordonate.y = sin(jumpUpAngle);

				if (jumpUpAngle >= 3.14) {
					jumpUp = false;
					jumpUpAngle = 0;
				}
			}

			// sar la stanga
			if (jumpLeft) {
				jumpLeftAngle += 5 * deltaTimeSeconds;
				sphereCoordonate.y = sin(jumpLeftAngle);
				sphereCoordonate.x = -0.5 + 0.5 * cos(jumpLeftAngle);

				if (position == 1) {
					sphereCoordonate.x += 1;
				}

				if (jumpLeftAngle >= 3.14) {
					jumpLeft = false;
					jumpLeftAngle = 0;
				}
			}

			// sar la dreapta
			if (jumpRight) {
				jumpRightAngle += 5 * deltaTimeSeconds;
				sphereCoordonate.y = sin(jumpRightAngle);
				sphereCoordonate.x = 0.5 - 0.5 * cos(jumpRightAngle);

				if (position == 1) {
					sphereCoordonate.x -= 1;
				}

				if (jumpRightAngle >= 3.14) {
					jumpRight = false;
					jumpRightAngle = 0;
				}
			}
		}
		else {
			if (!alien) {
				sphereCoordonate.y += -2 * deltaTimeSeconds;
			}
			scaleFactor -= 0.02f;
		}

		if (scaleFactor > 0) {
			rotateAngleSphere += 2 * deltaTimeSeconds;
			glm::mat4 modelMatrix = glm::mat4(1);

			if (firstPerson) {
				camera->Set(glm::vec3(sphereCoordonate.x, sphereCoordonate.y + 0.8, 0),
					glm::vec3(sphereCoordonate.x, sphereCoordonate.y, -3), glm::vec3(0, 1, 0));
			}

			// afisare sfera
			{
				modelMatrix *= Transform3D::Translate(sphereCoordonate.x, 0.3 + sphereCoordonate.y, 0);
				modelMatrix *= Transform3D::RotateOX(-rotateAngleSphere);
				modelMatrix *= Transform3D::Scale(scaleFactor, scaleFactor, scaleFactor);

				if (noiseTime > 0) {
					noiseTime -= 1.5 * deltaTimeSeconds;
					RenderSimpleMesh(meshes["sphere"], shaders["SphereShader"], modelMatrix, glm::vec3(1, 0, 1), NULL);
				}
				else {
					RenderSimpleMesh(meshes["sphere"], shaders["MyShader"], modelMatrix, glm::vec3(1, 0, 1), NULL);
				}
			}

			// verificare casuta
			if (!fall && !jumpUp && !jumpRight && !jumpLeft) {
				if (mapMatrix[1][position] == 0 && distance < 0.5) {
					fall = true;
				}
				else if (mapMatrix[2][position] == 0 && distance > 0.5) {
					fall = true;
				} 
				else if (mapMatrix[1][position] > 0 && distance < 0.5) {
					CheckPowerUp(1, position);
					mapMatrix[1][position] = 10;
				}
				else if (mapMatrix[2][position] > 0 && distance > 0.5) {
					CheckPowerUp(2, position);
					mapMatrix[2][position] = 10;
				}
				else if (mapMatrix[1][position] < 0 && distance < 0.5) {
					alien = true;
				}
				else if (mapMatrix[2][position] < 0 && distance > 0.5) {
					alien = true;
				}
			}

			// verificare banuti
			{
				if (!jumpUp && !jumpRight && !jumpLeft) {
					if (diamondMatrix[1][position] == 1 && distance < 0.5) {
						diamondMatrix[1][position] = 0;
						score += 10;
					}
					else if (diamondMatrix[2][position] == 1 && distance > 0.5) {
						diamondMatrix[2][position] = 0;
						score += 10;
					}
				}
				else if (jumpUp) {
					if (diamondMatrix[1][position] == 2 && sphereCoordonate.y > 0.5) {
						diamondMatrix[1][position] = 0;
						score += 10;
					}
				}
			}
		}
		else {
			exit(1);
		}
	}
}

void Tema2::FrameEnd()
{
	// DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, const Texture2D* texture)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Set shader uniforms for light & material properties
	// TODO: Set light position uniform

	GLint angle = glGetUniformLocation(shader->program, "angle");
	glUniform1f(angle, 30);

	int shaderId = shader->GetProgramID();
	int locationLight = glGetUniformLocation(shaderId, "light_position");
	glUniform1fv(locationLight, 200, lightPosition);

	int light_direction = glGetUniformLocation(shader->program, "light_direction");
	glUniform1fv(light_direction, 200, lightDirection);

	locationLight = glGetUniformLocation(shaderId, "light_position_allien");
	glUniform1fv(locationLight, 200, lightPositionAllien);

	light_direction = glGetUniformLocation(shader->program, "light_direction_allien");
	glUniform1fv(light_direction, 200, lightDirectionAllien);

	// TODO: Set eye position (camera position) uniform
	glm::vec3 eyePosition = GetSceneCamera()->transform->GetWorldPosition();
	int locationEye = glGetUniformLocation(shaderId, "eye_position");
	glUniform3fv(locationEye, 1, glm::value_ptr(eyePosition));

	// TODO: Set material property uniforms (shininess, kd, ks, object color) 
	GLint locationShininess = glGetUniformLocation(shader->program, "material_shininess");
	glUniform1i(locationShininess, materialShininess);

	GLint locationKd = glGetUniformLocation(shader->program, "material_kd");
	glUniform1f(locationKd, materialKd);

	GLint locationKs = glGetUniformLocation(shader->program, "material_ks");
	glUniform1f(locationKs, materialKs);

	GLint locationColor = glGetUniformLocation(shader->program, "object_color");
	glUniform3fv(locationColor, 1, glm::value_ptr(color));

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	int contor = 0;
	if (texture != NULL) {
		//TODO : activate texture location 0
		glActiveTexture(GL_TEXTURE0);

		//TODO : Bind the texture1 ID
		glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());

		//TODO : Send texture uniform value
		glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);

		contor = 1;
	}

	int loc_contor = glGetUniformLocation(shader->program, "contor");
	glUniform1f(loc_contor, contor);

	int locationTime = glGetUniformLocation(shaderId, "Time");
	glUniform1f(locationTime, (GLfloat)Engine::GetElapsedTime());

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}


// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	float cameraSpeed = 2.0f;
	float cameraDistance = deltaTime * cameraSpeed;


	if (window->KeyHold(GLFW_KEY_SPACE) && !jumpUp && !jumpRight && !jumpLeft) {
		jumpUp = true;
	}

	if (window->KeyHold(GLFW_KEY_D) && !jumpUp && !jumpRight && !jumpLeft && position != 2) {
		jumpRight = true;
		position++;
	}

	if (window->KeyHold(GLFW_KEY_A) && !jumpUp && !jumpRight && !jumpLeft && position != 0) {
		jumpLeft = true;
		position--;
	}

	if (stopTime == 0) {
		if (window->KeyHold(GLFW_KEY_W) && speed < 3.5) {
			speed += 0.01f;
		}


		if (window->KeyHold(GLFW_KEY_S) && speed > 0.5) {
			speed -= 0.01f;
		}
	}

	if (window->KeyHold(GLFW_KEY_C)) {
		if (!firstPerson) {
			firstPerson = true;
		}
		else {
			firstPerson = false;
			camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

		}
	}
}


void Tema2::OnKeyPress(int key, int mods)
{
}

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}
