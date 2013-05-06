uniform sampler2D u_Texture;
uniform vec3 u_Color;
varying vec4 v_Color;
varying vec2 v_UVCoord;

void main()
{
	
    //gl_FragColor = vec4(1, 1, 1, 1) * v_Color * texture2D(u_TexColor, v_UVCoord); // * v_Color;
	gl_FragColor = texture2D(u_Texture, v_UVCoord) * v_Color;
	//gl_FragColor = vec4(1, 1, 1, 1);
}