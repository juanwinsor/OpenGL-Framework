#include "common.h"
#include "Renderer.h"
#include "Renderer2D.h"


//singleton
Renderer2D* Renderer2D::m_Instance = NULL;
Renderer2D* Renderer2D::getInstance()
{
	if(m_Instance == NULL)
	{
		m_Instance = new Renderer2D();
	}
	return m_Instance;
}

void Renderer2D::unloadInstance()
{
	if(m_Instance != NULL)
	{
		delete m_Instance;
		m_Instance = NULL;
	}
}

Renderer2D::Renderer2D()
{
	//load a shader to render the text with
	m_FontShader = new Shader("Content/Shaders/vsFont.glsl", "Content/Shaders/fsFont.glsl");
	glUniform4f(m_FontShader->vsColorHandle(), 1, 1, 1, 1);

	//load a shader to draw textures with
	m_SpriteShader = new Shader("Content/Shaders/vs.glsl", "Content/Shaders/fs.glsl");
	glUniform4f(m_SpriteShader->vsColorHandle(), 1, 1, 1, 1);
}

Renderer2D::~Renderer2D()
{
	delete m_FontShader;
	delete m_SpriteShader;
}

void Renderer2D::drawTexture(GLuint texture, Vector4 destinationDimensions, Vector4 sourceDimensions, Vector3 color, Vector2 origin, float rotation)
{

	float width = destinationDimensions.z; //destinationDimensions.z - destinationDimensions.x;
	float height = destinationDimensions.w;

	//top left
	m_Vertices[0].position[0] = 0 - origin.x;
	m_Vertices[0].position[1] = 0 + origin.y;
	m_Vertices[0].position[2] = 0;
	m_Vertices[0].color[0] = 1;
	m_Vertices[0].color[1] = 1;
	m_Vertices[0].color[2] = 1;
	m_Vertices[0].color[3] = 1;
	m_Vertices[0].uv[0] = 0;
	m_Vertices[0].uv[1] = 1;

	//bottom left
	m_Vertices[1].position[0] = 0 - origin.x;
	m_Vertices[1].position[1] = -height + origin.y;
	m_Vertices[1].position[2] = 0;
	m_Vertices[1].color[0] = 1;
	m_Vertices[1].color[1] = 1;
	m_Vertices[1].color[2] = 1;
	m_Vertices[1].color[3] = 1;
	m_Vertices[1].uv[0] = 0;
	m_Vertices[1].uv[1] = 0;

	//bottom right
	m_Vertices[2].position[0] = width - origin.x;
	m_Vertices[2].position[1] = -height + origin.y;
	m_Vertices[2].position[2] = 0;
	m_Vertices[2].color[0] = 1;
	m_Vertices[2].color[1] = 1;
	m_Vertices[2].color[2] = 1;
	m_Vertices[2].color[3] = 1;
	m_Vertices[2].uv[0] = 1;
	m_Vertices[2].uv[1] = 0;

	//top right
	m_Vertices[3].position[0] = width - origin.x;
	m_Vertices[3].position[1] = 0 + origin.y;
	m_Vertices[3].position[2] = 0;
	m_Vertices[3].color[0] = 1;
	m_Vertices[3].color[1] = 1;
	m_Vertices[3].color[2] = 1;
	m_Vertices[3].color[3] = 1;
	m_Vertices[3].uv[0] = 1;
	m_Vertices[3].uv[1] = 1;

	m_Indices[0] = 0;
	m_Indices[1] = 1;
	m_Indices[2] = 2;
	m_Indices[3] = 3;
	m_Indices[4] = 0;
	m_Indices[5] = 2;

	//calculate wvp matrix

	//use orthographic projection for 2d sprites
	Matrix ortho;
	ortho.SetIdentity();
	ortho.SetOrtho(0, Renderer::getInstance()->screenWidth(), 0, Renderer::getInstance()->screenHeight(), 1, -1);

	//sprite position
	Matrix pos;
	pos.SetIdentity();
	pos.Rotate(rotation, 0, 0, 1);
	pos.SetPosition(Vector3(destinationDimensions.x, destinationDimensions.y, 0));
	pos.Multiply(&ortho);


	//draw the texture
	m_SpriteShader->setTexture(texture);

	m_SpriteShader->apply();

	glUniformMatrix4fv(m_SpriteShader->worldViewProjectionHandle(), 1, false, (GLfloat*)&pos.m11);

	//vertex position
	glVertexAttribPointer(m_SpriteShader->vsPositionHandle(), 3, GL_FLOAT, GL_FALSE, sizeof(VertexDefinition), m_Vertices->position); //&Verts->position);
    glEnableVertexAttribArray(m_SpriteShader->vsPositionHandle());
	//vertex color
	glVertexAttribPointer(m_SpriteShader->vsColorHandle(), 4, GL_FLOAT, GL_FALSE, sizeof(VertexDefinition), m_Vertices->color); //m_Vertices->color); //&Verts->color);
    glEnableVertexAttribArray(m_SpriteShader->vsColorHandle());
	//uv coords
	glVertexAttribPointer(m_SpriteShader->vsUVCoordinateHandle(), 2, GL_FLOAT, GL_FALSE, sizeof(VertexDefinition), m_Vertices->uv);
    glEnableVertexAttribArray(m_SpriteShader->vsUVCoordinateHandle());
	
	//draw the elements
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, m_Indices);

	glDisableVertexAttribArray(m_SpriteShader->vsPositionHandle());
    glDisableVertexAttribArray(m_SpriteShader->vsColorHandle());
	glDisableVertexAttribArray(m_SpriteShader->vsUVCoordinateHandle());
}

