#include "common.h"
#include "Camera.h"

Camera::Camera()
{

}

Camera::Camera(int screenWidth, int screenHeight)
{
	m_ScreenWidth = screenWidth;
	m_ScreenHeight = screenHeight;

	//initialize projection matrix
	float ratio = (float)m_ScreenWidth/m_ScreenHeight;
	m_Projection.SetPerspective(45, ratio, 1.0f, 1000 );

	//initialize view matrix
	m_View.SetIdentity();
	//m_View.SetLookAtRH(Vector3(0.0f, 100.0f, 1.0f), Vector3(0,1,0), Vector3(0,0,0));	
	//m_View.SetPosition(Vector3(0, 10, 0));
	//m_View.SetLookAtRH(Vector3(0.0f, 10.0f, 10.0f), Vector3(0,1,0), Vector3(0,0,0));	
	m_View.SetLookAtRH(Vector3(0.0f, 30.0f, 30.0f), Vector3(0,1,0), Vector3(0,0,0));	
}


Camera::~Camera()
{

}

Matrix Camera::worldViewProjection(Matrix world)
{
	Matrix worldViewProjection;
	Matrix viewProjection;

	viewProjection = m_View;
	viewProjection.Multiply(&m_Projection);
	worldViewProjection = world;	
	worldViewProjection.Multiply(&viewProjection);

	return worldViewProjection;
	
}

Matrix Camera::view()
{
	return m_View;
}

Matrix Camera::projection()
{
	return m_Projection;
}

Vector3 Camera::getPosition()
{
	return Vector3(0.0f, 100.0f, 1.0f);
}