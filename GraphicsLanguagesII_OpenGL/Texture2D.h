#ifndef __TEXTURE2D_H
#define __TEXTURE2D_H


class Texture2D
{
public:
	Texture2D(char* filePath);
	~Texture2D();

	int textureID(){ return m_TextureID; }
	int width() { return m_Width; }
	int height() { return m_Height; }
	
protected:
	GLuint m_TextureID;
	int m_Width;
	int m_Height;
};


#endif