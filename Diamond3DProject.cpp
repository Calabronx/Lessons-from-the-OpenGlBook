#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <shader.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 900;
const unsigned int SCR_HEIGHT = 800;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Openg GL Diamond 3D", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	Shader shader("diamond.vs", "diamond.fs");
	float vertices[] = {
		// first Pyramid	
		
			    //vertices			     // color
				-0.5f, -0.5f, -0.5f,	 1.0f, 0.0f, 0.0f, // frente 
				 0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 0.0f,// ROJO	
				 0.0f,  0.5f, 0.0f,		 1.0f, 1.0f, 1.0f,

				-0.5, -0.5f, 0.5f,		 0.0f, 1.0f, 0.0f,// atras
				 0.5f,-0.5f, 0.5f,		 0.0f, 1.0f, 0.0f,// VERDE
				 0.0f, 0.5f, 0.0f,		 1.0f, 1.0f, 1.0f,

				-0.5f,-0.5f, -0.5f,      0.0f, 0.0f, 1.0f,
				-0.5f,-0.5f,  0.5f,      0.0f, 0.0f, 1.0f,
				 0.0f, 0.5f,  0.0f,      0.0f, 0.0f, 1.0f,

				 0.5f, -0.5f,-0.5f,      1.0f, 1.0f, 0.0f,
				 0.5f, -0.5f, 0.5f,      1.0f, 1.0f, 0.0f,
				 0.0f,  0.5f, 0.0f,      1.0f, 1.0f, 0.0f,

			 // second Pyramid

				 //vertices			     // color
				 -0.5f, -0.5f, -0.5f,    0.5f, 0.0f, 1.0f,
				  0.5f, -0.5f, -0.5f,	 0.5f, 0.0f, 1.0f,
				  0.0f, -1.5f,  0.0f,    0.5f, 0.0f, 1.0f,

				 -0.5f, -0.5f,  0.5f,	 0.0f, 1.0f, 1.0f,
				  0.5f, -0.5f,  0.5f,	 0.0f, 1.0f, 1.0f,
				  0.0f, -1.5f,  0.0f,    0.0f, 1.0f, 1.0f,

				 -0.5f, -0.5f, -0.5f,    0.5f, 0.0f, 0.5f,
				 -0.5f, -0.5f, 0.5f,     0.5f, 0.0f, 0.5f,
				  0.0f, -1.5f, 0.0f,     0.5f, 0.0f, 0.5f,

				  0.5f, -0.5f, -0.5f,    1.0f, 0.5f, 0.0f,
				  0.5f, -0.5f,  0.5f,    1.0f, 0.5f, 0.0f,
				  0.0f, -1.5f,  0.0f,	 1.0f, 0.5f, 0.0f
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//glClearColor(0.2f, 0.3f, 0.3f, 7.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw our first triangle
		shader.use();

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.5f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(glm::radians(60.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		shader.setMat4(projection, "projection");
		shader.setMat4(model, "model");
		shader.setMat4(view, "view");
		shader.setMat4(projection, "projection");

		/*float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shader.ID, "pyramidColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/

		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 36);
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shader.ID);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	/*if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		float greenValue = sin(glfwGetTime()) / 2.0f + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shader.ID, "pyramidColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}