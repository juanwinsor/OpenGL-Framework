uniform mat4 u_WorldViewProj;
uniform vec2 u_MousePosition;

attribute vec4 a_Position;
attribute vec4 a_Color;
attribute vec2 a_UVCoord;


varying vec4 v_Color;
varying vec2 v_UVCoord;

void main()
{
    gl_Position = u_WorldViewProj * a_Position;
	v_UVCoord = a_UVCoord;

	v_Color = vec4(0.8, 0.8, 0.8, 0.2);

	vec2 mouse = normalize(u_MousePosition);

	//change alpha based on mouse input
	if(mouse.y > 0.2)
	{
		v_Color = vec4(0.8, 0.8, 0.8, mouse.y);
	}
	
	
}