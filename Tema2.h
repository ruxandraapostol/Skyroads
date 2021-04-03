#pragma once
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <TextRenderer/TextRenderer.h>
#include <Core/GPU/Mesh.h>
#include "LabCamera.h"
#include "Objects2.h"
#include "Transform3D.h"


class Tema2 : public SimpleScene
{
public:
	Tema2();
	~Tema2();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void RenderSimpleMesh(Mesh* mesh, Shader* shader,
		const glm::mat4& modelMatrix, const glm::vec3& color, const Texture2D *texture);

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;
	void CreateMap();
	void CheckPowerUp(int i, int j);
	void DrawComets(int i, float distance, int sens, float deltaTimeSeconds);

protected:

	// texturi
	std::unordered_map<std::string, Texture2D*> mapTextures;

	// camera
	CameraTema2::Camera* camera;
	glm::mat4 projectionMatrix;
	bool firstPerson;
	bool renderCameraTarget;


	// shadere
	float lightPosition[200];
	float lightDirection[200];
	float lightPositionAllien[200];
	float lightDirectionAllien[200];
	unsigned int materialShininess;
	float materialKd;
	float materialKs;

	// variabile harta
	int mapMatrix[21][3];
	float speed, distance;
	bool prevLine;

	// variabile sarituri
	bool jumpUp, jumpLeft, jumpRight, fall;
	float jumpUpAngle, jumpLeftAngle, jumpRightAngle;

	// variabile sfera
	glm::vec2 sphereCoordonate;
	float rotateAngleSphere;
	float scaleFactor;
	float power;
	int position;
	int stopTime;
	float noiseTime;

	TextRenderer* Text;
	int level;
	int count;

	// comets 
	float planet1Angular;
	float planet2Angular;
	float planetAngular;
	glm::vec3 planets[21];
	bool alien;
	float planetDistance[21];
	int diamondMatrix[21][3];
	int score;
};
