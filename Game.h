#pragma once
#include "YXA.h"

#include <stdio.h>
#include <cstdio>
#include <ctime>

using namespace std;

class Game
{
private:
	YXA* yxa;
protected:

public:
	Game();
	~Game();
};

Game::Game()
{
	float updateRate = 1.f / 60.f;
	XMINT2 resolution = XMINT2(1280, 960);
	yxa = new YXA(resolution);
	Scene* scene = yxa->CreateScene();
	Image* image = yxa->CreateImage(resolution);
	Image* image2 = yxa->CreateImage(resolution);
	Model* batModel = yxa->CreateModel("sphere3Maya.obj", "Old_Stone_Road_COLOR.dds"); //Old_Stone_Road_COLOR
	Model* bowlingPlaneModel = yxa->CreateModel("BowlingPlaneMaya.obj", "BowlingPlane.dds");

	Camera* batcam = scene->CreateCamera(resolution);
	batcam->SetWorldPos(XMFLOAT3(0.f, 0.f, -1.5f));

	Object* bowlingPlane = scene->CreateObject(bowlingPlaneModel);
	bowlingPlane->SetWorldPos(XMFLOAT3(0.f, -0.5f, 0.f));
	bowlingPlane->SetScale(XMFLOAT3(0.2f, 0.2f, 0.2f));
	
	const int nrX = 15;
	const int nrY = 15;
	const int nrZ = 15;
	Object* objList[nrX][nrY][nrZ];
	float space = 2.0f;
	for (int x = 0; x < nrX; x++)
	{
		for (int y = 0; y < nrY; y++)
		{
			for (int z = 0; z < nrZ; z++)
			{
				objList[x][y][z] = scene->CreateObject(batModel);
				objList[x][y][z]->SetWorldPos(XMFLOAT3((x - nrX/2) * space, (y - nrY/ 2) * space, (z - nrZ / 2) * space));
			}
		}
	}
	
	while (yxa->Running())
	{
		clock_t start = std::clock();
		//UPDATE
		if (GetAsyncKeyState(_In_ 'W'))
		{
			batcam->MoveFront(1.f * updateRate);
		}
		if (GetAsyncKeyState(_In_ 'S'))
		{
			batcam->MoveFront(-1.f * updateRate);
		}
		if (GetAsyncKeyState(_In_ 'A'))
		{
			batcam->MoveRight(-1.f * updateRate);
		}
		if (GetAsyncKeyState(_In_ 'D'))
		{
			batcam->MoveRight(1.f * updateRate);
		}
		if (GetAsyncKeyState(_In_ 'Q'))
		{
			batcam->MoveUp(1.f * updateRate);
		}
		if (GetAsyncKeyState(_In_ 'E'))
		{
			batcam->MoveUp(-1.f * updateRate);
		}
		if (GetAsyncKeyState(VK_NUMPAD4))
		{
			batcam->Pitch(-1.f / 4.f * (2.f * pi) * (updateRate));
		}
		if (GetAsyncKeyState(VK_NUMPAD6))
		{
			batcam->Pitch(1.f / 4.f * (2.f * pi) * (updateRate));
		}

		if (GetAsyncKeyState(VK_NUMPAD2))
		{
			batcam->Yaw(-1.f / 4.f * (2.f * pi) * (updateRate));
		}
		if (GetAsyncKeyState(VK_NUMPAD8))
		{
			batcam->Yaw(1.f / 4.f * (2.f * pi) * (updateRate));
		}

		//UPDATE ROTATION
		for (int x = 0; x < nrX; x++)
		{
			for (int y = 0; y < nrY; y++)
			{
				for (int z = 0; z < nrZ; z++)
				{
					objList[x][y][z]->Roll(1.f / 4.f * (2.f * pi) * (updateRate));
					objList[x][y][z]->Yaw(1.f / 4.f * (2.f * pi) * (updateRate));
					objList[x][y][z]->SetScale(XMFLOAT3(0.5f, 0.5f, 0.5f));
				}
			}
		}

		//UPDATE PHYSICS
		scene->UpdatePhysics(updateRate);

		//RENDER
		scene->RenderImage(batcam, image);
		//image->GaussianBlurTo(image2);

		//WAIT
		while((std::clock() - start) / (double)CLOCKS_PER_SEC < updateRate)
		{

		}

		//PRESENT
		yxa->Present(image);
	}
}

Game::~Game()
{
	delete yxa;
}