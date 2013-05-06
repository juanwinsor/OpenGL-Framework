uniform mat4 u_WorldViewProj;
//vertex position
attribute vec4 a_Position;

void main()
{	
    gl_Position = u_WorldViewProj * a_Position;
}