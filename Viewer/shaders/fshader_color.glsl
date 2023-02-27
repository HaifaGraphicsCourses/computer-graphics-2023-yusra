#version 330 core

struct Material
{
	sampler2D textureMap;
	// You can add more fields here...
	// Such as:
	//		1. diffuse/specular relections constants
	//		2. specular alpha constant
	//		3. Anything else you find relevant
	
	/*vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;*/
};

// We set this field's properties from the C++ code
uniform Material material;

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

	frag_color = vec4(orig_fragPos,1);

	// ambient
	//vec3 ambient = lightColor * material.ambient;
	// diffuse
	//vec3 norm = normalize(Normal);
	//vec3 lightDir = normalize(lightPos - FragPos);
	//float diff = max(dot(norm, lightDir), 0.0);
	//vec3 diffuse = lightColor * (diff * material.diffuse);
	// specular
	//vec3 viewDir = normalize(viewPos - FragPos);
	//vec3 reflectDir = reflect(-lightDir, norm);
	//float spec = pow(max(dot(viewDir, reflectDir), 0.0),
	//material.shininess);
	//vec3 specular = lightColor * (spec * material.specular);
	//vec3 result = ambient + diffuse + specular;
	//FragColor = vec4(result, 1.0);*/
}

















//#version 150

//in  vec2 texCoord;
//out vec4 fColor;

//uniform sampler2D texture;

//void main() 
//{ 
//   fColor = textureLod( texture, texCoord, 0 );
//} 

