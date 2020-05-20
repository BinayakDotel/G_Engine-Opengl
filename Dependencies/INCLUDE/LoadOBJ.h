#pragma once

//STD Libs
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<algorithm>

//OpenGL Math libs
#include<glm.hpp>
#include<vec3.hpp>
#include<vec4.hpp>
#include<mat4x4.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>

//Own libs
#include <Object2D.h>

static Object2D loadOBJ(const std::string& path) {
	Object2D obj;
	//Vertex portions
	std::vector<glm::vec3> vertex_positions;
	std::vector<glm::vec2> vertex_texcoords;
	std::vector<glm::vec3> vertex_normals;

	//Face vectors
	std::vector<unsigned int> vertex_position_indicies;
	std::vector<unsigned int> vertex_texcoord_indicies;
	std::vector<unsigned int> vertex_normal_indicies;

	//Vertex array
	//std::vector<Vertex> vertices;

	std::stringstream buffer;
	std::ifstream in_file(path.c_str());
	std::string line = "";
	std::string prefix = "";
	glm::vec3 temp_vec3;
	glm::vec2 temp_vec2;
	GLint temp_glint = 0;

	std::vector<glm::vec3> vertices;

	//File open error check
	if (!in_file.is_open()) {
		throw "ERROR::OBJLOADER::Could not open file.";
	}

	//Read one line at a time
	while (std::getline(in_file, line)) {
		//Get the prefix of the line
		buffer.clear();
		buffer.str(line);
		buffer >> prefix;

		if (prefix == "#") {

		}
		else if (prefix == "o") {

		}
		else if (prefix == "s") {

		}
		else if (prefix == "use_mtl") {

		}
		else if (prefix == "v") //Vertex position
		{
			buffer >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_positions.push_back(temp_vec3);
		}
		else if (prefix == "vt") {
			buffer >> temp_vec2.x >> temp_vec2.y;
			vertex_texcoords.push_back({ temp_vec2 });
		}
		else if (prefix == "vn") {
			buffer >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_normals.push_back({ temp_vec3 });
		}
		else if (prefix == "f") {
			int counter = 0;
			while (buffer >> temp_glint) {
				//Pushing indices into correct arrays
				if (counter == 0)
					obj.index.push_back(temp_glint);
				else if (counter == 1)
					vertex_texcoord_indicies.push_back(temp_glint);
				else if (counter == 2)
					vertex_normal_indicies.push_back(temp_glint);

				//Handling characters
				if (buffer.peek() == '/') {
					++counter;
					buffer.ignore(1, '/');
				}
				else if (buffer.peek() == ' ') {
					++counter;
					buffer.ignore(1, ' ');
				}

				//Reset the counter
				if (counter > 2)
					counter = 0;
			}
		}
		else {

		}
	}
	
	//Load in all indices
	for (size_t i = 0; i < obj.index.size(); ++i) {		
		obj.vertex.push_back(vertex_positions.at(obj.index.at(i) - 1));
		obj.texCoords.push_back(vertex_texcoords.at(vertex_texcoord_indicies[i] - 1));
	}
	
	//DEBUG
	//std::cout << "Nr of vertices: " << vertices.size() << "\n";

	//Loaded success
	std::cout << "OBJ file loaded!" << "\n";
	return obj;
}