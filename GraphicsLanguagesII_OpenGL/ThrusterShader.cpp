#include "common.h"
#include "ThrusterShader.h"

ThrusterShader::ThrusterShader(char* vertexShader, char* fragmentShader) : Shader(vertexShader, fragmentShader)
{
	m_TotalTime = 0;
}
	

void ThrusterShader::apply()
{
	//call initial apply
	Shader::apply();

	//set shader parameters
	GLint handle = programHandle();
	GLint uniformHandle = glGetUniformLocation(handle, "u_TotalTime");
	glUniform1f(uniformHandle, m_TotalTime);

}

void ThrusterShader::setTime(double time)
{
	m_TotalTime = time;
}