uniform mat4 u_WorldViewProj;
uniform sampler2D u_Texture;
uniform vec3 u_Color;
uniform vec3 u_CameraPosition;

varying vec3 v_Position;
varying vec4 v_Color;
varying vec2 v_UVCoord;
varying vec3 v_Normal;

struct lightStruct
{
	int enabled;
	vec3 position;
	vec3 direction;
	vec4 diffuseColor;
	int type;
    vec4 ambientColor;
    vec4 specularColor;
	vec3 attenuation;
};

struct materialStruct
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float specularPower;
};

uniform lightStruct u_Light[8];
uniform materialStruct u_Material;


//functions
vec4 directionalLight(lightStruct light, vec4 textureColor)
{
	//ambient
	vec4 ambient = light.ambientColor * u_Material.ambient;

	//diffuse
	float diffuseAmount = max(dot(-light.direction, v_Normal), 0.0);
	vec4 diffuse = vec4((diffuseAmount * light.diffuseColor.rgb * u_Material.diffuse.rgb), 1.0);
	
	//specular
	vec3 eyeVector = normalize(u_CameraPosition - v_Position);
	vec3 halfwayVector = normalize(eyeVector + -light.direction);
	vec4 specular = pow(max(dot(halfwayVector, v_Normal), 0.0), u_Material.specularPower) * u_Material.specular;

	//final color
	vec4 color = (ambient + diffuse + specular) * textureColor; 
	return clamp(color, 0.0, 1.0); //saturate
}

vec4 pointLight(lightStruct light, vec4 textureColor)
{
	//ambient
	vec4 ambient = light.ambientColor * u_Material.ambient;

	//calculate light direction
	vec3 lightVector = light.position - v_Position;

	//diffuse
	float diffuseAmount = max(dot(lightVector, v_Normal), 0.0);
	vec4 diffuse = vec4((diffuseAmount * light.diffuseColor.rgb * u_Material.diffuse.rgb), 1.0);

	//specular
	vec3 eyeVector = normalize(u_CameraPosition - v_Position);
	vec3 halfwayVector = normalize(eyeVector + -light.direction);
	vec4 specular = pow(max(dot(halfwayVector, v_Normal), 0.0), u_Material.specularPower) * u_Material.specular;

	//falloff
	float dist = abs(distance(light.position, v_Position));
	float attenuation = light.attenuation.x + light.attenuation.y * dist + light.attenuation.z * dist * dist;

	//final color
	vec4 color = (ambient + diffuse + specular) * textureColor / attenuation; 
	return clamp(color, 0.0, 1.0); //saturate
}


vec4 spotLight(lightStruct light, vec4 textureColor)
{
	//ambient
	vec4 ambient = light.ambientColor * u_Material.ambient;

	//calculate light direction
	vec3 lightVector = light.position - v_Position;

	//diffuse
	float diffuseAmount = max(dot(lightVector, v_Normal), 0.0);
	vec4 diffuse = vec4((diffuseAmount * light.diffuseColor.rgb * u_Material.diffuse.rgb), 1.0);

	//specular
	vec3 eyeVector = normalize(u_CameraPosition - v_Position);
	vec3 halfwayVector = normalize(eyeVector + -light.direction);
	vec4 specular = pow(max(dot(halfwayVector, v_Normal), 0.0), u_Material.specularPower) * u_Material.specular;

	//falloff
	float dist = abs(distance(light.position, v_Position));
	float attenuation = light.attenuation.x + light.attenuation.y * dist + light.attenuation.z * dist * dist;

	//final color
	vec4 color = (ambient + diffuse + specular) * textureColor / attenuation; 

	//spot
	float spot = pow(max(dot(lightVector, normalize(light.direction)), 0), 1.2);
	color *= spot;

	return clamp(color, 0.0, 1.0); //saturate
}

void main()
{
	vec4 finalColor = vec4(0, 0, 0, 1);

	for(int i = 0; i < 8; i++)
	{
		if(u_Light[i].enabled)
		{
			//finalColor = vec4(1, 0, u_Light[i].type, 1); //u_Light[i].diffuseColor;
			if(u_Light[i].type == 0)
			{
				finalColor += directionalLight(u_Light[i], texture2D(u_Texture, v_UVCoord));
			}
			if(u_Light[i].type == 1)
			{
				finalColor += pointLight(u_Light[i], texture2D(u_Texture, v_UVCoord));
			}
			if(u_Light[i].type == 2)
			{
				finalColor += spotLight(u_Light[i], texture2D(u_Texture, v_UVCoord));
			}
		}
		
	}

	//return the total contribution of all the lights
	gl_FragColor = finalColor;
}

