#include "common.h"
#include "GameMain.h"
#include "Renderer.h"
#include "Renderer2D.h"
#include "RenderableElements.h"
#include "Spaceship.h"


#include "Player.h"
#include "Quad.h"
#include "TextBillboard.h"
#include "TextureFont.h"

#include "UIManager.h"
#include "UI_Component_Transform.h"

#include "RenderableModel.h"
#include "Material.h"

GameMain::GameMain()
{
	//initialization
	m_TotalTime = 0;
	m_Score = 0;


	m_LightButton1Pressed = false;
	m_LightButton2Pressed = false;
	m_LightButton3Pressed = false;
	m_LightButton4Pressed = false;


	//*********************************************2D********************************************
	m_TestTexture = new Texture2D("Content/Textures/firefly.png");
	m_DefaultTexture = new Texture2D("Content/Textures/1px.png");
	
	m_CubeMapID = SOIL_load_OGL_single_cubemap("Content/Textures/field_128_cube.dds", SOIL_DDS_CUBEMAP_FACE_ORDER, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);


	//*********************************************UI********************************************
	//Add an image UI element
	Entity* img = UIManager::getInstance()->createImage("firefly", "Content/Textures/firefly.png");
	((UI_Component_Transform*)img->getComponent(UI_COMPONENT_TRANSFORM))->SetPosition(Vector3(0, 400, 0));

	
	//********************************************3D********************************************

	//lights
	Light* dirLight_Red = LightManager::getInstance()->addLight(LIGHT_DIRECTIONAL);
	dirLight_Red->DiffuseColor = Vector4(1, 0, 0, 1);
	dirLight_Red->Direction = Vector3(-1, -1, 0);

	Light* dirLight_Blue = LightManager::getInstance()->addLight(LIGHT_DIRECTIONAL);
	dirLight_Blue->DiffuseColor = Vector4(0, 0, 1, 1);
	dirLight_Blue->Direction = Vector3(1, -1, 0);

	LightManager::getInstance()->addLight(LIGHT_POINT);

	LightManager::getInstance()->addLight(LIGHT_SPOT);



	//***************************************Plane
	//create world matrix
	Matrix planeWorld;
	planeWorld.SetIdentity();
	planeWorld.SetPosition(0, 0, 0);
	//planeWorld.Scale(10, 10, 10);

	//create model
	RenderableModel* planeModel = new RenderableModel();
	planeModel->LoadModel("Content/Models/plane.obj");
	planeModel->setWorld(planeWorld);	
	planeModel->setLightingMode(LIGHTINGMODE_NORMAL);

	//create shader
	Shader* planeShader = new Shader("Content/Shaders/vsLights.glsl", "Content/Shaders/fsLights.glsl");
	planeShader->setTexture(m_DefaultTexture->textureID());	

	//create material
	Material* planeMaterial = new Material();
	//horseMaterial->setDiffuse(0.7f, 0.7f, 0.7f, 1);
	planeMaterial->setShader(planeShader);
	planeModel->setMaterial(planeMaterial);	

	Renderer::getInstance()->addRenderable(planeModel);


	//***************************************Light Sphere

	m_PointLightWorld.SetIdentity();
	m_PointLightWorld.SetPosition(0, 10, 0);

	//create model
	m_LightSphereModel = new RenderableModel();
	m_LightSphereModel->LoadModel("Content/Models/sphere.obj");
	m_LightSphereModel->setWorld(m_PointLightWorld);	
	m_LightSphereModel->setLightingMode(LIGHTINGMODE_NORMAL);

	//create shader
	Shader* lightSphereShader = new Shader("Content/Shaders/vsLights.glsl", "Content/Shaders/fsLights.glsl");
	lightSphereShader->setTexture(m_DefaultTexture->textureID());	

	//create material
	Material* lightSphereMaterial = new Material();
	//horseMaterial->setDiffuse(0.7f, 0.7f, 0.7f, 1);
	lightSphereMaterial->setShader(lightSphereShader);
	m_LightSphereModel->setMaterial(lightSphereMaterial);	

	Renderer::getInstance()->addRenderable(m_LightSphereModel);




	//***************************************White Sphere
	//create world matrix
	Matrix whiteSphereWorld;
	whiteSphereWorld.SetIdentity();
	whiteSphereWorld.SetPosition(3, 2, 0);
	//whiteSphereWorld.Scale(20, 20, 20);

	//create model
	RenderableModel* whiteSphereModel = new RenderableModel();
	whiteSphereModel->LoadModel("Content/Models/sphere.obj");
	whiteSphereModel->setWorld(whiteSphereWorld);	
	whiteSphereModel->setLightingMode(LIGHTINGMODE_NORMAL);

	//create shader
	Shader* whiteSphereShader = new Shader("Content/Shaders/vsLights.glsl", "Content/Shaders/fsLights.glsl");
	whiteSphereShader->setTexture(m_DefaultTexture->textureID());

	//create material
	Material* whiteSphereMaterial = new Material();
	whiteSphereMaterial->setDiffuse(1, 1, 1, 1);
	whiteSphereMaterial->setShader(whiteSphereShader);
	whiteSphereModel->setMaterial(whiteSphereMaterial);	

	Renderer::getInstance()->addRenderable(whiteSphereModel);


	//***************************************Blue Box
	//create world matrix
	Matrix blueBoxWorld;
	blueBoxWorld.SetIdentity();
	blueBoxWorld.SetPosition(4, 5, -5);
	//whiteSphereWorld.Scale(20, 20, 20);

	//create model
	RenderableModel* blueBoxModel = new RenderableModel();
	blueBoxModel->CreateCube(2, 2, 2);
	blueBoxModel->setWorld(blueBoxWorld);	
	blueBoxModel->setLightingMode(LIGHTINGMODE_NORMAL);

	//create shader
	Shader* blueBoxShader = new Shader("Content/Shaders/vsLights.glsl", "Content/Shaders/fsLights.glsl");
	blueBoxShader->setTexture(m_DefaultTexture->textureID());

	//create material
	Material* blueBoxMaterial = new Material();
	blueBoxMaterial->setDiffuse(0, 0, 1, 1);
	blueBoxMaterial->setShader(blueBoxShader);
	blueBoxModel->setMaterial(blueBoxMaterial);	

	Renderer::getInstance()->addRenderable(blueBoxModel);


	//***************************************Red Barrel
	//create world matrix
	m_RedBarrelWorld.SetIdentity();
	m_RedBarrelWorld.SetPosition(-5, 0, 0);

	//create model
	m_RedBarrelModel = new RenderableModel();
	m_RedBarrelModel->LoadModel("Content/models/barrel.obj");
	m_RedBarrelModel->setWorld(m_RedBarrelWorld);	
	m_RedBarrelModel->setLightingMode(LIGHTINGMODE_NORMAL);

	//create shader
	Shader* redBarrelShader = new Shader("Content/Shaders/vsLights.glsl", "Content/Shaders/fsLights.glsl");
	redBarrelShader->setTexture(m_DefaultTexture->textureID());

	//create material
	Material* redBarrelMaterial = new Material();
	redBarrelMaterial->setDiffuse(1, 0, 0, 1);
	redBarrelMaterial->setShader(redBarrelShader);
	m_RedBarrelModel->setMaterial(redBarrelMaterial);	

	Renderer::getInstance()->addRenderable(m_RedBarrelModel);

	/*
	//***************************************Barrel
	//testing models
	Matrix barrelWorld;
	barrelWorld.SetIdentity();
	barrelWorld.SetPosition(-8, 0, 0);

	//barrelWorld.Scale(0.5f, 0.5f, 0.5f);

	Shader* shader = new Shader("Content/Shaders/vsLights.glsl", "Content/Shaders/fsLights.glsl");
	shader->setTexture(m_TestTexture->textureID());
	RenderableModel* model = new RenderableModel();
	//model->LoadModel("Content/Models/barrel.obj");
	model->LoadModel("Content/Models/barrel.obj");
	//model->setShader(shader);
	//model->setTextureID(m_TestTexture->textureID());
	model->setWorld(barrelWorld);

	model->setLightingMode(LIGHTINGMODE_NORMAL);

	Material* material = new Material();
	material->setShader(shader);
	//material->setShader(NULL);
	model->setMaterial(material);

	Renderer::getInstance()->addRenderable(model);
	*/


	//***********************************Horse
	//create model world matrix
	Matrix horseWorld;
	horseWorld.SetIdentity();
	horseWorld.Rotate(60, 0, 1, 0);
	horseWorld.SetPosition(15, 0, 0);	

	//create model
	RenderableModel* horseModel = new RenderableModel();
	horseModel->LoadModel("Content/Models/horse.obj");
	horseModel->setWorld(horseWorld);	
	horseModel->setLightingMode(LIGHTINGMODE_NORMAL);

	//create shader
	Shader* horseShader = new Shader("Content/Shaders/vsLights.glsl", "Content/Shaders/fsLights.glsl");
	horseShader->setTexture(m_DefaultTexture->textureID());	

	//create material
	Material* horseMaterial = new Material();
	//horseMaterial->setDiffuse(0.7f, 0.7f, 0.7f, 1);
	horseMaterial->setShader(horseShader);
	horseModel->setMaterial(horseMaterial);	

	m_HorseModel = horseModel;

	Renderer::getInstance()->addRenderable(horseModel);


	//************************************Cube
	Matrix cubeWorld;
	cubeWorld.SetIdentity();
	cubeWorld.SetPosition(10, 0, 0);	

	RenderableModel* cube = new RenderableModel();
	cube->CreateCube(2, 2, 2);
	cube->setWorld(cubeWorld);
	cube->setLightingMode(LIGHTINGMODE_NORMAL);

	Shader* cubeShader = new Shader("Content/Shaders/vsLights.glsl", "Content/Shaders/fsLights.glsl");
	cubeShader->setTexture(m_DefaultTexture->textureID());	

	//create material
	Material* cubeMaterial = new Material();
	//horseMaterial->setDiffuse(0.7f, 0.7f, 0.7f, 1);
	cubeMaterial->setShader(cubeShader);
	cube->setMaterial(cubeMaterial);

	Renderer::getInstance()->addRenderable(cube);


	/*****************************************Sphere with cubemap
	//sphere test for cubemap
	Shader* sphereShader = new Shader("Content/Shaders/vsCubeMap.glsl", "Content/Shaders/fsCubeMap.glsl");	
	sphereShader->setUniform("u_CubeMap", m_CubeMapID, 1, GL_TEXTURE_CUBE_MAP);
	RenderableModel* sphereModel = new RenderableModel();
	sphereModel->LoadModel("Content/Models/Sphere.obj");
	//sphereModel->setShader(sphereShader);
	//sphereModel->setTextureID(m_TestTexture->textureID());

	Material* sphereMaterial = new Material();
	sphereMaterial->setShader(sphereShader);
	sphereModel->setMaterial(sphereMaterial);

	//world matrix
	Matrix sphereWorld;
	sphereWorld.SetIdentity();
	sphereWorld.SetPosition(3, 0, 0);
	sphereWorld.Scale(20, 20, 20);

	//set uniforms
	sphereShader->setUniform("u_WorldMatrix", sphereWorld);
	sphereShader->setUniform("u_CameraPosition", Renderer::getInstance()->camera()->getPosition());
	sphereModel->setWorld(sphereWorld);

	sphereModel->setLightingMode(LIGHTINGMODE_NONE);

	//add sphere to renderer
	Renderer::getInstance()->addRenderable(sphereModel);
	*/



	//**************************************************old stuff
	/*for(int i = 0; i < MAX_GAME_OBJECTS; i++)
	{
		m_GameObjects[i] = NULL;
	}*/

	////create 2 spaceships
	//m_GameObjects[0] = new Player(1);
	//m_GameObjects[0]->setPosition(Vector3(-2.0f, 0, 0));
	//m_GameObjects[1] = new Player(2);
	//m_GameObjects[1]->setPosition(Vector3(2.0f, 0, 0));

	////create billboards for player names
	//TextBillboard* player1Name = new TextBillboard();
	//player1Name->setText("Player 1");
	//m_GameObjects[2] = player1Name;

	//TextBillboard* player2Name = new TextBillboard();
	//player2Name->setText("Player 2");
	//player2Name->setFaceCamera(false);
	//m_GameObjects[3] = player2Name;
	//
	//TextBillboard* justificationTest = new TextBillboard();
	//justificationTest->setText("Press r, t, y, f, g, h, v, b, n to justify the text");
	//m_GameObjects[4] = justificationTest;


	//fonts
	m_Font = new TextureFont("Content/Fonts/amble47.fnt");
	m_FontPapyrus = new TextureFont("Content/Fonts/papyrus.fnt");


	//setup the render target
	m_RenderTarget = new RenderTarget(Renderer::getInstance()->screenWidth(), Renderer::getInstance()->screenHeight(), GL_LINEAR, GL_LINEAR);

	//enable FPS render
	Renderer::getInstance()->showFPS(true);


	
}

