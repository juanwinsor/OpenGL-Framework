#include "common.h"
#include "Renderer.h"
#include "GameMain.h"
#include "InputManager.h"
#include "Renderer2D.h"
#include "UIManager.h"

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	int running = GL_TRUE;

	//initialize renderer
	Renderer::getInstance()->initialize();

	GameMain* gameMain = new GameMain();
	gameMain->initialize();

	//start game loop
	double lastTime = glfwGetTime();
	GameTime gameTime;

	while(running)
	{
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		gameTime.ElapsedTime = deltaTime;
		gameTime.TotalTime = currentTime;

		glfwPollEvents();

		if(glfwGetWindowParam(GLFW_OPENED))
		{
			InputManager::getInstance()->update();
			gameMain->update(gameTime);
			gameMain->draw(gameTime);
		}

		running = glfwGetWindowParam( GLFW_OPENED );
	}
	
	//clean up glfw
	glfwTerminate();
	//clean up game	
	delete gameMain;
	//clean up renderer
	Renderer::unloadInstance();
	//clean up input singleton
	InputManager::unloadInstance();
	//clean up uimananger
	UIManager::unloadInstance();
	//clean up renderer2D
	Renderer2D::unloadInstance();

	//exit OK
	return 0;
}