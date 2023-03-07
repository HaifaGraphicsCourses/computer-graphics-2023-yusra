# Assignment3
## Yusra Rayyan - 212896534  
### 1.

first we create unique identifier for the texture and for a vertex array object (VAO). the nwe buknd and create buffer. we put the vertices of the texture on GLfloat vtc[] and the coordinates in GLfloat tex[]. after that we store the  vertices and the coordinates. and then, we loads and compiles a sheder. the rest setup the program and tells the shader where to to look for the vertex position data, and the data dimensions and the same for texture coordinates. In the end we tell shader to use GL_TEXTURE0 as the texture id.

### 2.

we add to .h:

    struct Vertex
    {
        glm::vec3 position;
    	glm::vec3 normal;
    	glm::vec2 textureCoords;
    };
    private:
    std::vector<glm::vec3> textureCoords;
	std::vector<Vertex> modelVertices;
    GLuint vbo;
	GLuint vao;
	GLuint ebo;
	public:
	GLuint GetVAO() const;
	void setupMesh();
we add in .cpp:

    void MeshModel::setupMesh()
    {
    	glGenVertexArrays(1, &vao);
    	glGenBuffers(1, &vbo);
    
    	glBindVertexArray(vao);
    	glBindBuffer(GL_ARRAY_BUFFER, vbo);
    	glBufferData(GL_ARRAY_BUFFER, modelVertices.size() * sizeof(Vertex), &modelVertices[0], GL_STATIC_DRAW);
    
    	// Vertex Positions
    	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    	glEnableVertexAttribArray(0);
    
    	// Normals attribute
    	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
    	glEnableVertexAttribArray(1);
    
    	// Vertex Texture Coords
    	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
    	glEnableVertexAttribArray(2);
    
    	// unbind to make sure other code does not change it somewhere else
    	glBindVertexArray(0);
    }


    modelVertices.reserve(3 * faces.size());
	for (int i = 0; i < faces.size(); i++)
	{
		Face currentFace = faces.at(i);
		for (int j = 0; j < 3; j++)
		{
			int vertexIndex = currentFace.GetVertexIndex(j) - 1;

			Vertex vertex;
			vertex.position = vertices[vertexIndex];
			vertex.normal = normals[vertexIndex];

			if (textureCoords.size() > 0)
			{
				int textureCoordsIndex = currentFace.GetTextureIndex(j) - 1;
				vertex.textureCoords = textureCoords[textureCoordsIndex];
			}

			modelVertices.push_back(vertex);
		}
	}

### 3.

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
    
    void main()
    {
    	// Apply the model transformation to the 'position' and 'normal' properties of the vertex,
    	// so the interpolated values of these properties will be available for usi n the fragment shader
    	orig_fragPos = vec3(vec4(pos, 1.0f));
    	fragPos = vec3(model * vec4(pos, 1.0f));
    	fragNormal = mat3(model) * normal;
    
    	// Pass the vertex texture coordinates property as it is. Its interpolated value
    	// will be avilable for us in the fragment shader
    	fragTexCoords = texCoords;
    
    	// This is an internal OpenGL variable, we must set a value to this variable
    	gl_Position = projection * view *  model * vec4(pos, 1.0f);
    }

### 4.

    #version 330 core
    struct Material
    {
    	sampler2D textureMap;
    	// You can add more fields here...
    	// Such as:
    	//		1. diffuse/specular relections constants
    	//		2. specular alpha constant
    	//		3. Anything else you find relevant
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
    }
    

### 5.

In the render we set the values in the shaders:

    colorShader.setUniform("model", currentModel->GetTransformation());
    colorShader.setUniform("view", camera.GetViewTransformation());
    colorShader.setUniform("projection", camera.GetProjectionTransformation());
    colorShader.setUniform("material.textureMap", 0);

here we set the polygon in fill mode ( so the triangles will be filled with the color), then we bind the VAO of the current model and draw the model, in the end we unbind the VAO.
   
    // Drag our model's faces (triangles) in fill mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBindVertexArray(currentModel->GetVAO());
    glDrawArrays(GL_TRIANGLES, 0, currentModel->GetModelVertices().size());
    glBindVertexArray(0);
 
fragmant shader:

    frag_color = vec4(255,0,0,1);
  
 we color the model in red (255,0,0).
 
 
results:
![5_1.png](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-yusra/blob/73000f1c62f3e24a0fdfcd52c47d6a5a1c1c57cf/Assignment3Report/Photos/5_1.png)


### 6.
Phong shading:

we set more values in the render:

    colorShader.setUniform("light.ambient", scene->GetAmbientColor());	
	colorShader.setUniform("light.diffuse", scene->GetDiffuseColor());
	colorShader.setUniform("light.specular", scene->GetSpecularColor());
	colorShader.setUniform("light.shininess", scene->GetPower());
	colorShader.setUniform("light.pos", scene->GetLightPosition());
	colorShader.setUniform("material.ambient", currentModel->GetAmbientColor());
	colorShader.setUniform("material.diffuse", currentModel->GetDiffuseColor());
	colorShader.setUniform("material.specular", currentModel->GetSpecularColor());

