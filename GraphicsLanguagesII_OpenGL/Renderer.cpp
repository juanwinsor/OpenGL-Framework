#include "common.h"
#include "Renderer.h"
#include "Renderable2D.h"
#include "Quad.h"
#include "Renderer2D.h"

using namespace std;

//window resize callback
void GLFWCALL windowResize(int width, int height)
{
	glViewport( 0, 0, width, height );
	Renderer::getInstance()->updateSurface(width, height);
}

//singleton
Renderer* Renderer::m_Instance = NULL;
Renderer* Renderer::getInstance()
{
	if(m_Instance == NULL)
	{
		m_Instance = new Renderer();
	}
	return m_Instance;
}

void Renderer::unloadInstance()
{
	if(m_Instance != NULL)
	{
		delete m_Instance;
		m_Instance = NULL;
	}
}

Renderer::Renderer()
{
	
}

Renderer::~Renderer()
{
	//cleanup internal objects
	delete m_Camera;
	m_Camera = NULL;
}

void Renderer::updateSurface(int screenWidth, int screenHeight)
{
	m_ScreenWidth = screenWidth;
	m_ScreenHeight = screenHeight;
}

void Renderer::addRenderable(Renderable* renderable)
{
	//add the new renderable to the list
	if(renderable != NULL)
	{
		m_RenderableList.push_back(renderable);
	}
}

void Renderer::add2DRenderable(Renderable* renderable)
{
	//add the new renderable to the list
	if(renderable != NULL)
	{
		m_RenderableList2D.push_back(renderable);
	}
}

void Renderer::deleteRenderable(Renderable* renderable)
{
	for(int i = 0; i < m_RenderableList.size(); i ++)
	{
		if(m_RenderableList[i] == renderable)
		{
			m_RenderableList.erase(m_RenderableList.begin() + i);
		}
	}
}

void Renderer::initialize()
{
	//initialize glfw
	glfwInit();

	m_ScreenWidth = 1280;
	m_ScreenHeight = 720;

	//open a gl window
	if(!glfwOpenWindow(m_ScreenWidth, m_ScreenHeight, 8, 8, 8, 8, 31, 1, GLFW_WINDOW))	
	{
		//clean up glfw if a window couldn't be opened
		glfwTerminate();
	}

	glfwSetWindowTitle("Graphics Languages II");

	glfwDisable(GLFW_AUTO_POLL_EVENTS);
	glfwEnable(GLFW_STICKY_KEYS);
	glfwEnable(GLFW_STICKY_MOUSE_BUTTONS);

	//enable alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//initialize glew
	glewInit();

	//initialize viewport
	windowResize(m_ScreenWidth, m_ScreenHeight);

	glfwSetWindowSizeCallback(windowResize);

	m_Camera = new Camera(m_ScreenWidth, m_ScreenHeight);


	m_ShowFPS = false;
	m_FPS = 0;

	m_DefaultTextureFont = new TextureFont("Content/Fonts/amble47.fnt");
}

Camera* Renderer::camera()
{
	return m_Camera;
}

void Renderer::clear()
{
	glClearDepth(1.0f);
	glClearColor(0.39f, 0.584f, 0.9294f, 1.0f); //cornflower blue	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	
}

void Renderer::draw(GameTime gameTime)
{
	m_GameTime = gameTime;

	//wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
	//draw all 3d renderables
	for(int i = 0; i < m_RenderableList.size(); i++)
	{
		(m_RenderableList[i])->draw();		
	}
	
	//draw all 2d renderables
	//for(int i = 0; i < m_RenderableList2D.size(); i++)
	//{
	//	((Renderable2D*)m_RenderableList2D[i])->draw();		
	//}


	
	
}

void Renderer::drawTexture(GLuint textureID, Vector4 sourceDimensions, Vector4 destinationDimensions, Vector4 color, float rotation, Vector2 origin)
{

}

void Renderer::begin()
{
	clear();

	//enable depth test for drawing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDepthMask( GL_TRUE );
	//glDepthRange(1.0f, 0.0f);
	glDepthRange(1.0f, 0.0f);
}

void Renderer::end()
{

	if(m_ShowFPS)
	{
		calculateFPS(m_GameTime);
		char fps[20];
		sprintf(fps, "FPS: %0.1f", m_FPS);
		drawString(m_DefaultTextureFont, fps, Vector3(m_ScreenWidth, m_ScreenHeight, 0), Vector4(1, 1, 0, 1), 30.0f, Justify_Right | Justify_Top);
	}


	//present
	glfwSwapBuffers();

	glDisable(GL_DEPTH_TEST);
}


int Renderer::screenWidth()
{
	return m_ScreenWidth;
}

int Renderer::screenHeight()
{
	return m_ScreenHeight;
}


void Renderer::drawString(TextureFont* textureFont, char* string, Vector3 position, Vector4 color, float size, int justification)
{
	Matrix ortho;
	ortho.SetIdentity();
	ortho.SetOrtho(0, m_ScreenWidth, 0, m_ScreenHeight, 1, -1);

	Matrix pos;
	pos.SetIdentity();
	pos.SetPosition(position);
	pos.Multiply(&ortho);


	Renderer2D::getInstance()->drawString(string, textureFont, color, justification, size, pos);
}

void Renderer::showFPS(bool enabled)
{
	m_ShowFPS = enabled;
}

void Renderer::calculateFPS(GameTime gameTime)
{	
	static double initialTime = glfwGetTime();
	static int frameCount = 0;
	float interval = 1.0f;

	if((gameTime.TotalTime - initialTime) > interval)
	{
		m_FPS = (float)(frameCount / (gameTime.TotalTime - initialTime));

		frameCount = 0;
		initialTime = glfwGetTime();
	}
	else
	{
		frameCount++;
	}
}