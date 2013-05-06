#include "common.h"
#include "MouseShader.h"

MouseShader::MouseShader(char* vertexShader, char* fragmentShader) : Shader(vertexShader, fragmentShader)
{
	m_MousePosition.Set(0, 0);
}

void MouseShader::apply()
{
	Shader::apply();

	//set shader parameters
	GLint handle = programHandle();
	GLint uniformHandle = glGetUniformLocation(handle, "u_MousePosition");
	glUniform2f(uniformHandle, m_MousePosition.x, m_MousePosition.y);
}

void MouseShader::setMousePosition(float x, float y)
{
	m_MousePosition.Set(x, y);
}