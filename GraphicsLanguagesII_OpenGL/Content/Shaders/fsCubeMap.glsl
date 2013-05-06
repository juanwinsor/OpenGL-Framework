uniform sampler2D u_Texture;
uniform samplerCube u_CubeMap;
uniform vec3 u_Color;

varying vec4 v_Color;
varying vec2 v_UVCoord;
varying vec3 v_Reflection;
void main()
{
	
    //gl_FragColor = vec4(1, 1, 1, 1) * v_Color * texture2D(u_TexColor, v_UVCoord); // * v_Color;
	//gl_FragColor = vec4(1, 1, 1, 1); //texture2D(u_Texture, v_UVCoord) * v_Color; //* vec4(u_Color, 1);
	//gl_FragColor = v_Color;

	gl_FragColor = textureCube(u_CubeMap, v_Reflection);
}