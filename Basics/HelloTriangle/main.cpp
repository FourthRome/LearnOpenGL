#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core\n\
layout(location = 0) in vec3 aPos;\n\
\n\
out vec4 vertexColor;\n\
\n\
void main()\n\
{\n\
	gl_Position = vec4(aPos, 1.0);\n\
	vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n\
}\0";

const char* fragmentShaderSource = "#version 330 core\n\
out vec4 FragColor;\n\
\n\
void main()\n\
{\n\
	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n\
}\0";

const char* fragmentShaderSource_2 = "#version 330 core\n\
in vec4 vertexColor;\n\
\n\
out vec4 FragColor;\n\
\n\
void main()\n\
{\n\
	//FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n\
	FragColor = vertexColor;\n\
}\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// Function to be called on window resize
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	// Function to catch ESC keypress
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {
	// Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create GLFW window
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL shaders", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Load GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Create a viewport within window
	//glViewport(0, 0, 800, 600);

	// Create vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Check if vertex shader compiled successfully
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return -1;
	}

	// Create fragment shader
	//unsigned int fragmentShader;
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);

	//// Check if fragment shader compiled successfully
	//glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	//if (!success) {
	//	glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
	//	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	//	return -1;
	//}

	// Create fragment shaders (task with two shaders)
	unsigned int fragmentShaders[2];
	const char* fragmentShaderSources[] = { fragmentShaderSource, fragmentShaderSource_2 };
	for (auto i = 0; i < 2; ++i) {
		fragmentShaders[i] = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaders[i], 1, &fragmentShaderSources[i], NULL);
		glCompileShader(fragmentShaders[i]);
	}

	//// Check if fragment shader compiled successfully
	//glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	//if (!success) {
	//	glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
	//	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	//	return -1;
	//}

	// Check if fragment shaders compiled successfully (task with two shaders)
	for (auto i = 0; i < 2; ++i) {
		glGetShaderiv(fragmentShaders[i], GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragmentShaders[i], sizeof(infoLog), NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
			return -1;
		}
	}

	//// Creating shader program
	//unsigned int shaderProgram;
	//shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);

	//// Check if shaders got linked correctly
	//glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	//if (!success) {
	//	glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
	//	std::cout << "ERROR::SHADER::PROGRAM::LINKAGE_FAILED\n" << infoLog << std::endl;
	//	return -1;
	//}

	// Creating shader programs (task with two shaders)
	unsigned int shaderPrograms[2];
	for (auto i = 0; i < 2; ++i) {
		shaderPrograms[i] = glCreateProgram();
		glAttachShader(shaderPrograms[i], vertexShader);
		glAttachShader(shaderPrograms[i], fragmentShaders[i]);
		glLinkProgram(shaderPrograms[i]);
	}

	// Check if shaders got linked correctly (task with two shaders)
	for (auto i = 0; i < 2; ++i) {
		glGetProgramiv(shaderPrograms[i], GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderPrograms[i], sizeof(infoLog), NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKAGE_FAILED\n" << infoLog << std::endl;
			return -1;
		}
	}

	//// Clean up shaders
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);

	// Clean up shaders (task with two shaders)
	glDeleteShader(vertexShader);
	for (auto i = 0; i < 2; ++i) {
		glDeleteShader(fragmentShaders[i]);
	}

	// Triangle's vertices
	/*float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};*/

	// Rectangle vertices
	/*float vertices[] = {
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};*/

	// Rectangle indices
	/*unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};*/

	// Triangles' vertices
	float vertices[] = {
		0.5f, 0.5f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.0f, 0.0f, 0.0f,
		-0.5f, 0.0f, 0.0f
	};


	// Create vertex array object
	//unsigned int VAO;
	//glGenVertexArrays(1, &VAO);
	//glBindVertexArray(VAO);

	// Create two VAOs (for task with two triangles):
	unsigned int VAOs[2];
	glGenVertexArrays(2, VAOs);

	// Create vertex buffer object for vertex shader
	//unsigned int VBO;
	//glGenBuffers(1, &VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Create two VBOs for vertex shader (task with 2 triangles)
	unsigned int VBOs[2];
	glGenBuffers(2, VBOs);

	// Binding buffers, filling them, setting interpretation (task with 2 triangles)
	for (auto i = 0; i < 2; ++i) {
		glBindVertexArray(VAOs[i]);
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) / 2, vertices + i * ((sizeof(vertices) / 2) / sizeof(float)), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)NULL);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);
	}

	// Create element buffer object
	/*unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// Interpretation for vertex data
	/*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) NULL);
	glEnableVertexAttribArray(0);*/

	// Enable wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Main loop
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//// Activate shader program
		//glUseProgram(shaderProgram);

		// Binding VAO
		//glBindVertexArray(VAO);

		// Drawing triangle
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		// Drawing rectangle
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Drawing triangles
		for (auto i = 0; i < 2; ++i) {
			// Activate shader program
			glUseProgram(shaderPrograms[i]);

			glBindVertexArray(VAOs[i]);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Exit the program
	glfwTerminate();
	return 0;
}