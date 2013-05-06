uniform mat4 u_WorldViewProj;
attribute vec4 a_Position;
attribute vec4 a_Color;
attribute vec2 a_UVCoord;


varying vec4 v_Color;
varying vec2 v_UVCoord;

void main()
{
    gl_Position = u_WorldViewProj * a_Position;
	v_Color = a_Color;
	v_UVCoord = a_UVCoord;
}