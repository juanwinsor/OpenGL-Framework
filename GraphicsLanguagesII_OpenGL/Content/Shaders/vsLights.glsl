uniform mat4 u_WorldViewProj;
uniform mat4 u_Projection;
uniform mat4 u_World;
uniform mat4 u_View;
uniform vec3 u_CameraPosition;

attribute vec4 a_Position;
attribute vec4 a_Color;
attribute vec2 a_UVCoord;
attribute vec3 a_Normal;

varying vec3 v_Position;
varying vec4 v_Color;
varying vec2 v_UVCoord;
varying vec3 v_Normal;

void main()
{    
	//gl_Position = u_WorldViewProj * a_Position;
	mat4 worldView =  u_View * u_World;
	gl_Position = (u_Projection * worldView) * a_Position;

	v_Color = a_Color; // * u_Light.diffuseColor;
	v_UVCoord = a_UVCoord;
	v_Normal = mat3(u_World) * normalize(a_Normal);
	v_Position = u_World * a_Position;
}


//get handle to struct member
//glGetUniformLocation(handle, "u_Light.diffuseColor");

//get handle to array
//glGetUniformLocation(handle, "u_LightPos[0]");

//get handle to array of structs
//glGetUniformLocation(handle, "u_Lights[0].diffuseColor");
//structs and elements of structs get optimized out so hardcoded indexes may not be in order