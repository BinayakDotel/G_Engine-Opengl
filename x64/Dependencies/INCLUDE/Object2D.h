#pragma once
#include <vector>
#include <glm.hpp>

struct Object2D {
	std::vector<glm::vec3> vertex;
	std::vector<unsigned int> index;
	std::vector<glm::vec2> texCoords;
};