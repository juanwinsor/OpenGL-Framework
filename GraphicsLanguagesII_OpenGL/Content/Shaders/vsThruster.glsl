uniform mat4 u_WorldViewProj;
uniform float u_TotalTime;

attribute vec4 a_Position;
attribute vec4 a_Color;
attribute vec2 a_UVCoord;


varying vec4 v_Color;
varying vec2 v_UVCoord;

void main()
{
    gl_Position = u_WorldViewProj * a_Position;
	v_UVCoord = a_UVCoord;

	//flicker between red and orange
	float result = sin(u_TotalTime * 50);
	if(result < 0)
	{
		//red
		v_Color = vec4(1.0, 0, 0, 1);
	}
	else
	{
		//orange
		v_Color = vec4(1.0, 0.5, 0.2, 1);
	}

	
}