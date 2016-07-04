#include <Frame2D.h>
#include "LoginScene.h"

#pragma comment(lib, "Frame2D.lib")

USING_NS_F2D

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	Application::getInstance()->SetWindowStyle(true, "StarShip", 40 * 10, 55 * 10);
	Application::getInstance()->startSystem(hInstance);

	Application::getInstance()->startScene(LoginScene::Create());

	return Application::getInstance()->Run();
}