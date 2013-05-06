#ifndef __RENDERABLETEXT_H
#define __RENDERABLETEXT_H


#include "Renderable.h"
#include "TextureFont.h"

class RenderableText : public Renderable
{
public:
	RenderableText();
	~RenderableText();

	void draw();


	void setText(char* text);
	void setColor(Vector4 color);
	void setPosition(Vector3 position);
	void setTextureFont(TextureFont* textureFont);
	void setJustification(int justification);
	void setFaceCamera(bool enabled);

protected:
	TextureFont* m_TextureFont;

	char* m_Text;
	Vector4 m_Color;
	Vector3 m_Position;
	int m_Justification;
	bool m_FaceCamera;
};


#endif