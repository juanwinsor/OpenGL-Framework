#ifndef __THRUSTERSHADER_H
#define __THRUSTERSHADER_H

#include "Shader.h"

class ThrusterShader : public Shader
{
public:
	ThrusterShader(char* vertexShader, char* fragmentShader);

	void apply();

	void setTime(double time);
protected:
	double m_TotalTime;
};

#endif