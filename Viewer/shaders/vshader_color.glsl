#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

// The model/view/projection matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// These outputs will be available in the fragment shader as inputs
out vec3 orig_fragPos;
out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTexCoords;

//for toon shading
out vec3 surface_normal;

void main()
{
	// Apply the model transformation to the 'position' and 'normal' properties of the vertex,
	// so the interpolated values of these properties will be available for usi n the fragment shader
	orig_fragPos = vec3(vec4(pos, 1.0f));
	fragPos = vec3(view * model * vec4(pos, 1.0f));
	fragNormal = mat3(transpose(inverse(view * model))) * normal;

	// Pass the vertex texture coordinates property as it is. Its interpolated value
	// will be avilable for us in the fragment shader
	fragTexCoords = texCoords;

	// This is an internal OpenGL variable, we must set a value to this variable
	gl_Position = projection * view *  model * vec4(pos, 1.0f);

	surface_normal = vec3(model * vec4(normal, 1.0));

	float pi = 3.141592654;
	fragTexCoords = vec2(fragPos);
	float theta = (atan(fragPos.y, 1.5*fragPos.x) + pi*0.5)/pi ; 
	fragTexCoords = vec2(theta, -(-fragPos.z+0.5));
	float u = 0.5 + atan(fragPos.x, fragPos.z) / (2 * pi);
	float v = 0.5 + asin(fragPos.y / 3 ) / pi ; 
	fragTexCoords = vec2(u,v);
}



