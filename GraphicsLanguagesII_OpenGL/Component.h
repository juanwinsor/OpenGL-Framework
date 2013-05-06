#ifndef _COMPONENT_H
#define _COMPONENT_H


class Entity;

class Component
{
public:
	Component();
	~Component();

	virtual void Attach();
	virtual void Detach();
	virtual void Update(GameTime gameTime);
	virtual void Draw();

	Entity* Owner;
protected:
	
};

#endif