void Renderer2D::drawString(char* text, TextureFont* textureFont, Vector4 color, int justificationflags, float height, Matrix worldViewProjectionMatrix)
{
	float uTL;
	float uBL;
	float uTR;
	float uBR;

	float vTL;
	float vBL;
	float vTR;
	float vBR;

	TextureFont::FontProperties fontProps = textureFont->fontProperties();
	float fw = fontProps.scaleW; //(textureFont.fontProperties()).scaleW;
	float fh = fontProps.scaleH;

	int cursorX = 0;

	int textLength = strlen(text);
	//to keep track of the full width of all of the quads together
	float stringWidth = 0;
	//keep track of the highest height
	float stringHeight = 0;

	float scale = height / fontProps.lineHeight;


	for(int i =0; i < textLength; i++)
	{
		for(int j = 0; j < textureFont->getNumberOfCharacters(); j++)
		{			
			if(textureFont->getCharacter(j).id == text[i])
			{
				//************************Calcluate the UV's
				//top left
				uTL = textureFont->getCharacter(j).x / fw;
				vTL = 1 - (textureFont->getCharacter(j).y / fh);
				//top right
				uTR = (textureFont->getCharacter(j).x + textureFont->getCharacter(j).width) / fw;
				vTR = vTL;
				//bottom left
				uBL = uTL;
				vBL = 1 - ((textureFont->getCharacter(j).y + textureFont->getCharacter(j).height) / fh);
				//bottom right
				uBR = uTR;
				vBR = vBL;

				//************************Populate vertex definitions
				//precalculate values
				int iTimes4 = i * 4;
				int iTimes6 = i * 6;

				//float scale = 0.2f;

				// upper left
				m_Vertices[iTimes4].position[0] = (cursorX + textureFont->getCharacter(j).xoffset) * scale;
				m_Vertices[iTimes4].position[1] = -textureFont->getCharacter(j).yoffset * scale; //(textureFont->getCharacter(j).height) * scale;
				m_Vertices[iTimes4].uv[0] = uTL;
				m_Vertices[iTimes4].uv[1] = vTL;

				// upper right
				m_Vertices[iTimes4 + 1].position[0] = (textureFont->getCharacter(j).width + cursorX + textureFont->getCharacter(j).xoffset) * scale;
				m_Vertices[iTimes4 + 1].position[1] = -textureFont->getCharacter(j).yoffset * scale; //(textureFont->getCharacter(j).height) * scale;
				m_Vertices[iTimes4 + 1].uv[0] = uTR;
				m_Vertices[iTimes4 + 1].uv[1] = vTR;

				// lower left
				m_Vertices[iTimes4 + 2].position[0] = (cursorX + textureFont->getCharacter(j).xoffset) * scale;
				m_Vertices[iTimes4 + 2].position[1] = (-textureFont->getCharacter(j).height - textureFont->getCharacter(j).yoffset) * scale;
				m_Vertices[iTimes4 + 2].uv[0] = uBL;
				m_Vertices[iTimes4 + 2].uv[1] = vBL;

				// lower right
				m_Vertices[iTimes4 + 3].position[0] = (textureFont->getCharacter(j).width + cursorX + textureFont->getCharacter(j).xoffset) * scale;
				m_Vertices[iTimes4 + 3].position[1] = (-textureFont->getCharacter(j).height - textureFont->getCharacter(j).yoffset) * scale;
				m_Vertices[iTimes4 + 3].uv[0] = uBR;
				m_Vertices[iTimes4 + 3].uv[1] = vBR;

				m_Indices[iTimes6] = iTimes4;
				m_Indices[iTimes6 + 1] = iTimes4 + 1;
				m_Indices[iTimes6 + 2] = iTimes4 + 2;
				m_Indices[iTimes6 + 3] = iTimes4 + 1;
				m_Indices[iTimes6 + 4] = iTimes4 + 3;
				m_Indices[iTimes6 + 5] = iTimes4 + 2;

				cursorX += textureFont->getCharacter(j).xadvance;

				//keep track of the last width
				stringWidth = m_Vertices[iTimes4 + 3].position[0];
				//keep track of the lowest height
				if(m_Vertices[iTimes4].position[1] < stringHeight)
				{
					stringHeight = m_Vertices[iTimes4 + 3].position[1];
				}

				break;
			}
		}
	}



	//determine justification from flags
	float justificationX = 0;
	float justificationY = 0;
	//determine x justification
	if((justificationflags & Justify_Left) == Justify_Left)
	{
		//set left most at the 0 point
		justificationX = 0;
	}
	else if((justificationflags & Justify_CenterX) == Justify_CenterX)
	{
		justificationX = -stringWidth / 2;
	}
	else if ((justificationflags & Justify_Right) == Justify_Right)
	{
		justificationX = -stringWidth;
	}
	//determine y justification
	if((justificationflags & Justify_Top) == Justify_Top)
	{
		justificationY = 0;
	}
	else if((justificationflags & Justify_CenterY) == Justify_CenterY)
	{
		justificationY = -stringHeight / 2;
	}
	else if ((justificationflags & Justify_Bottom) == Justify_Bottom)
	{
		justificationY = -stringHeight;
	}


	//initialize the rest of the data
    for( int j=0; j < textLength * 4; j++ )
    {
		m_Vertices[j].position[0] += justificationX;
		m_Vertices[j].position[1] += justificationY;
        m_Vertices[j].position[2] = 0;
		m_Vertices[j].color[0] = color.x;
		m_Vertices[j].color[1] = color.y;
		m_Vertices[j].color[2] = color.z;
        m_Vertices[j].color[3] = color.w;
    }


	//draw the string
	//set the font texture
	m_FontShader->setTexture(textureFont->getFontTexture());

	m_FontShader->apply();

	glUniformMatrix4fv(m_FontShader->worldViewProjectionHandle(), 1, false, (GLfloat*)&worldViewProjectionMatrix.m11);

	//vertex position
	glVertexAttribPointer(m_FontShader->vsPositionHandle(), 3, GL_FLOAT, GL_FALSE, sizeof(VertexDefinition), m_Vertices->position); //&Verts->position);
    glEnableVertexAttribArray(m_FontShader->vsPositionHandle());
	//vertex color
	glVertexAttribPointer(m_FontShader->vsColorHandle(), 4, GL_FLOAT, GL_FALSE, sizeof(VertexDefinition), m_Vertices->color); //m_Vertices->color); //&Verts->color);
    glEnableVertexAttribArray(m_FontShader->vsColorHandle());
	//uv coords
	glVertexAttribPointer(m_FontShader->vsUVCoordinateHandle(), 2, GL_FLOAT, GL_FALSE, sizeof(VertexDefinition), m_Vertices->uv);
    glEnableVertexAttribArray(m_FontShader->vsUVCoordinateHandle());
	
	//draw the elements
	glDrawElements(GL_TRIANGLES, textLength * 6, GL_UNSIGNED_SHORT, m_Indices);

	glDisableVertexAttribArray(m_FontShader->vsPositionHandle());
    glDisableVertexAttribArray(m_FontShader->vsColorHandle());
	glDisableVertexAttribArray(m_FontShader->vsUVCoordinateHandle());
}