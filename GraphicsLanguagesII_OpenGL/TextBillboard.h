#ifndef __TEXTBILLBOARD_H
#define __TEXTBILLBOARD_H

#include "RenderableText.h"
#include "TextureFont.h"
#include "Renderer.h"
#include "GameObject.h"

class TextBillboard : public GameObject
{
public:
	TextBillboard();
	~TextBillboard();

	void update(GameTime gameTime);

	void setColor(Vector4 color);
	void setPosition(Vector3 position);
	void setText(char* text);
	void setJustification(int justification);
	void setTextureFont(TextureFont* textureFont);
	void setFaceCamera(bool enabled);

protected:
	RenderableText* m_RenderableText;
	TextureFont* m_TextureFont;

	bool m_FaceCamera;
};


#endif