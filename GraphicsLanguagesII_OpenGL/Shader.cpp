#include "common.h"
#include "Shader.h"
//#include <stdio.h>
//#include <assert.h>

Shader::Shader()
{

}

Shader::Shader(char* vertexShader, char* fragmentShader)
{
	m_TextureID = -1;
	m_VertexShaderSource = NULL;
	m_VertexShaderLength = 0;
	m_VertexShaderHandle = -1;

	m_FragmentShaderSource = NULL;
	m_FragmentShaderLength = 0;
	m_FragmentShaderHandle = -1;

	m_ProgramHandle = -1;

	m_VSPositionHandle = -1;
	m_VSColorHandle = -1;
	m_VSUVCoordinateHandle = -1;
	m_VSNormalHandle = -1;

	//load and compile the shaders
	loadShaderFiles(vertexShader, fragmentShader);
}

Shader::~Shader()
{
    glDetachShader(m_ProgramHandle, m_VertexShaderHandle);
    glDetachShader(m_ProgramHandle, m_FragmentShaderHandle);    
    glDeleteShader(m_VertexShaderHandle);
    glDeleteShader(m_FragmentShaderHandle);
    glDeleteProgram(m_ProgramHandle);
}

void Shader::loadShaderFiles(char* vertexShader, char* fragmentShader)
{
	//read in the shaders
	m_VertexShaderSource = Shader::readFile(vertexShader, &m_VertexShaderLength);
	m_FragmentShaderSource = Shader::readFile(fragmentShader, &m_FragmentShaderLength);	

	//compile shaders
	GLuint vsObject = glCreateShader(GL_VERTEX_SHADER);
	GLuint fsObject = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vsSource = m_VertexShaderSource;
	glShaderSource(vsObject, 1, &vsSource, &m_VertexShaderLength);
	const char* fsSource = m_FragmentShaderSource;
	glShaderSource(fsObject, 1, &fsSource, &m_FragmentShaderLength);

	glCompileShader(vsObject);
	glCompileShader(fsObject);

	bool vsCompiled = false;
	bool fsCompiled = false;
	GLint compiled;
	glGetShaderiv(vsObject, GL_COMPILE_STATUS, &compiled);
	if(compiled)
	{
		vsCompiled = true;
	}
	else
	{
		//check shader compiler errors
		GLint infoLen = 0;
		glGetShaderiv(vsObject, GL_INFO_LOG_LENGTH, &infoLen);
		if(infoLen)
        {
			char* buf = (char*)malloc(infoLen);
            if( buf )
            {
				glGetShaderInfoLog(vsObject, infoLen, NULL, buf);
				OutputDebugStringA(buf);
				int i = 0;
				//assert(false);
			}
		}

		glDeleteShader(vsObject);
	}

	glGetShaderiv(fsObject, GL_COMPILE_STATUS, &compiled);
	if(compiled)
	{
		fsCompiled = true;
	}
	else
	{

		//check shader compiler errors
		GLint infoLen = 0;
		glGetShaderiv(fsObject, GL_INFO_LOG_LENGTH, &infoLen);
		if(infoLen)
        {
			char* buf = (char*)malloc(infoLen);
            if( buf )
            {
				glGetShaderInfoLog(fsObject, infoLen, NULL, buf);
				OutputDebugStringA(buf);
				//assert(false);
				int i = 0;
			}
		}

		glDeleteShader(fsObject);
	}

	//if both shaders compiled create a shader program
	if(vsCompiled && fsCompiled)
	{
		m_VertexShaderHandle = vsObject;
		m_FragmentShaderHandle = fsObject;

		GLuint programID = glCreateProgram();

		glAttachShader(programID, vsObject);
		glAttachShader(programID, fsObject);

		glLinkProgram(programID);
		GLint linkStatus = GL_FALSE;
		//check if linking failed
		glGetProgramiv( programID, GL_LINK_STATUS, &linkStatus );
		if( linkStatus != GL_TRUE )
		{
			//clean up
			glDeleteProgram(programID);
			glDeleteShader(vsObject);
			glDeleteShader(fsObject);

			vsObject = 0;
			fsObject = 0;
		}


		//store the handle
		m_ProgramHandle = programID;
	}

	//store a handle to the uniforms
	m_WorldViewProjectionHandle =  glGetUniformLocation( m_ProgramHandle, "u_WorldViewProj" );
	GLint test = glGetUniformLocation( m_ProgramHandle, "u_TotalTime" );
	m_FSTextureHandle = glGetUniformLocation(m_ProgramHandle, "u_Texture");

	//store the handle to the position attribute
	m_VSColorHandle = glGetAttribLocation( m_ProgramHandle, "a_Color" );	
	m_VSPositionHandle = glGetAttribLocation( m_ProgramHandle, "a_Position" );	
	m_VSUVCoordinateHandle = glGetAttribLocation( m_ProgramHandle, "a_UVCoord" );
	m_VSNormalHandle = glGetAttribLocation(m_ProgramHandle, "a_Normal");
	
}

