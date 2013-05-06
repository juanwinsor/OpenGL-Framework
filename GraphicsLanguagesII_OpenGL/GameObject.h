#ifndef __GAMEOBJECT_H
#define __GAMEOBJECT_H



class GameObject
{
public:
	GameObject();
	~GameObject();

	void virtual update(GameTime gameTime);

	void setPosition(Vector3 position);
	Vector3 getPosition();
protected:
	bool m_Active;

	Vector3 m_Position;
	Vector3 m_Rotation;
	Vector3 m_Velocity;
	
	float m_Health;

	GLint m_TextureID;
	
};


#endif