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

###4. 

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
    
### 5 and 6 and 7 :)
I have problem in 5 (I get a black screan) , so I will add the code in hope not losing all the grades:
the fargment shader:

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
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light.specular * (spec * material.specular) * textureColor;
    	
    	vec3 result = ambient + diffuse + specular;
    	frag_color = vec4(result, 1.0);
    }



Renderer:

    void Renderer::Render(const std::shared_ptr<Scene>& scene) {
    	int cameraCount = scene->GetCameraCount();
    	if (cameraCount > 0)
    	{
    		int modelCount = scene->GetModelCount();
    		auto camera = scene->GetActiveCamera();
    		//const Camera&
    		for (int currentModelIndex = 0; currentModelIndex < modelCount; currentModelIndex++)
    		{
    			auto currentModel = scene->GetModel(currentModelIndex);
    			//std::shared_ptr<MeshModel> currentModel
    			// Activate the 'colorShader' program (vertex and fragment shaders)
    			colorShader.use();
    
    			// Set the uniform variables
    			colorShader.setUniform("model", currentModel.GetTransformation());
    			colorShader.setUniform("view", camera.GetViewTransformation());
    			colorShader.setUniform("projection", camera.GetProjectionTransformation());
    			colorShader.setUniform("material.textureMap", 0);
    
    			colorShader.setUniform("material.ambient", scene->GetAmbientColor());
    			colorShader.setUniform("material.diffuse", scene->GetDiffuseColor());
    			colorShader.setUniform("material.specular", scene->GetSpecularColor());
    			colorShader.setUniform("material.shininess", scene->GetPower());
    
    			colorShader.setUniform("Light.light", scene->GetColor());
    			colorShader.setUniform("Light.pos", scene->GetLightPosition());
    
    			// Set 'texture1' as the active texture at slot #0
    			texture1.bind(0);
    
    			// Drag our model's faces (triangles) in fill mode
    			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    			glBindVertexArray(currentModel.GetVAO());
    			glDrawArrays(GL_TRIANGLES, 0, currentModel.RetVerticesSize());
    			glBindVertexArray(0);
    
    			// Unset 'texture1' as the active texture at slot #0
    			texture1.unbind(0);
    
    			colorShader.setUniform("color", glm::vec3(0, 0, 0));
    
    			// Drag our model's faces (triangles) in line mode (wireframe)
    			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    			glBindVertexArray(currentModel.GetVAO());
    			glDrawArrays(GL_TRIANGLES, 0, currentModel.RetVerticesSize());
    			glBindVertexArray(0);
    		}
    	}
    }
    
### 8.
Again since I had a problem in 5, I will only write the code:

here we need to add in the vetex shader:
    //for toon shading
    out vec3 surface_normal; 
    
    void main()
    {
    	//...the same as before
    
    	surface_normal = vec3(model * vec4(normal, 0.0));
    }
In the fragment shader:

	///this part for toon\cel shading:
	vec3 uNormal = normilize( surface_normal);
	vec3 uVec = norm; 
	vec3 uLight = normilize(light.pos);
	float brightness = max(dot(uNormal, uLight), 0.0);
	float level = floor(brightness * levels);
	brightness = level / levels;
	frag_color = vec4( mesh_color * brihgtness * light.ambient, 1.0);
	
** sending the levels is thesame as the other section ( the same as we sent the colors for the light for example).

> Note: I tried to figure out where did the code went wrong while doing 2 to 5,  but I could not find the problem, so I just wrote the code hoping it is correct.

### *******************************************************
### 5. after fixing:

Few things was missing in the main (in main.cpp):
    int main(int argc, char** argv)
    {
    
    	if (!Setup(windowWidth, windowHeight, windowTitle))
    	{
    		std::cerr << "Setup failed" << std::endl;
    		return -1;
    	}
    
    	scene = std::make_shared<Scene>();
    	glm::vec3 eye = glm::vec3(0, 0, 10);
    	glm::vec3 at = glm::vec3(0, 0, 0);
    	glm::vec3 up = glm::vec3(0, 1, 0);
    	Camera camera = Camera(eye, at, up, GetAspectRatio());
    	scene->AddCamera(camera);
    
    	Renderer renderer;
    	renderer.LoadShaders();
    	renderer.LoadTextures();
    
    	while (!glfwWindowShouldClose(window))
    	{
    		// Poll and process events
    		glfwPollEvents();
    
    		// Imgui stuff
    		ImGui_ImplOpenGL3_NewFrame();
    		ImGui_ImplGlfw_NewFrame();
    		ImGui::NewFrame();
    		DrawImguiMenus();
    		ImGui::Render();
    		//HandleImguiInput();
    
    		// Clear the screen and depth buffer
    		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    		// Render scene
    		renderer.Render(scene);
    
    		// Imgui stuff
    		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    		// Swap front and back buffers
    		glfwSwapBuffers(window);
    	}
    
    	glfwTerminate();
    	return 0;
    }
    
vertex shader:
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

fragmant shader:
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
    
    	frag_color = vec4(255,0,0,1);
    }