GLint Shader::vsPositionHandle()
{
	return m_VSPositionHandle;
}

GLint Shader::worldViewProjectionHandle()
{
	return m_WorldViewProjectionHandle;
}

GLint Shader::vsColorHandle()
{
	return m_VSColorHandle;
}

GLint Shader::vsNormalHandle()
{
	return m_VSNormalHandle;
}

GLint Shader::vsUVCoordinateHandle()
{
	return m_VSUVCoordinateHandle; 
}

char* Shader::readFile(char* filename, int* length)
{
	FILE* file;
	int fileLength = 0;
	

	//open file
	fopen_s(&file, filename, "rb");
	if(file)
	{
		//find the end of the file
		fseek(file, 0, SEEK_END);
		//get the length of the file
		long size = ftell(file);
		//go back to the beginning of the stream
		rewind(file);

		//read data into buffer
		char* fileBuffer = new char[size];
		fread(fileBuffer, size, 1, file);

		fileLength = size;

		//close the file
		fclose(file);

		*length = fileLength;

		return fileBuffer;
	}

	return NULL;
}

void Shader::apply()
{
	//load the shader onto the gpu
	glUseProgram(m_ProgramHandle);

	//apply texture
	if(m_TextureID > -1)
	{
		glActiveTexture( GL_TEXTURE0 );
		glBindTexture( GL_TEXTURE_2D, m_TextureID );
		//glUniform1i(m_TextureID , 0 /*the texture slot TEXTURE0*/);
		glUniform1i(m_FSTextureHandle , 0 /*the texture slot TEXTURE0*/);
	}
	

	//set any custom uniform values that have been set
	for(int i = 0; i < m_UniformValues.size(); i++)
	{
		//only set the value when the uniform handle is valid
		if(m_UniformValues[i].UniformHandle > -1)
		{
			switch(m_UniformValues[i].ValueType)
			{
			case 0: //integer			
				glUniform1i(m_UniformValues[i].UniformHandle, m_UniformValues[i].Value.IntegerValue);
				break;

			case 1: //float
				glUniform1f(m_UniformValues[i].UniformHandle, m_UniformValues[i].Value.FloatValue);
				break;

			case 2: //vector3
				glUniform3f(m_UniformValues[i].UniformHandle, m_UniformValues[i].Value.Vector3Value[0], m_UniformValues[i].Value.Vector3Value[1], m_UniformValues[i].Value.Vector3Value[2]);
				break;

			case 3: //vector2
				glUniform2f(m_UniformValues[i].UniformHandle, m_UniformValues[i].Value.Vector2Value[0], m_UniformValues[i].Value.Vector2Value[1]);
				break;

			case 4: //matrix
				glUniformMatrix4fv(m_UniformValues[i].UniformHandle, 1, false, (GLfloat*)&m_UniformValues[i].Value.MatrixValue[0]);
				break;

			case 5: //texture
				//apply texture
				if(m_UniformValues[i].Value.TextureValue.TextureID > -1)
				{
					//activate the appropriate texture slot
					switch(m_UniformValues[i].Value.TextureValue.TextureSlot)
					{
					case 0:
						glActiveTexture(GL_TEXTURE0);
						break;

					case 1:
						glActiveTexture(GL_TEXTURE1);
						break;

					case 2:
						glActiveTexture(GL_TEXTURE2);
						break;

					case 3:
						glActiveTexture(GL_TEXTURE3);
						break;
					}
					
					//bind the texture to the render target
					glBindTexture(m_UniformValues[i].Value.TextureValue.TextureType, m_UniformValues[i].Value.TextureValue.TextureID);
					//assign the texture slot to the uniform texture
					glUniform1i(m_FSTextureHandle, m_UniformValues[i].Value.TextureValue.TextureSlot /*the texture slot TEXTURE0*/);
				}
				break;

			case 6: //vector4
				glUniform4f(m_UniformValues[i].UniformHandle, m_UniformValues[i].Value.Vector4Value[0], m_UniformValues[i].Value.Vector4Value[1], m_UniformValues[i].Value.Vector4Value[2], m_UniformValues[i].Value.Vector4Value[3]);
				break;
			}
		}
	}
}

