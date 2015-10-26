#include "Game.h"
#include <crtdbg.h>


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Game game;

	//TODO Entity: LookAt, LookTo, Roll, Yaw

	//TODO FIX Objloader to load both quads and triangles 

	//TODO STRUCT BUFFER eller CONST BUFFER, Filtret är fel, blir mörka färger

	//CHANGED:
	//HWND ligger nu lagrad i YXA, windowHandler har pekare till HWND istället
	//WindowHandler har också pekare till ImageShaders för att komma åt copy(),
	//om vi har image->Copy(trg UAV) (används i Present()) har användearen tillgång till den. 

	return 0;
}