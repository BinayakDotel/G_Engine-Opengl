#include <GL/glew.h>
#include <GLFW/glfw3.h> //For handling window and keyboard
#include<glm.hpp>
#include "gtc/matrix_transform.hpp"
#include"gtx/transform.hpp"
#include "print.h"
#include<iostream>
#include<stdlib.h>
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Texture.h"

/*int main() {
	//initializing glfw
	if (!glfwInit()) {
		print("Failed to initialize GLFW" + glfwInit());
		return -1;
	}

	//Creating Window
	GLFWwindow* window;
	//width, height, "Name"
	window = glfwCreateWindow(800, 600, "LearnOpengl", NULL, NULL);

	//Checking If window is initialized or not?
	if (window == NULL) {
		print("Failed to initialize window");
		glfwTerminate();
		return -1;
	}

	//Creating Window Context
	glfwMakeContextCurrent(window);

	//Initialize GLEW
	glewExperimental = true;

	if (glewInit() != GLEW_OK) {
		print("GLEW is not initialized");
		return -1;
	}
	glfwSwapInterval(1);

	std::string vertexShader =
		"#version 330 core\n"
		"\n"
		"layout (location = 0) in vec4 position;\n"
		"layout (location = 1) in vec4 i_Color;\n"
		"layout (location = 2) in vec2 texCoords;\n"
		"uniform mat4 MVP;\n"
		"out vec2 v_texCoords;\n"
		"out vec4 o_Color;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	o_Color= i_Color;\n"
		"   gl_Position= MVP * position;\n"
		"	v_texCoords= texCoords;\n"
		"}\n";

	std::string fragmentShader =
		"#version 330 core\n"
		"\n"
		"layout (location = 0) out vec4 color;\n"
		"uniform sampler2D u_texture;\n"
		"in vec4 o_Color;\n"
		"in vec2 v_texCoords;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	vec4 texColor= texture(u_texture, v_texCoords);\n"
		"   color= texColor * o_Color;\n"
		"}\n";

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//glm::vec4 myVector;

	float change = 0.05f;

	float positions[] = {
		// positions          // colors					// texture coords
		 2.0f, 1.0f, 0.0f,	  0.9f, 0.5f, 0.1f, 1.0f,   1.0f, 1.0f,   // top right
		 2.0f, 0.0f, 0.0f,    0.2f, 0.5f, 0.9f, 1.0f,   1.0f, 0.0f,   // bottom right
		 0.3f, 0.0f, 0.0f,    0.2f, 0.5f, 0.9f, 1.0f,   0.0f, 0.0f,   // bottom left
		 0.3f, 1.0f, 0.0f,    0.8f, 0.4f, 0.2f, 1.0f,   0.0f, 1.0f,    // top left

		 -0.3f, 1.0f, 0.0f,   0.9f, 0.9f, 0.9f, 1.0f,   1.0f, 1.0f,   // top right
		 -0.3f, 0.0f, 0.0f,   0.9f, 0.9f, 0.9f, 1.0f,   1.0f, 0.0f,   // bottom right
		 -2.0f, 0.0f, 0.0f,   0.9f, 0.9f, 0.9f, 1.0f,   0.0f, 0.0f,   // bottom left
		 -2.0f, 1.0f, 0.0f,   0.9f, 0.9f, 0.9f, 1.0f,   0.0f, 1.0f,    // top left
	};
	unsigned int indices[] = {
		0,1,2,
		2,3,0,

		4,5,6,
		6,7,4
	};

	VertexBuffer vertex_buffer(positions, sizeof(positions));
	IndexBuffer index_buffer(indices, 12);
	VertexBufferLayout vertex_layout;
	vertex_layout.push<float>(3);

	//For Texture
	vertex_layout.push<float>(4);
	vertex_layout.push<float>(2);
	VertexArray vertex_array;
	vertex_array.addBuffer(vertex_buffer, vertex_layout);

	float x = 2.0f, y = 1.5f, z = 1.0f;
	glm::mat4 proj = glm::ortho(-2.0f, x, -1.5f, y, -1.0f, z);
	glm::mat4 translateMat = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, 1.0f));
	glm::vec3 myRotationAxis(1.0f, 0.0f, 0.0f);
	glm::mat4 rotateMat = glm::rotate(45.0f, myRotationAxis);
	glm::mat4 view = translateMat * scaleMat * rotateMat;
	glm::mat4 mvp = proj * view;

	Shader shader(vertexShader, fragmentShader);
	Shader shader1(vertexShader, fragmentShader);

	shader.bindShader();
	//shader.setUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 0.5f);
	shader.setUniformMat4f("MVP", mvp);

	Texture texture("texture.jpg");
	texture.bindTexture();
	shader.setUniform1i("u_texture", 0);

	Renderer render;

	do {
		//Clear the screen
		render.clearScreen();

		//draw Triangle
		vertex_array.addBuffer(vertex_buffer, vertex_layout);

		// Draw the triangle !
		render.Draw(vertex_array, index_buffer, shader);

		glDisableVertexAttribArray(0);

		if (glfwGetKey(window, GLFW_KEY_1)) {
			translateMat = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 0, 0));
		}
		if (glfwGetKey(window, GLFW_KEY_2)) {
			translateMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0, 0));
		}
		if (glfwGetKey(window, GLFW_KEY_3)) {
			scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f));
		}
		if (glfwGetKey(window, GLFW_KEY_4)) {
			scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
		}
		if (glfwGetKey(window, GLFW_KEY_5)) {
			rotateMat = glm::rotate(-45.0f, glm::vec3(2.0f, 2.0f, 2.0f));
		}
		if (glfwGetKey(window, GLFW_KEY_6)) {
			rotateMat = glm::rotate(-45.0f, glm::vec3(2.0f, 2.0f, 2.0f));
		}
		shader.bindShader();
		//shader.setUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
		texture.bindTexture();
		shader.setUniform1i("u_texture", 0);
		view = translateMat * scaleMat * rotateMat;
		mvp = proj * view;
		shader.setUniformMat4f("MVP", mvp);

		//swap Buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
}
*/