the code similar to assignment 2b: 

the relevant part:

	// ambient
    	vec3 ambient = light.ambient * material.ambient;
    	
    	// diffuse
    	vec3 norm = normalize(fragNormal);
    	vec3 lightDir = normalize(light.pos - fragPos);
    	float diff = dot(norm, lightDir);
    	if(diff < 0.0) 
    		diff = 0.0;
    	vec3 diffuse = light.diffuse * (diff * material.diffuse);
    	
    	// specular
    	vec3 viewDir = normalize(-fragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), light.shininess);
        vec3 specular = light.specular * (spec * material.specular);
    	
    	vec3 result = ambient + diffuse + specular;
    	frag_color = vec4(result, 1.0);
    	

full fragment shader:

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
    	//vec3 textureColor = vec3(texture(material.textureMap, fragTexCoords));
    
    	// ambient
    	vec3 ambient = light.ambient * material.ambient;
    	
    	// diffuse
    	vec3 norm = normalize(fragNormal);
    	vec3 lightDir = normalize(light.pos - fragPos);
    	float diff = dot(norm, lightDir);
    	if(diff < 0.0) 
    		diff = 0.0;
    	vec3 diffuse = light.diffuse * (diff * material.diffuse);
    	
    	// specular
    	vec3 viewDir = normalize(-fragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), light.shininess);
        vec3 specular = light.specular * (spec * material.specular);
    	
    	vec3 result = ambient + diffuse + specular;
    	frag_color = vec4(result, 1.0);
    
    }


    
    
![6_1.png](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-yusra/blob/c4e3af695293540975c51f3a6d052bea51e7ddf2/Assignment3Report/Photos/6_1.png)

![6_2.png](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-yusra/blob/44d54329c7cfe9ade94c77f00d71ca4dac6ca3db/Assignment3Report/Photos/6_2.png)

### 7.

** canonical project : cylinder.

Here we need the Texture2D file,  We call the function laodTexture2D() in the main.cpp 
I used the crate in the refrence file.

afte adding the picture and crate file to debug and release, need to chabge in the fragment shader:

    vec3 textureColor = vec3(texture(material.textureMap, fragTexCoords));
    frag_color = vec4(textureColor, 1.0);
 
in render:

    void Renderer::LoadTextures()
    {
    	if (!texture1.loadTexture("bin\\Debug\\crate.jpg", true))
    	{
    		texture1.loadTexture("bin\\Release\\crate.jpg", true);
    	}
    }

![7.1.png](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-yusra/blob/44d54329c7cfe9ade94c77f00d71ca4dac6ca3db/Assignment3Report/Photos/7.1.png)

![7.2.png](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-yusra/blob/44d54329c7cfe9ade94c77f00d71ca4dac6ca3db/Assignment3Report/Photos/7.2.png)

![7.3.png](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-yusra/blob/44d54329c7cfe9ade94c77f00d71ca4dac6ca3db/Assignment3Report/Photos/7.3.png)

![7.4.png](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-yusra/blob/44d54329c7cfe9ade94c77f00d71ca4dac6ca3db/Assignment3Report/Photos/7.4.png)


### 8.
Toon shading:

In the vertex we added:

    //for toon shading
    out vec3 surface_normal;
    
    void main()
    {
    	...
    	surface_normal = vec3(model * vec4(normal, 1.0));
    }

In the fragment shader we added:

resutl is the model color.
    
    //for toon shading
    in vec3 surface_normal;

    void main()
    {
        ...
    	///this part for toon\cel shading:
    	vec3 uNormal = normalize( surface_normal);
    	vec3 uLight = normalize(light.pos);
    	float brightness = max(dot(uNormal, uLight), 1.0);
    	float levels = material.levels;
    	vec3 color = material.mesh_color;
    	float intensity = brightness * levels;
    	intensity = floor(intensity) / levels;
    	vec3 toon_shading = result* intensity;
    	frag_color = vec4(toon_shading, 1.0);
    }
    
the levels we set in the render:

    colorShader.setUniform("material.levels", 1.0f*currentModel->GetModelVertices().size());


![8.1.png](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-yusra/blob/44d54329c7cfe9ade94c77f00d71ca4dac6ca3db/Assignment3Report/Photos/8.1.png)

![8.2.png](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-yusra/blob/44d54329c7cfe9ade94c77f00d71ca4dac6ca3db/Assignment3Report/Photos/8.2.png)

![8.3.png](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-yusra/blob/44d54329c7cfe9ade94c77f00d71ca4dac6ca3db/Assignment3Report/Photos/8.3.png)











    

	

    
