#ifndef __GAMEMAIN_H
#define __GAMEMAIN_H


#include "GameObject.h"
#include "Quad.h"
#include "TextureFont.h"
#include "RenderTarget.h"
#include "Texture2D.h"
#include "Model.h"

class RenderableModel;

#define MAX_GAME_OBJECTS 100

class GameMain
{
public:
	GameMain();
	~GameMain();

	void initialize();
	void update(GameTime gameTime);
	void draw(GameTime gameTime);
protected:

	Quad* m_Quad;

	GameObject* m_GameObjects[MAX_GAME_OBJECTS];
	

	float m_TotalTime;
	int m_Score;

	//texture font
	TextureFont* m_Font;
	TextureFont* m_FontPapyrus;

	Texture2D* m_TestTexture;
	Texture2D* m_DefaultTexture;

	RenderTarget* m_RenderTarget;

	Model* m_Model;


	GLuint m_CubeMapID;
	

	RenderableModel* m_HorseModel;


	bool m_LightButton1Pressed;
	bool m_LightButton2Pressed;
	bool m_LightButton3Pressed;
	bool m_LightButton4Pressed;

	//light world matrix
	Matrix m_PointLightWorld;
	RenderableModel* m_LightSphereModel;

	Matrix m_RedBarrelWorld;
	RenderableModel* m_RedBarrelModel;
};

#endif