#ifndef __LIGHTMANAGER_H
#define __LIGHTMANAGER_H

#include "Utility\Vector.h"
#include "Material.h"
#include "Shader.h"

#define MAXLIGHTS 8

enum LightingMode
{
	LIGHTINGMODE_NONE, //no lights
	LIGHTINGMODE_NORMAL, //diffuse/specular
	//LIGHTINGMODE_BUMPTANGENTSPACE //normal mapping
};

enum LightType
{
	LIGHT_DIRECTIONAL,
	LIGHT_POINT,
	LIGHT_SPOT,	
	LIGHT_AMBIENT
};

struct Light
{
	char* Name;
	LightType Type;
	Vector3 Position;
	Vector3 Direction;
	bool Enabled;
	Vector4 AmbientColor;
	Vector4 DiffuseColor;
	Vector4 SpecularColor;
	Vector3 Attenuation;
};



class LightManager
{
public:
	static LightManager* getInstance();
	static void unloadInstance();

	Light* addLight(LightType lightType);
	Light* getLight(int index);
	
	void update();

	void setMaterial(Material* material);
	Material* material(){ return m_Material; };

	Shader* shader();
protected:
	static LightManager* m_Instance;

	LightManager();
	~LightManager();

	void updateLights();
	void updateMaterial();
	

	//vector<Light*> m_Lights;
	Light* m_Lights[MAXLIGHTS];

	Material* m_Material;

	Shader* m_Shader;
};

#endif
