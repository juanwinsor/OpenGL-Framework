#include "common.h"
#include "InputManager.h"


InputManager* InputManager::m_Instance = NULL;

InputManager::InputManager()
{
}

InputManager::~InputManager()
{

}

InputManager* InputManager::getInstance()
{
	if(m_Instance == NULL)
	{
		m_Instance = new InputManager();
	}
	return m_Instance;
}

void InputManager::unloadInstance()
{
	if(m_Instance != NULL)
	{
		delete m_Instance;
		m_Instance = NULL;
	}
}

void InputManager::update()
{

}


Vector2 InputManager::mousePosition()
{
	int x = 0;
	int y = 0;
	glfwGetMousePos(&x, &y);
	m_MousePosition.x = x;
	m_MousePosition.y = y;

	return m_MousePosition;
}

int InputManager::mouseButton(int button)
{
	return glfwGetMouseButton(button);
}