GLint Shader::programHandle()
{
	return m_ProgramHandle;
}

GLint Shader::fsTextureHandle()
{
	return m_FSTextureHandle;
}

void Shader::setUniform(char* uniformName, GLint value) //int
{
	//check if uniform name already exists
	bool found = false;
	int index = -1;
	for(int i = 0; i < m_UniformValues.size(); i++)
	{

		//int test = strcmp(m_UniformValues[i].UniformName,uniformName);

		if(strcmp(m_UniformValues[i].UniformName,uniformName) == 0)
		{
			//change the value of the one found
			m_UniformValues[i].Value.IntegerValue = value;

			found = true;
			index = i;
			break;
		}
	}

	//uniform hasn't been set yet, only do a handle lookup the first time it is added
	if(!found)
	{
		//create a new string to hold the name so it isn't a reference of the one passed in
		char* uName = new char[128];
		strcpy(uName, uniformName);

		//get uniform handle
		GLint uniformHandle = glGetUniformLocation(m_ProgramHandle, uniformName);
		//create a place to store the uniform name, handle and value
		UniformValueType uVal;
		uVal.IntegerValue = value;
		UniformValueStruct val(uName, uniformHandle, uVal, 0);
		//add it to the list
		m_UniformValues.push_back(val);
		
	}
	
}

void Shader::setUniform(char* uniformName, float value) //float
{
	//check if uniform name already exists
	bool found = false;
	int index = -1;
	for(int i = 0; i < m_UniformValues.size(); i++)
	{
		if(strcmp(m_UniformValues[i].UniformName,uniformName) == 0)
		{
			//change the value of the one found
			m_UniformValues[i].Value.FloatValue = value;

			found = true;
			index = i;
			break;
		}
	}
	
	//uniform hasn't been set yet, only do a handle lookup the first time it is added
	if(!found)
	{
		//create a new string to hold the name so it isn't a reference of the one passed in
		char* uName = new char[128];
		strcpy(uName, uniformName);

		//get uniform handle
		GLint uniformHandle = glGetUniformLocation(m_ProgramHandle, uniformName);
		//create a place to store the uniform name, handle and value
		UniformValueType uVal;
		uVal.FloatValue = value;
		UniformValueStruct val(uName, uniformHandle, uVal, 1);
		//add it to the list
		m_UniformValues.push_back(val);
	}
}

