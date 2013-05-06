#ifndef __MOUSESHADER_H
#define __MOUSESHADER_H

#include "Shader.h"


class MouseShader : public Shader
{
public:
	MouseShader(char* vertexShader, char* fragmentShader);

	void apply();

	void setMousePosition(float x, float y);
protected:
	Vector2 m_MousePosition;
};

#endif