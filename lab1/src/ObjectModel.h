#pragma once

#include <vector>

#include "Face3D.h"
#include "Trajectory.h"

class ObjectModel {
public:
	std::vector<Face3D> faces;
	glm::vec3 startingRotation;
	glm::vec3 currentRotation;
	glm::vec3 startingPosition;
	glm::vec3 currentPosition;

	ObjectModel(glm::vec3 startingRotation, glm::vec3 startingPosition, std::vector<Face3D> faces) {
		this->startingRotation = startingRotation;
		this->startingPosition = startingPosition;

		this->currentPosition = currentPosition;
		this->currentRotation = currentRotation;

		this->faces = faces;
	}
	glm::vec3 calculateCurrentPosition(Trajectory trajectroy, int i, float t)
	{
		currentPosition = trajectroy.calculatePositon(t, i);
		return currentPosition;
	}

	void setFaces(std::vector<Face3D> faces)
	{
		this->faces = faces;
	}

	void draw(glm::mat3x3 R, glm::vec3 srediste, Trajectory *putanja, float t, int i) {
		glColor3f(0.8, 0.8, 0.8);
		glBegin(GL_TRIANGLES);
		for (unsigned int j = 0; j < this->faces.size(); j++)
		{


			glm::vec3 v1 = ((this->faces[j].vertex1->vertex - srediste)*inverse(R)) / 5.0f + (putanja->calculatePositon(t, i));
			glm::vec3 v2 = ((this->faces[j].vertex2->vertex - srediste)*inverse(R)) / 5.0f + (putanja->calculatePositon(t, i));
			glm::vec3 v3 = ((this->faces[j].vertex3->vertex - srediste)*inverse(R)) / 5.0f + (putanja->calculatePositon(t, i));

			glVertex3f(v1.x, v1.y, v1.z);
			glVertex3f(v2.x, v2.y, v2.z);
			glVertex3f(v3.x, v3.y, v3.z);
		}
		glEnd();
	}
};