void Shader::setUniform(char* uniformName, Vector4 value)
{
	//check if uniform name already exists
	bool found = false;
	int index = -1;

	for(int i = 0; i < m_UniformValues.size(); i++)
	{
		if(strcmp(m_UniformValues[i].UniformName,uniformName) == 0)
		{
			//change the value of the one found
			m_UniformValues[i].Value.Vector4Value[0] = value.x;
			m_UniformValues[i].Value.Vector4Value[1] = value.y;
			m_UniformValues[i].Value.Vector4Value[2] = value.z;
			m_UniformValues[i].Value.Vector4Value[3] = value.w;

			found = true;
			index = i;
			break;
		}
	}

	//uniform hasn't been set yet, only do a handle lookup the first time it is added
	if(!found)
	{
		//create a new string to hold the name so it isn't a reference of the one passed in
		char* uName = new char[128];
		strcpy(uName, uniformName);

		//get uniform handle
		GLint uniformHandle = glGetUniformLocation(m_ProgramHandle, uniformName);
		//create a place to store the uniform name, handle and value
		UniformValueType uVal;
		uVal.Vector4Value[0] = value.x;
		uVal.Vector4Value[1] = value.y;
		uVal.Vector4Value[2] = value.z;
		uVal.Vector4Value[3] = value.w;
		UniformValueStruct val(uName, uniformHandle, uVal, 6);
		//add it to the list
		m_UniformValues.push_back(val);
	}

}

void Shader::setUniform(char* uniformName, Vector3 value) //vector3
{
	//check if uniform name already exists
	bool found = false;
	int index = -1;
	for(int i = 0; i < m_UniformValues.size(); i++)
	{
		if(strcmp(m_UniformValues[i].UniformName,uniformName) == 0)
		{
			//change the value of the one found
			m_UniformValues[i].Value.Vector3Value[0] = value.x;
			m_UniformValues[i].Value.Vector3Value[1] = value.y;
			m_UniformValues[i].Value.Vector3Value[2] = value.z;

			found = true;
			index = i;
			break;
		}
	}

	//uniform hasn't been set yet, only do a handle lookup the first time it is added
	if(!found)
	{
		//create a new string to hold the name so it isn't a reference of the one passed in
		char* uName = new char[128];
		strcpy(uName, uniformName);

		//get uniform handle
		GLint uniformHandle = glGetUniformLocation(m_ProgramHandle, uniformName);
		//create a place to store the uniform name, handle and value
		UniformValueType uVal;
		uVal.Vector3Value[0] = value.x;
		uVal.Vector3Value[1] = value.y;
		uVal.Vector3Value[2] = value.z;
		UniformValueStruct val(uName, uniformHandle, uVal, 2);
		//add it to the list
		m_UniformValues.push_back(val);
	}
}

void Shader::setUniform(char* uniformName, Vector2 value) //vector2
{
	//check if uniform name already exists
	bool found = false;
	int index = -1;
	for(int i = 0; i < m_UniformValues.size(); i++)
	{
		if(strcmp(m_UniformValues[i].UniformName,uniformName) == 0)
		{
			//change the value of the one found
			m_UniformValues[i].Value.Vector2Value[0] = value.x;
			m_UniformValues[i].Value.Vector2Value[1] = value.y;

			found = true;
			index = i;
			break;
		}
	}

	//uniform hasn't been set yet, only do a handle lookup the first time it is added
	if(!found)
	{
		//create a new string to hold the name so it isn't a reference of the one passed in
		char* uName = new char[128];
		strcpy(uName, uniformName);

		//get uniform handle
		GLint uniformHandle = glGetUniformLocation(m_ProgramHandle, uniformName);
		//create a place to store the uniform name, handle and value
		UniformValueType uVal;
		uVal.Vector2Value[0] = value.x;
		uVal.Vector2Value[1] = value.y;
		UniformValueStruct val(uName, uniformHandle, uVal, 3);
		//add it to the list
		m_UniformValues.push_back(val);
	}
}

