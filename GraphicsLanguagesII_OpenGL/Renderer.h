#ifndef __RENDERER_H
#define __RENDERER_H

#include <vector>
#include "Renderable.h"
#include "Camera.h"
#include "TextureFont.h"
#include "Utility\Vector.h"

class Renderer
{
public:
	static Renderer* getInstance();
	static void unloadInstance();
	
	void addRenderable(Renderable* renderable);
	void add2DRenderable(Renderable* renderable);
	void deleteRenderable(Renderable* renderable);

	void initialize();
	void clear();
	void begin();
	void draw(GameTime gameTime);
	void end();


	void drawString(TextureFont* textureFont, char* string, Vector3 position, Vector4 color, float size, int justification);
	void drawTexture(GLuint textureID, Vector4 sourceDimensions, Vector4 destinationDimensions, Vector4 color, float rotation, Vector2 origin);

	void showFPS(bool enabled);

	Camera* camera();
		
	void updateSurface(int screenWidth, int screenHeight);

	int screenWidth();
	int screenHeight();

protected:
	Renderer();
	~Renderer();
	static Renderer* m_Instance;


	void calculateFPS(GameTime gameTime);

	int m_ScreenWidth;
	int m_ScreenHeight;

	GameTime m_GameTime;

	Camera* m_Camera;

	bool m_ShowFPS;
	float m_FPS;

	TextureFont* m_DefaultTextureFont;

	std::vector<Renderable*> m_RenderableList2D;
	std::vector<Renderable*> m_RenderableList;
};

#endif