GameMain::~GameMain()
{

	/*delete m_GameObjects[0];
	delete m_GameObjects[1];
	delete m_GameObjects[2];
	delete m_GameObjects[3];
	delete m_GameObjects[4];*/
	delete m_Font;
	delete m_TestTexture;
}

void GameMain::initialize()
{
	
	
}

void GameMain::update(GameTime gameTime)
{

	LightManager::getInstance()->update();

	//update game here	


	/*for(int i = 0; i < MAX_GAME_OBJECTS; i++)
	{
		if(m_GameObjects[i] != NULL)
		{
			m_GameObjects[i]->update(gameTime);
		}
	}*/

	/*Vector3 position;
	position = m_GameObjects[0]->getPosition();
	position.y += 3.0f;
	m_GameObjects[2]->setPosition(position);

	position = m_GameObjects[1]->getPosition();
	position.y += 3.0f;
	m_GameObjects[3]->setPosition(position);*/


	Matrix horseWorld;
	horseWorld.SetIdentity();	
	horseWorld.Rotate(gameTime.TotalTime * 10, 0, 1, 0);
	horseWorld.SetPosition(15, 0, 0);
	m_HorseModel->setWorld(horseWorld);	


	//increment the score
	if(glfwGetKey('P'))
	{
		m_Score++;
	}

	//enable/disable red light
	if(glfwGetKey('1') && m_LightButton1Pressed == false)
	{
		Light* light = LightManager::getInstance()->getLight(0);
		light->Enabled = !light->Enabled;
		m_LightButton1Pressed = true;
	}
	else if(!glfwGetKey('1') && m_LightButton1Pressed == true)
	{
		m_LightButton1Pressed = false;
	}

	//enable/disable blue light
	if(glfwGetKey('2') && m_LightButton2Pressed == false)
	{
		Light* light = LightManager::getInstance()->getLight(1);
		light->Enabled = !light->Enabled;
		m_LightButton2Pressed = true;
	}
	else if(!glfwGetKey('2') && m_LightButton2Pressed == true)
	{
		m_LightButton2Pressed = false;
	}

	//enable/disable point light
	if(glfwGetKey('3') && m_LightButton3Pressed == false)
	{
		Light* light = LightManager::getInstance()->getLight(2);
		light->Enabled = !light->Enabled;
		m_LightButton3Pressed = true;
	}
	else if(!glfwGetKey('3') && m_LightButton3Pressed == true)
	{
		m_LightButton3Pressed = false;
	}


	

	//enable/disable spot light
	if(glfwGetKey('4') && m_LightButton4Pressed == false)
	{
		Light* light = LightManager::getInstance()->getLight(3);
		light->Enabled = !light->Enabled;
		m_LightButton4Pressed = true;
	}
	else if(!glfwGetKey('4') && m_LightButton4Pressed == true)
	{
		m_LightButton4Pressed = false;
	}



	//move light forward
	if(glfwGetKey('W'))
	{
		m_PointLightWorld.TranslatePostRotation(0, 0, -2 * gameTime.ElapsedTime);
	}
	//move light backward
	if(glfwGetKey('S'))
	{
		m_PointLightWorld.TranslatePostRotation(0, 0, 2 * gameTime.ElapsedTime);
	}
	//move light left
	if(glfwGetKey('A'))
	{
		m_PointLightWorld.TranslatePostRotation(-2 * gameTime.ElapsedTime, 0, 0);
	}
	//move light right
	if(glfwGetKey('D'))
	{
		m_PointLightWorld.TranslatePostRotation(2 * gameTime.ElapsedTime, 0, 0);
	}
	LightManager::getInstance()->getLight(2)->Position = Vector3(m_PointLightWorld.m41, m_PointLightWorld.m42, m_PointLightWorld.m43);
	m_LightSphereModel->setWorld(m_PointLightWorld);


	//rotate barrel
	if(glfwGetKey('I'))
	{
		m_RedBarrelWorld.Rotate(20 * gameTime.ElapsedTime, 1, 0, 0);
	}
	if(glfwGetKey('K'))
	{
		m_RedBarrelWorld.Rotate(-20 * gameTime.ElapsedTime, 1, 0, 0);
	}
	if(glfwGetKey('J'))
	{
		m_RedBarrelWorld.Rotate(-20 * gameTime.ElapsedTime, 0, 1, 0);
	}
	if(glfwGetKey('L'))
	{
		m_RedBarrelWorld.Rotate(20 * gameTime.ElapsedTime, 0, 1, 0);
	}
	m_RedBarrelModel->setWorld(m_RedBarrelWorld);


	




	////justification controls
	//if(glfwGetKey('R'))
	//{
	//	((TextBillboard*)m_GameObjects[4])->setJustification(Justify_Left | Justify_Top);
	//}
	//if(glfwGetKey('T'))
	//{
	//	((TextBillboard*)m_GameObjects[4])->setJustification(Justify_CenterX | Justify_Top);
	//}
	//if(glfwGetKey('Y'))
	//{
	//	((TextBillboard*)m_GameObjects[4])->setJustification(Justify_Right | Justify_Top);
	//}
	//if(glfwGetKey('F'))
	//{
	//	((TextBillboard*)m_GameObjects[4])->setJustification(Justify_Left | Justify_CenterY);
	//}
	//if(glfwGetKey('G'))
	//{
	//	((TextBillboard*)m_GameObjects[4])->setJustification(Justify_CenterX | Justify_CenterY);
	//}
	//if(glfwGetKey('H'))
	//{
	//	((TextBillboard*)m_GameObjects[4])->setJustification(Justify_Right | Justify_CenterY);
	//}
	//if(glfwGetKey('V'))
	//{
	//	((TextBillboard*)m_GameObjects[4])->setJustification(Justify_Left | Justify_Bottom);
	//}
	//if(glfwGetKey('B'))
	//{
	//	((TextBillboard*)m_GameObjects[4])->setJustification(Justify_CenterX | Justify_Bottom);
	//}
	//if(glfwGetKey('N'))
	//{
	//	((TextBillboard*)m_GameObjects[4])->setJustification(Justify_Right | Justify_Bottom);
	//}

}