void Shader::setUniform(char* uniformName, Matrix value) //matrix
{
	//check if uniform name already exists
	bool found = false;
	int index = -1;
	for(int i = 0; i < m_UniformValues.size(); i++)
	{
		if(strcmp(m_UniformValues[i].UniformName,uniformName) == 0)
		{
			//change the value of the one found
			m_UniformValues[i].Value.MatrixValue[0] = value.m11;
			m_UniformValues[i].Value.MatrixValue[1] = value.m12;
			m_UniformValues[i].Value.MatrixValue[2] = value.m13;
			m_UniformValues[i].Value.MatrixValue[3] = value.m14;
			m_UniformValues[i].Value.MatrixValue[4] = value.m21;
			m_UniformValues[i].Value.MatrixValue[5] = value.m22;
			m_UniformValues[i].Value.MatrixValue[6] = value.m23;
			m_UniformValues[i].Value.MatrixValue[7] = value.m24;
			m_UniformValues[i].Value.MatrixValue[8] = value.m31;
			m_UniformValues[i].Value.MatrixValue[9] = value.m32;
			m_UniformValues[i].Value.MatrixValue[10] = value.m33;
			m_UniformValues[i].Value.MatrixValue[11] = value.m34;
			m_UniformValues[i].Value.MatrixValue[12] = value.m41;
			m_UniformValues[i].Value.MatrixValue[13] = value.m42;
			m_UniformValues[i].Value.MatrixValue[14] = value.m43;
			m_UniformValues[i].Value.MatrixValue[15] = value.m44;

			found = true;
			index = i;
			break;
		}
	}

	//uniform hasn't been set yet, only do a handle lookup the first time it is added
	if(!found)
	{
		//create a new string to hold the name so it isn't a reference of the one passed in
		char* uName = new char[128];
		strcpy(uName, uniformName);

		//get uniform handle
		GLint uniformHandle = glGetUniformLocation(m_ProgramHandle, uniformName);
		//create a place to store the uniform name, handle and value
		UniformValueType uVal;
		uVal.MatrixValue[0] = value.m11;
		uVal.MatrixValue[1] = value.m12;
		uVal.MatrixValue[2] = value.m13;
		uVal.MatrixValue[3] = value.m14;
		uVal.MatrixValue[4] = value.m21;
		uVal.MatrixValue[5] = value.m22;
		uVal.MatrixValue[6] = value.m23;
		uVal.MatrixValue[7] = value.m24;
		uVal.MatrixValue[8] = value.m31;
		uVal.MatrixValue[9] = value.m32;
		uVal.MatrixValue[10] = value.m33;
		uVal.MatrixValue[11] = value.m34;
		uVal.MatrixValue[12] = value.m41;
		uVal.MatrixValue[13] = value.m42;
		uVal.MatrixValue[14] = value.m43;
		uVal.MatrixValue[15] = value.m44;
		UniformValueStruct val(uName, uniformHandle, uVal, 4);
		//add it to the list
		m_UniformValues.push_back(val);
	}
}

void Shader::setUniform(char* uniformName, GLint textureID, int textureSlot, GLenum textureType)
{
	//check if uniform name already exists
	bool found = false;
	int index = -1;
	for(int i = 0; i < m_UniformValues.size(); i++)
	{
		if(strcmp(m_UniformValues[i].UniformName,uniformName) == 0)
		{
			//change the value of the one found
			m_UniformValues[i].Value.TextureValue.TextureID = textureID;
			m_UniformValues[i].Value.TextureValue.TextureSlot = textureSlot;
			m_UniformValues[i].Value.TextureValue.TextureType = textureType;

			found = true;
			index = i;
			break;
		}
	}

	//uniform hasn't been set yet, only do a handle lookup the first time it is added
	if(!found)
	{
		//create a new string to hold the name so it isn't a reference of the one passed in
		char* uName = new char[128];
		strcpy(uName, uniformName);

		//get uniform handle
		GLint uniformHandle = glGetUniformLocation(m_ProgramHandle, uniformName);
		//create a place to store the uniform name, handle and value
		UniformValueType uVal;		
		uVal.TextureValue.TextureID = textureID;
		uVal.TextureValue.TextureSlot = textureSlot;
		uVal.TextureValue.TextureType = textureType;

		UniformValueStruct val(uName, uniformHandle, uVal, 5);
		//add it to the list
		m_UniformValues.push_back(val);
	}
}

void Shader::setTexture(GLint textureID)
{
	m_TextureID = textureID;
}

GLint Shader::textureID()
{
	return m_TextureID;
}