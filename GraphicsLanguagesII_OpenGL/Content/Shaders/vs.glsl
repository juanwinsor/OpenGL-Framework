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
    gl_Position = u_WorldViewProj * a_Position;
	v_Color = a_Color;
	v_UVCoord = a_UVCoord;
}