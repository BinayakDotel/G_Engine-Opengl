#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include "gtc/matrix_transform.hpp"
#include"gtx/transform.hpp"
#include <vec3.hpp>
#include <print.h>
#include <VertexArray.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <VertexBufferLayout.h>
#include <Shader.h>
#include <Renderer.h>
#include <Texture.h>
#include <Error.h>
#include <glm.hpp>
#include <Error.h>
#include <Vertex.h>
#include <LoadOBJ.h>
#include <PrespCamera.h>

#define WIDTH 1240
#define HEIGHT 800

static unsigned int numberofQuads = 0;
static glm::vec4 colCoord={ 1.0f, 1.0f, 1.0f, 1.0f };
static std::vector<glm::vec3> vertexCoord;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
		print("clicking");
}

static glm::vec4 determineColor(char color[6]) {
	if (strcmp(color, "red") == 0) {
		colCoord={ 0.9f, 0.2f, 0.2f, 1.0f };
	}
	if (strcmp(color, "blue") == 0) {
		colCoord={ 0.2f, 0.2f, 0.9f, 1.0f };
	}
	if (strcmp(color, "green") == 0) {
		colCoord={ 0.2f, 0.9f, 0.2f, 1.0f };
	}
	return colCoord;
}

static std::vector<Vertex> createObject(const std::string load, glm::vec3 pos, float id, char color[6]) {
	LoadOBJ obj(load);
	vertexCoord = obj.readObject();

	determineColor(color);

	glm::vec3 temp;
	int size = vertexCoord.size();

	for (int i = 0; i < size; i++) {
		if (i == 2 || i == 6 || i == 10) {
			temp= vertexCoord[i];
			vertexCoord[i] = vertexCoord[i + 1];
			vertexCoord[i + 1] = temp;
		}
	}
	std::vector<Vertex> vertex;

	for (int i=0; i < size; i++) {
		vertex.push_back({ vertexCoord[i], colCoord, {0.0f, 1.0f}, id });
	}

	numberofQuads += 1;
	return { vertex };
}

