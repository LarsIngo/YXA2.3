#include "Game.h"
#include <crtdbg.h>


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Game game;

	//TODO Entity: LookAt, LookTo, Roll, Yaw

	//TODO FIX Objloader to load both quads and triangles 

	//TODO STRUCT BUFFER eller CONST BUFFER, Filtret �r fel, blir m�rka f�rger

	//CHANGED:
	//HWND ligger nu lagrad i YXA, windowHandler har pekare till HWND ist�llet
	//WindowHandler har ocks� pekare till ImageShaders f�r att komma �t copy(),
	//om vi har image->Copy(trg UAV) (anv�nds i Present()) har anv�ndearen tillg�ng till den. 

	return 0;
}