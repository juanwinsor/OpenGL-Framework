#ifndef __RENDERTARGET_H
#define __RENDERTARGET_H



class RenderTarget
{
public:
	RenderTarget(int width, int height, int minFilter, int magFilter);
	~RenderTarget();

	void bind();
	GLuint texture(){ return m_Texture; }
	GLuint renderBuffer(){ return m_RenderBuffer; }
	GLuint frameBuffer(){ return m_FrameBuffer; }
	GLuint depthTexture(){ return m_DepthTexture; }

protected:
	GLuint m_Texture;
	GLuint m_DepthTexture;
	GLuint m_RenderBuffer;
	GLuint m_FrameBuffer;

	int m_Width;
	int m_Height;

	int m_MinFilter;
	int m_MagFilter;

	void unload();
	void initialize();
};


#endif