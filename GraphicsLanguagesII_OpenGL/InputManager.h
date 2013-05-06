#ifndef __INPUTMANAGER_H
#define __INPUTMANAGER_H



class InputManager
{
public:
	static InputManager* getInstance();
	static void unloadInstance();

	Vector2 mousePosition();
	int mouseButton(int button);

	void update();
protected:
	InputManager();
	~InputManager();
	static InputManager* m_Instance;

	Vector2 m_MousePosition;

};

#endif