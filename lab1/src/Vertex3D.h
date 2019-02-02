#include <glm/vec3.hpp>
#pragma once

class Vertex3D {
public:
	glm::vec3 vertex;
	Vertex3D(float x, float y, float z) {
		vertex.x = x;
		vertex.y = y;
		vertex.z = z;
	}
};