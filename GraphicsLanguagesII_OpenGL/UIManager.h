//Factory class for UI elements
//Uses the entity component system for the generic child parent structure

#ifndef __UIMANAGER_H
#define __UIMANAGER_H

#include "EntityManager.h"
#include "Entity.h"

class UIManager
{
public:
	static UIManager* getInstance();
	static void unloadInstance();

	

	//create premade ui elements
	Entity* createWindow(std::string name);
	Entity* createButton(std::string name);
	Entity* createTextBox(std::string name);
	Entity* createImage(std::string name, char* filename);

	//load UI data from a file
	void LoadUI(std::string name);

	void update(GameTime gameTime);
	void draw();

protected:
	UIManager();
	~UIManager();

	static UIManager* m_Instance;

	EntityManager* m_EntityManager;

};



#endif