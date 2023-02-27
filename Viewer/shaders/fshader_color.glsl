#version 330 core

struct Material
{
	sampler2D textureMap;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;	
};

struct Light
{
    vec3 pos;
   // vec3 color;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

// We set this field's properties from the C++ code
uniform Material material;
uniform Light light;

// Inputs from vertex shader (after interpolation was applied)
in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoords;

in vec3 orig_fragPos;

// The final color of the fragment (pixel)
out vec4 frag_color;

void main()
{
	// Sample the texture-map at the UV coordinates given by 'fragTexCoords'
	vec3 textureColor = vec3(texture(material.textureMap, fragTexCoords));
	//frag_color = vec4(orig_fragPos,1);

	// ambient
	vec3 ambient = light.ambient * material.ambient * textureColor;
	
	// diffuse
	vec3 norm = normalize(fragNormal);
	vec3 lightDir = normalize(light.pos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * (diff * material.diffuse) * textureColor;
	
	// specular
	vec3 viewDir = normalize(-fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), light.shininess);
    vec3 specular = light.specular * (spec * material.specular) * textureColor;
	
	vec3 result = ambient + diffuse + specular;
	frag_color = vec4(result, 1.0);
}