int main() {

	if (!glfwInit()) {
		print("Failed to initialize" + glfwInit());
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	// Open a window and create its OpenGL context
	GLFWwindow* window; // (In the accompanying source code, this variable is global for simplicity)
	window = glfwCreateWindow(WIDTH, HEIGHT, "Binayak", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
	glfwSwapInterval(10);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glfwSetKeyCallback(window, key_callback);

	std::string vertexShader =
		"#version 330 core\n"
		"\n"
		"layout (location = 0) in vec4 position;\n"
		"layout (location = 1) in vec4 i_Color;\n"
		"layout (location = 2) in vec2 i_texCoords;\n"
		"layout (location = 3) in float i_Index;\n"
		"out vec2 o_texCoords;\n"
		"out vec4 o_Color;\n"
		"out float o_Index;\n"
		"uniform mat4 MVP;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	o_Color= i_Color;\n"
		"   gl_Position= MVP * position;\n"
		"	o_texCoords= i_texCoords;\n"
		"	o_Index= i_Index;\n"
		"}\n";

	std::string fragmentShader =
		"#version 330 core\n"
		"\n"
		"layout (location = 0) out vec4 color;\n"
		"in vec4 o_Color;\n"
		"in vec2 o_texCoords;\n"
		"in float o_Index;\n"
		"uniform sampler2D u_Texture;\n"
		"uniform vec4 light;\n"
		"\n"
		"void main()\n"
		"{\n"
		"   color= texture(u_Texture, o_texCoords) * o_Color;\n"
		"	color= vec4(o_Color * light);\n"
		"}\n";
	
	std::string lightFragmentShader=
		"#version 330 core\n"
		"\n"
		"layout (location = 0) out vec4 lightColor;\n"
		"in vec4 o_Color;\n"
		"uniform vec4 light;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	lightColor= vec4(1.0f);\n"
		"}\n"; 

	unsigned int maxQuads = 100;
	unsigned int maxVertices = 4 * maxQuads;
	const unsigned int maxIndices = 6 * maxVertices;
	int offset = 0;
	unsigned int indices[6 * 4 * 100];

	double xpos=0.0, ypos=0.0;

	VertexBuffer vb(nullptr, sizeof(Vertex) * 1000);

	for (unsigned int i = 0; i < maxIndices; i+=6) {
		indices[i + 0] = 0 + offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;

		indices[i + 3] = 2 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = 0 + offset;

		offset += 4;
	}

	IndexBuffer ib(indices, maxIndices);
	ib.bindIndex();
	VertexBufferLayout layout;
	layout.push<float>(3);
	layout.push<float>(4);
	layout.push<float>(2);
	layout.push<float>(1);
	VertexArray va;

	Shader shader(vertexShader, fragmentShader);
	shader.bindShader();
	
	Texture texture("images/branch.jpg");
	texture.bindTexture();
	shader.setUniform1i("u_Texture", 0);

	glm::vec3 pos = { 0.0f, 0.0f, 3.0f };
	float aspect= float(WIDTH) / float(HEIGHT);
	float movespeed= 0.1f;
	PrespCamera camera(pos, 75.0f, aspect, 0.1f, 100.0f);
	glm::vec3 up= camera.getUp();
	glm::vec3 forward= camera.getForward();

	shader.setUniformMat4f("MVP", camera.getModelViewMatrix());
	glm::vec3 q1pos ={ -1.0f, 0.0f, 1.5f };
	glm::vec3 q2pos = { 0.0f, 0.0f, 1.1f };
	char col[3][6];
	strcpy_s(col[0], "red");
	strcpy_s(col[1], "blue");

	Renderer render;

	do {
		render.clearScreen();
		GLCALL(glClearColor(0.1f, 0.1f, 0.3f, 1.0f));
		GLCALL(glEnable(GL_DEPTH_TEST));
		GLCALL(glDepthFunc(GL_ALWAYS));

		glfwGetCursorPos(window, &xpos, &ypos);
        numberofQuads = 0;
		//auto q1 = createQuad("objects/circle.obj", q1pos, 0.0f, col[0]);
		std::vector<Vertex> q1= createObject("objects/circle.obj", q1pos, 0.0f, col[0]);
		int size = q1.size();

		Vertex vertices[100];

		memcpy(vertices, q1.data(), q1.size() * sizeof(Vertex));
		q1.erase(q1.begin(), q1.end());

		vb.bindVertex(vertices, sizeof(vertices));
		ib.bindIndex();
		va.addBuffer(vb, layout);
		shader.bindShader();
		texture.bindTexture();
		shader.setUniform1i("u_Texture", 0);
		shader.setUniformMat4f("MVP", camera.getModelViewMatrix());
		shader.setUniform4f("light", 1.0f, 0.0f, 0.0f, 1.0f);

		render.Draw(va, ib, shader);

		if (glfwGetKey(window, GLFW_KEY_UP)) {
			print("Up");
			pos.y += movespeed;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN)){
			print("Down");
			pos.y -= movespeed;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
			print("Right");
			pos.x += movespeed;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT)) {
			print("Left");
			pos.x -= movespeed;
		}
		if (glfwGetKey(window, GLFW_KEY_W)) {
	        q2pos.y += movespeed;
        }
        if (glfwGetKey(window, GLFW_KEY_S)) {
			q2pos.y -= movespeed;
		}
		if (glfwGetKey(window, GLFW_KEY_A)) {
			q2pos.x -= movespeed;
		}
		if (glfwGetKey(window, GLFW_KEY_D)) {
			q2pos.x += movespeed;
        }
		if (glfwGetKey(window, GLFW_KEY_U)) {
			q2pos.z-=movespeed;
		}
		if (glfwGetKey(window, GLFW_KEY_Z)) {
			q2pos.z+=movespeed;
		}
		if (glfwGetKey(window, GLFW_KEY_1)) {
			print(glfwGetKey(window, GLFW_KEY_1));
			if (glfwGetKey(window, GLFW_KEY_R)) {
				strcpy_s(col[0], "red");
			}
			if (glfwGetKey(window, GLFW_KEY_G)) {
				strcpy_s(col[0], "green");
			}
			if (glfwGetKey(window, GLFW_KEY_B)) {
				strcpy_s(col[0], "blue");
			}
		}
		if (glfwGetKey(window, GLFW_KEY_2)) {
			print(glfwGetKey(window, GLFW_KEY_2));
			if (glfwGetKey(window, GLFW_KEY_R)) {
				strcpy_s(col[1], "red");
			}
			if (glfwGetKey(window, GLFW_KEY_G)) {
				strcpy_s(col[1], "green");
			}
			if (glfwGetKey(window, GLFW_KEY_B)) {
				strcpy_s(col[1], "blue");
			}
		}
		camera.setPosition(pos);
		camera.moveUp(up);
		camera.moveForward(forward);
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
}