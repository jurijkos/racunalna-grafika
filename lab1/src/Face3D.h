#pragma once
#include "Vertex3D.h"

class Face3D {
public:
	Vertex3D *vertex1;
	Vertex3D *vertex2;
	Vertex3D *vertex3;

	Face3D(Vertex3D *vertex1, Vertex3D *vertex2, Vertex3D *vertex3) {
		this->vertex1 = vertex1;
		this->vertex2 = vertex2;
		this->vertex3 = vertex3;
	}
};