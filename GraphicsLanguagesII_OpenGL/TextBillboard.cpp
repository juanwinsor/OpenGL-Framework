#include "common.h"
#include "TextBillboard.h"

TextBillboard::TextBillboard()
{
	m_FaceCamera = true;

	//create a texture font to draw with
	//TODO: remove this and add error checking for valid texture font instead
	m_TextureFont = new TextureFont("Content/Fonts/amble47.fnt");

	//create a renderable text object
	m_RenderableText = new RenderableText();
	m_RenderableText->setColor(Vector4(1, 1, 1, 1));
	m_RenderableText->setPosition(Vector3(0, 0, 0));
	m_RenderableText->setText("billboard");
	m_RenderableText->setJustification(Justify_CenterX | Justify_CenterY);
	m_RenderableText->setTextureFont(m_TextureFont);
	//add text to the renderer
	Renderer::getInstance()->addRenderable(m_RenderableText);
}

TextBillboard::~TextBillboard()
{
	Renderer::getInstance()->deleteRenderable(m_RenderableText);

	delete m_TextureFont;
	delete m_RenderableText;
}

void TextBillboard::update(GameTime gameTime)
{
	m_RenderableText->setPosition(m_Position);
}

void TextBillboard::setColor(Vector4 color)
{
	m_RenderableText->setColor(color);
}


void TextBillboard::setPosition(Vector3 position)
{
	m_RenderableText->setPosition(position);
}

void TextBillboard::setText(char* text)
{
	m_RenderableText->setText(text);
}

void TextBillboard::setJustification(int justification)
{
	m_RenderableText->setJustification(justification);
}


void TextBillboard::setTextureFont(TextureFont* textureFont)
{
	m_RenderableText->setTextureFont(textureFont);
}

void TextBillboard::setFaceCamera(bool enabled)
{
	m_FaceCamera = enabled;
	m_RenderableText->setFaceCamera(enabled);
}