#include <vector>
#include "common.h"
#include "LightManager.h"
#include "Renderer.h"

using namespace std;


LightManager::LightManager()
{
	m_Shader = new Shader("Content/Shaders/vsLights.glsl", "Content/Shaders/fsLights.glsl");
	m_Shader->setTexture(0);
	m_Material = NULL;
	//m_Material = new Material();
	//m_Material->setShader(NULL);

	//null out initial lights
	for(int i = 0; i < MAXLIGHTS; i++)
	{
		m_Lights[i] = NULL;
	}
}

LightManager::~LightManager()
{
	if(m_Shader != NULL)
	{
		delete m_Shader;
	}

	if(m_Material != NULL)
	{
		delete m_Material;
	}
}


LightManager* LightManager::m_Instance = NULL;

LightManager* LightManager::getInstance()
{
	if(m_Instance == NULL)
	{
		m_Instance = new LightManager();
	}
	return m_Instance;
}

void LightManager::unloadInstance()
{
	if(m_Instance != NULL)
	{
		delete m_Instance;
		m_Instance = NULL;
	}
}

Light* LightManager::addLight(LightType lightType)
{
	Light* light = new Light();
	light->Type = lightType;

	switch(lightType)
	{
	case LIGHT_DIRECTIONAL:
		light->Position = Vector3(0, 0, 0);
		light->Direction = Vector3(0.6, -0.5, -0.3);
		light->DiffuseColor = Vector4(1, 0, 0, 1);
		light->AmbientColor = Vector4(0.2, 0.2, 0.2, 1);
		light->SpecularColor = Vector4(1, 1, 1, 1);
		light->Attenuation = Vector3(0, 0, 0);
		light->Enabled = true;
		light->Type = lightType;
		//light->
		break;

	case LIGHT_POINT:
		light->Position = Vector3(0, 15, 0);
		light->Direction = Vector3(0, 0, 0);
		light->DiffuseColor = Vector4(1, 1, 1, 1);
		light->Enabled = true;
		light->Type = lightType;
		light->AmbientColor = Vector4(0.2, 0.2, 0.2, 1);
		light->SpecularColor = Vector4(1, 1, 1, 1);
		light->Attenuation = Vector3(0.001f, 0.01, 0.2);
		break;

	case LIGHT_SPOT:
		light->Position = Vector3(10, 8, 10);
		light->Direction = Vector3(0.4, 0.9, 0.6);
		light->DiffuseColor = Vector4(1, 1, 1, 1);
		light->Enabled = true;
		light->Type = lightType;
		light->AmbientColor = Vector4(0.2, 0.2, 0.2, 1);
		light->SpecularColor = Vector4(1, 1, 1, 1);
		light->Attenuation = Vector3(15, 12, 3);
		break;
	}

	for(int i = 0; i < MAXLIGHTS; i++)
	{
		if(m_Lights[i] == NULL)
		{
			m_Lights[i] = light;
			break;
		}
	}


	return light;
}

void LightManager::setMaterial(Material* material)
{
	m_Material = material;
	updateMaterial();
}

void LightManager::updateLights()
{
	/*if(m_Material != NULL && m_Material->shader() != NULL)
	{
		GLint texID = m_Material->shader()->textureID();
		m_Shader->setTexture(texID);
	}*/

	for(int i = 0; i < MAXLIGHTS; i++)
	{
		if(m_Lights[i] != NULL)
		{
			//char* uniformNameEnabled = new char[128];
			char uniformNameEnabled[128];
			sprintf(uniformNameEnabled, "u_Light[%i].enabled", i);
			m_Shader->setUniform(uniformNameEnabled, m_Lights[i]->Enabled);
			//delete uniformNameEnabled;

			char un[128];
			char* uniformNameType = new char[128];
			sprintf(uniformNameType, "u_Light[%i].type", i);
			m_Shader->setUniform(uniformNameType, (GLint)m_Lights[i]->Type);
			delete uniformNameType;

			char* uniformNamePosition = new char[128];
			sprintf(uniformNamePosition, "u_Light[%i].position", i);
			m_Shader->setUniform(uniformNamePosition, m_Lights[i]->Position);
			delete uniformNamePosition;

			char* uniformNameDirection = new char[128];
			sprintf(uniformNameDirection, "u_Light[%i].direction", i);
			m_Shader->setUniform(uniformNameDirection, m_Lights[i]->Direction);
			delete uniformNameDirection;

			char* uniformNameDiffuse = new char[128];
			sprintf(uniformNameDiffuse, "u_Light[%i].diffuseColor", i);
			m_Shader->setUniform(uniformNameDiffuse, m_Lights[i]->DiffuseColor);
			delete uniformNameDiffuse;

			char* uniformNameAmbient = new char[128];
			sprintf(uniformNameAmbient, "u_Light[%i].ambientColor", i);
			m_Shader->setUniform(uniformNameAmbient, m_Lights[i]->AmbientColor);
			delete uniformNameAmbient;

			char* uniformNameSpecular = new char[128];
			sprintf(uniformNameSpecular, "u_Light[%i].specularColor", i);
			m_Shader->setUniform(uniformNameSpecular, m_Lights[i]->SpecularColor);
			delete uniformNameSpecular;

			char* uniformNameAttenuation = new char[128];
			sprintf(uniformNameAttenuation, "u_Light[%i].attenuation", i);
			m_Shader->setUniform(uniformNameAttenuation, m_Lights[i]->Attenuation);
			delete uniformNameAttenuation;
		}
		else
		{
			char* uniformNameEnabled = new char[128];
			sprintf(uniformNameEnabled, "u_Light[%i].enabled", i);
			m_Shader->setUniform(uniformNameEnabled, 0);
			delete uniformNameEnabled;
		}
	}
}

void LightManager::updateMaterial()
{
	if(m_Material != NULL && m_Material->shader() != NULL)
	{
		m_Shader->setTexture(m_Material->shader()->textureID());
	}

	if(m_Shader != NULL && m_Material != NULL)
	{
		m_Shader->setUniform("u_Material.ambient",  m_Material->ambient());
		m_Shader->setUniform("u_Material.diffuse", m_Material->diffuse());
		m_Shader->setUniform("u_Material.specular", m_Material->specular());
		m_Shader->setUniform("u_Material.specularPower", m_Material->specularPower());
	}

	
}

Light* LightManager::getLight(int index)
{
	return m_Lights[index];
}


Shader* LightManager::shader()
{ 
	return m_Shader; 
}

void LightManager::update()
{
	updateLights();
	//updateMaterial();
	Camera* cam = Renderer::getInstance()->camera();
	m_Shader->setUniform("u_CameraPosition", cam->getPosition());
}