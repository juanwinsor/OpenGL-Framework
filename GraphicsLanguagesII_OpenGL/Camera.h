#ifndef __CAMERA_H
#define __CAMERA_H




class Camera
{
public:
	Camera();
	Camera(int screenWidth, int screenHeight);
	~Camera();

	Matrix worldViewProjection(Matrix world);
	Matrix view();
	Matrix projection();

	Vector3 getPosition();
	
private:
	Matrix m_Projection;
	Matrix m_View;

	int m_ScreenHeight;
	int m_ScreenWidth;
};

#endif