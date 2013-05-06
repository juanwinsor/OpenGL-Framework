#ifndef __SHADER_H
#define __SHADER_H


#include <vector>

using namespace std;

struct UniformTexture
{
	int TextureID;
	int TextureSlot;
	GLenum TextureType;
};

union UniformValueType
{
	int IntegerValue;
	float FloatValue;	
	float Vector3Value[3];
	float Vector2Value[2];
	float MatrixValue[16];
	UniformTexture TextureValue;
	float Vector4Value[4];
};

struct UniformValueStruct
{
	char* UniformName;
	int UniformHandle;	
	UniformValueType Value;
	int ValueType; //holds a value determining which member in the union it should use //0 - integer, 1 - float, 2 - vector3, 3 - vector2, 4 - matrix

	UniformValueStruct(char* uniformName, int uniformHandle, UniformValueType value, int valueType):UniformName(uniformName), UniformHandle(uniformHandle), Value(value), ValueType(valueType){}
};


class Shader
{
public:
	Shader();
	Shader(char* vertexShader, char* fragmentShader);
	~Shader();

	virtual void apply();

	void setUniform(char* uniformName, GLint value); //int
	void setUniform(char* uniformName, float value); //float
	void setUniform(char* uniformName, Vector4 value); //vector4
	void setUniform(char* uniformName, Vector3 value); //vector3
	void setUniform(char* uniformName, Vector2 value); //vector2
	void setUniform(char* uniformName, Matrix value); //Matrix
	void setUniform(char* uniformName, GLint textureID, int textureSlot, GLenum textureType); //texture
	void setTexture(GLint textureID);
	

	GLint programHandle();

	GLint worldViewProjectionHandle();
	GLint vsPositionHandle();
	GLint vsColorHandle();
	GLint vsUVCoordinateHandle();
	GLint fsTextureHandle();
	GLint vsNormalHandle();

	GLint textureID();

protected:	
	char* m_VertexShaderSource;
	int m_VertexShaderLength;
	GLuint m_VertexShaderHandle;

	char* m_FragmentShaderSource;
	int m_FragmentShaderLength;
	GLuint m_FragmentShaderHandle;

	GLuint m_ProgramHandle;


	void loadShaderFiles(char* vertexShader, char* fragmentShader);
	char* readFile(char* filename, int* length);
	
	
	GLint m_WorldViewProjectionHandle;

	GLint m_VSPositionHandle;
	GLint m_VSColorHandle;
	GLint m_VSUVCoordinateHandle;
	GLint m_FSTextureHandle;
	GLint m_VSNormalHandle;

	GLint m_TextureID;

	//uniform values
	vector<UniformValueStruct> m_UniformValues;
};

#endif