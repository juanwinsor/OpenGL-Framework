#include "common.h"
#include "Texture2D.h"

Texture2D::Texture2D(char* filePath)
{
	//load the texture and store the id to it
	m_TextureID = SOIL_load_OGL_texture(filePath, 0, 0 /* 0 will specify to let SOIL generate a texture ID for us */, SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//get the dimensions of the texture
	int mipLevel = 0;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, mipLevel, GL_TEXTURE_WIDTH, &m_Width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, mipLevel, GL_TEXTURE_HEIGHT, &m_Height);

	int test = 0;
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_TextureID);
	m_TextureID = 0;
}