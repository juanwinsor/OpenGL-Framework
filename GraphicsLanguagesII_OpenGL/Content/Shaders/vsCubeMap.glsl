uniform mat4 u_WorldViewProj;
uniform mat4 u_WorldMatrix;
uniform vec3 u_CameraPosition;

attribute vec4 a_Position;
attribute vec4 a_Color;
attribute vec2 a_UVCoord;

attribute vec3 a_Normal;

varying vec4 v_Color;
varying vec2 v_UVCoord;
varying vec3 v_Reflection;

void main()
{
    gl_Position = u_WorldViewProj * a_Position;
	v_Color = a_Color;
	v_UVCoord = a_UVCoord;

	vec3 view = u_CameraPosition - (u_WorldMatrix * a_Position);
	v_Reflection = reflect(view, a_Normal);
}