Renderer:

    void Renderer::Render(const std::shared_ptr<Scene>& scene)
    {
    	int cameraCount = scene->GetCameraCount();
    	if (cameraCount > 0)
    	{
    		int modelCount = scene->GetModelCount();
    		Camera& camera = scene->GetActiveCamera();
    
    		for (int currentModelIndex = 0; currentModelIndex < modelCount; currentModelIndex++)
    		{
    			std::shared_ptr<MeshModel> currentModel = scene->GetModel(currentModelIndex);
    
    			// Activate the 'colorShader' program (vertex and fragment shaders)
    			colorShader.use();
    
    			// Set the uniform variables
    			colorShader.setUniform("model", currentModel->GetTransformation());
    			colorShader.setUniform("view", camera.GetViewTransformation());
    			colorShader.setUniform("projection", camera.GetProjectionTransformation());
    			colorShader.setUniform("material.textureMap", 0);
    
    			// Set 'texture1' as the active texture at slot #0
    			texture1.bind(0);
    
    			// Drag our model's faces (triangles) in fill mode
    			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    			glBindVertexArray(currentModel->GetVAO());
    			glDrawArrays(GL_TRIANGLES, 0, currentModel->GetModelVertices().size());
    			glBindVertexArray(0);
    
    			// Unset 'texture1' as the active texture at slot #0
    			texture1.unbind(0);
    
    			colorShader.setUniform("color", glm::vec3(0, 0, 0));
    
    			// Drag our model's faces (triangles) in line mode (wireframe)
    			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    			glBindVertexArray(currentModel->GetVAO());
    			glDrawArrays(GL_TRIANGLES, 0, currentModel->GetModelVertices().size());
    			glBindVertexArray(0);
    		}
    	}
    }

### 6.
fragment shader:

    #version 330 core
    
    struct Material
    {
    	sampler2D textureMap;
    	vec3 ambient;
    	vec3 diffuse;
    	vec3 specular;	
    
    //	vec3 color;
    
    	//for toon shading
    	//vec3 mesh_color;
    	//float levels; 
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
    
    // for toon shading
    //in vec3 surface_normal;
    
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

Renderer:

    void Renderer::Render(const std::shared_ptr<Scene>& scene)
    {
    	int cameraCount = scene->GetCameraCount();
    	if (cameraCount > 0)
    	{
    		int modelCount = scene->GetModelCount();
    		Camera& camera = scene->GetActiveCamera();
    
    		for (int currentModelIndex = 0; currentModelIndex < modelCount; currentModelIndex++)
    		{
    			std::shared_ptr<MeshModel> currentModel = scene->GetModel(currentModelIndex);
    
    			// Activate the 'colorShader' program (vertex and fragment shaders)
    			colorShader.use();
    
    			// Set the uniform variables
    			colorShader.setUniform("model", currentModel->GetTransformation());
    			colorShader.setUniform("view", camera.GetViewTransformation());
    			colorShader.setUniform("projection", camera.GetProjectionTransformation());
    			colorShader.setUniform("material.textureMap", 0);
    
    			colorShader.setUniform("light.ambient", scene->GetAmbientColor());
    			colorShader.setUniform("light.diffuse", scene->GetDiffuseColor());
    			colorShader.setUniform("light.specular", scene->GetSpecularColor());
    			colorShader.setUniform("light.shininess", scene->GetPower());
    			colorShader.setUniform("light.pos", scene->GetLightPosition());
    			//colorShader.setUniform("light.color", scene->GetColor());
    
    			colorShader.setUniform("material.ambient", currentModel->GetAmbientColor());
    			colorShader.setUniform("material.diffuse", currentModel->GetDiffuseColor());
    			colorShader.setUniform("material.specular", currentModel->GetSpecularColor());
    			//colorShader.setUniform("material.color", currentModel->GetColor());
    
    
    			// Set 'texture1' as the active texture at slot #0
    			texture1.bind(0);
    
    			// Drag our model's faces (triangles) in fill mode
    			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    			glBindVertexArray(currentModel->GetVAO());
    			glDrawArrays(GL_TRIANGLES, 0, currentModel->GetModelVertices().size());
    			glBindVertexArray(0);
    
    			// Unset 'texture1' as the active texture at slot #0
    			texture1.unbind(0);
    
    			//colorShader.setUniform("color", glm::vec3(0, 0, 0));
    
    			// Drag our model's faces (triangles) in line mode (wireframe)
    			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    			glBindVertexArray(currentModel->GetVAO());
    			glDrawArrays(GL_TRIANGLES, 0, currentModel->GetModelVertices().size());
    			glBindVertexArray(0);
    		}
    	}
    }
    
![6_1.png](Assignment3Report/Photos/6_1.png)

![6_2.png](Assignment3Report/Photos/6_2.png)

### 7.

![7.1.png](Assignment3Report/Photos/7.1.png)

![7.2.png]()

![7.3.png]()

![7.4.png]()


### 8.
In the vertex:

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
    }

In the fragment shader:

    #version 330 core
    
    struct Material
    {
    	sampler2D textureMap;
    	vec3 ambient;
    	vec3 diffuse;
    	vec3 specular;	
    
    	//for toon shading
    	vec3 mesh_color;
    	float levels; 
    };
    
    struct Light
    {
        vec3 pos;
        vec3 color;
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
    
    //for toon shading
    in vec3 surface_normal;
    
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
    
the levels:

    colorShader.setUniform("material.levels", 1.0f*currentModel->GetModelVertices().size());

![8.1.png]()

![8.2.png]()












    

	

    
