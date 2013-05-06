#include "common.h"
#include "RenderTarget.h"


RenderTarget::RenderTarget(int width, int height, int minFilter, int magFilter)
{
	m_Texture = 0;
	m_RenderBuffer = 0;
	m_FrameBuffer = 0;

	m_Width = width;
	m_Height = height;

	m_MinFilter = minFilter;
	m_MagFilter = magFilter;


	initialize();

}

RenderTarget::~RenderTarget()
{
	unload();
}


void RenderTarget::bind()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER, m_FrameBuffer);
}

void RenderTarget::initialize()
{
	//check if the size is valid
	GLint maxFBSize;
	//get the maximum size
	glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &maxFBSize);
	//compare size to size specified
	if(m_Width > maxFBSize || m_Height > maxFBSize)
	{
		return;
	}

	//get a handle for the framebuffer
	glGenFramebuffers(1, &m_FrameBuffer);

	//create a color texture
	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	//initialize the texture data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	//set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_MinFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_MagFilter);
	glBindTexture(GL_TEXTURE_2D, 0);

	//create a depth texture
	glGenTextures(1, &m_DepthTexture);
	glBindTexture(GL_TEXTURE_2D, m_DepthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_Width, m_Height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_MinFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_MagFilter);
	glBindTexture(GL_TEXTURE_2D, 0);

	//create a renderbuffer
	//glGenRenderbuffers(1, &m_RenderBuffer);
	//glBindRenderbufferEXT(GL_RENDERBUFFER, m_RenderBuffer);
	//glRenderbufferStorageEXT(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, m_Width, m_Height);

	//bind the framebuffer
	glBindFramebufferEXT(GL_FRAMEBUFFER, m_FrameBuffer);
	//attach the color texture
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture, 0);
	//attach the depth texture
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthTexture, 0);
	//attach the renderbuffer
	//glFramebufferRenderbufferEXT(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RenderBuffer);

	//unbind the framebuffer
	glBindFramebufferEXT(GL_FRAMEBUFFER, 0);

	//if creation failed then cleanup
	GLint fbStatus = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER);
	if(fbStatus != GL_FRAMEBUFFER_COMPLETE)
	{
		//cleanup the objects
		unload();
	}
}

void RenderTarget::unload()
{
	if(m_Texture != 0)
	{
		glDeleteTextures(1, &m_Texture);
	}
	if(m_RenderBuffer != 0)
	{
		glDeleteRenderbuffers(1, &m_RenderBuffer);
	}
	if(m_FrameBuffer != 0)
	{
		glDeleteFramebuffers(1, &m_FrameBuffer);
	}
	if(m_DepthTexture != 0)
	{
		glDeleteTextures(1, &m_DepthTexture);
	}

	m_Texture = 0;
	m_RenderBuffer = 0;
	m_FrameBuffer = 0;
	m_DepthTexture = 0;
}