void GameMain::draw(GameTime gameTime)
{
	//enabled render target
	m_RenderTarget->bind();

	Renderer::getInstance()->begin();	

	//draw all drawables
	Renderer::getInstance()->draw(gameTime);

	Renderer::getInstance()->end();	


	//disable render target
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	

	//draw 2d stuff
	//draw full screen
	Renderer2D::getInstance()->drawTexture(m_RenderTarget->texture(), Vector4(0, Renderer::getInstance()->screenHeight(), Renderer::getInstance()->screenWidth(), Renderer::getInstance()->screenHeight()), Vector4(0, 0, 0, 0), Vector3(1, 1, 1), Vector2(0, 0), 0);

	//draw debug
	Renderer2D::getInstance()->drawTexture(m_RenderTarget->texture(), Vector4(0, Renderer::getInstance()->screenHeight(), 200, 100), Vector4(0, 0, 0, 0), Vector3(1, 1, 1), Vector2(0, 0), 0);
	Renderer2D::getInstance()->drawTexture(m_RenderTarget->depthTexture(), Vector4(200, Renderer::getInstance()->screenHeight(), 200, 100), Vector4(0, 0, 0, 0), Vector3(1, 1, 1), Vector2(0, 0), 0);

	//draw 2d
	//Renderer2D::getInstance()->drawTexture(m_TestTexture->textureID(), Vector4(200, Renderer::getInstance()->screenHeight() - 200, 400, 200), Vector4(0, 0, 0, 0), Vector3(1, 1, 1), Vector2(0, 0), 0);

	//draw UI
	UIManager::getInstance()->draw();

	//draw text to screen
	m_TotalTime = gameTime.TotalTime;

	char value[20];
	sprintf(value, "Time: %0.1f", m_TotalTime);
	Renderer::getInstance()->drawString(m_FontPapyrus, value, Vector3(Renderer::getInstance()->screenWidth() / 2, Renderer::getInstance()->screenHeight(), 0), Vector4(1, 1, 1, 1), 40.0f, Justify_CenterX | Justify_Top);
	
	sprintf(value, "Score: %i", m_Score);
	Renderer::getInstance()->drawString(m_FontPapyrus, value, Vector3(0, Renderer::getInstance()->screenHeight(), 0), Vector4(1, 1, 1, 1), 40.0f, Justify_Left | Justify_Top);

	
	
}