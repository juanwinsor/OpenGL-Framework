#include "common.h"
#include "Renderer2D.h"
#include "RenderableText.h"
#include "Renderer.h"

RenderableText::RenderableText()
{
	m_Text = NULL;
	m_Justification = 0;
	m_TextureFont = NULL;

}

RenderableText::~RenderableText()
{

}

void RenderableText::draw()
{
	Matrix world;
	world.SetIdentity();
	world.SetPosition(m_Position);
	
	world = Renderer::getInstance()->camera()->worldViewProjection(world);	

	//always face the camera
	if(m_FaceCamera)
	{
		//0 out the world rotation to make always facing camera
		world.m14 = 0;
		world.m24 = 0;
		world.m34 = 0;	
	}

	Renderer2D::getInstance()->drawString(m_Text, m_TextureFont, m_Color, m_Justification, 1.0f, world);
}


void RenderableText::setText(char* text)
{
	m_Text = text;
}

void RenderableText::setColor(Vector4 color)
{
	m_Color = color;
}

void RenderableText::setPosition(Vector3 position)
{
	m_Position = position;
}

void RenderableText::setTextureFont(TextureFont* textureFont)
{
	m_TextureFont = textureFont;
}

void RenderableText::setJustification(int justification)
{
	m_Justification = justification;
}

void RenderableText::setFaceCamera(bool enabled)
{
	m_FaceCamera = enabled;
}