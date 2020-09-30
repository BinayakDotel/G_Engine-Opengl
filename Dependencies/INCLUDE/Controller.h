#pragma once
#include<GLFW/glfw3.h>
#include<print.h>
#include<LoadOBJ.h>

class Controller {
public:
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_O && action == GLFW_PRESS) {
			print("You pressed O");
		}
	}
};