#pragma once

#ifndef MESH_H


#include<glm/gtc/matrix_transform.hpp>

#include <string>

using namespace std;

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	string type;
};
#endif  MESH_H