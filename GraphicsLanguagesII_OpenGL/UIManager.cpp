#include "common.h"
#include "UIManager.h"
#include "UI_Component_Button.h"
#include "UI_Component_Image.h"
#include "UI_Component_Transform.h"

//singleton
UIManager* UIManager::m_Instance = NULL;

UIManager* UIManager::getInstance()
{
	if(m_Instance == NULL)
	{
		m_Instance = new UIManager();
	}
	return m_Instance;
}


void UIManager::unloadInstance()
{
	if(m_Instance != NULL)
	{
		delete m_Instance;
		m_Instance = NULL;
	}
}

UIManager::UIManager()
{
	m_EntityManager = new EntityManager();
}

UIManager::~UIManager()
{
	if(m_EntityManager != NULL)
	{
		delete m_EntityManager;
		m_EntityManager = NULL;
	}
}

Entity* UIManager::createWindow(std::string name)
{
	//create a new element
	Entity* entity = m_EntityManager->CreateEntity();
	//give the window a transform
	entity->addComponent<UI_Component_Transform>(UI_COMPONENT_TRANSFORM);
	//give the window an image
	entity->addComponent<UI_Component_Image>(UI_COMPONENT_IMAGE);
	//set the ui elements name
	entity->setName(name);

	return entity;
}

Entity* UIManager::createButton(std::string name)
{
	//create a new element
	Entity* entity = m_EntityManager->CreateEntity();
	//give the button a transform
	entity->addComponent<UI_Component_Transform>(UI_COMPONENT_TRANSFORM);
	//give the button an image
	entity->addComponent<UI_Component_Image>(UI_COMPONENT_IMAGE);
	//give the button the button functionality
	entity->addComponent<UI_Component_Button>(UI_COMPONENT_BUTTON);
	//set the ui elements name
	entity->setName(name);

	return entity;
}

Entity* UIManager::createTextBox(std::string name)
{
	//create a new element
	Entity* entity = m_EntityManager->CreateEntity();
	//give the button a transform
	entity->addComponent<UI_Component_Transform>(UI_COMPONENT_TRANSFORM);
	//give the textbox an image
	entity->addComponent<UI_Component_Image>(UI_COMPONENT_IMAGE);
	//set the ui elements name
	entity->setName(name);

	return entity;
}

Entity* UIManager::createImage(std::string name, char* filename)
{
	//create a new element
	Entity* entity = m_EntityManager->CreateEntity();
	//give the button a transform
	entity->addComponent<UI_Component_Transform>(UI_COMPONENT_TRANSFORM);
	//add an image component
	UI_Component_Image* imageComponent = (UI_Component_Image*)entity->addComponent<UI_Component_Image>(UI_COMPONENT_IMAGE);
	imageComponent->loadImage(filename);
	//set the ui elements name
	entity->setName(name);

	return entity;
}

void UIManager::LoadUI(std::string name)
{

}

void UIManager::update(GameTime gameTime)
{
	m_EntityManager->Update(gameTime);
}

void UIManager::draw()
{
	m_EntityManager->Draw();
}