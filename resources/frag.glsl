#version 440

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D diffuseTex;
	sampler2D specularTex;
};

in vec3 fragPos;
in vec4 fragColor;
in vec2 fragPosTex;
in vec3 fragNormals;

out vec4 finalColor;

uniform Material material;
uniform vec3 lightPos0;
uniform vec3 cameraPos;
uniform sampler2D texture2;

vec3 getDiffuseLight(Material material, vec3 fragPos, vec3 fragNormals, vec3 lightPos0)
{
	vec3 fragToLightDir = normalize(lightPos0 - fragPos);
	vec3 normal = normalize(fragNormals);
	float diffuseIntensity = max(dot(fragToLightDir, normal), 0.0);
	vec3 diffuseFinal = material.diffuse * diffuseIntensity;
	return diffuseFinal;
}

vec3 getSpecularLight(Material material, vec3 lightPos0, vec3 fragPos, vec3 fragNormals, vec3 cameraPos)
{
	vec3 fragToLightDir = normalize(lightPos0 - fragPos);
	vec3 fragToViewDir = normalize(cameraPos - fragPos);
	vec3 reflectDir = reflect(-fragToLightDir, normalize(fragNormals));
	float specularIntensity = pow(max(dot(fragToViewDir, reflectDir), 0.0), 60);
	vec3 specularFinal = material.specular * specularIntensity; 
	return specularFinal;
}

void main()
{
	vec3 ambientLight = material.ambient;
	vec3 diffuseLight = getDiffuseLight(material, fragPos, fragNormals, lightPos0);
	vec3 specularFinal = getSpecularLight(material, lightPos0, fragPos, fragNormals, cameraPos);

	finalColor = texture(texture2, fragPosTex) * fragColor * 
				 vec4(ambientLight + diffuseLight + specularFinal, 1.0f);
	//finalColor = fragColor;  
}
