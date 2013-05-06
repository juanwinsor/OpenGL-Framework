#ifndef __RENDERER2D_H
#define __RENDERER2D_H



#include "TextureFont.h"
#include "Shader.h"

class Renderer2D
{
public:
	static Renderer2D* getInstance();
	static void unloadInstance();

	void drawString(char* text, TextureFont* textureFont, Vector4 color, int justificationflags, float height, Matrix projectionMatrix);
	void drawTexture(GLuint texture, Vector4 destDimensions, Vector4 srcDimensions, Vector3 color, Vector2 origin, float rotation);

protected:
	Renderer2D();
	~Renderer2D();

	static Renderer2D* m_Instance;

	Shader* m_FontShader;
	Shader* m_SpriteShader;

	VertexDefinition m_Vertices[1000];
    GLushort m_Indices[1000];
};


#endif