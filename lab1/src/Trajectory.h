#pragma once

#include <vector>
#include "Vertex3D.h"
#include <glm/mat4x4.hpp>

class Trajectory {
public:
	std::vector<Vertex3D> R;
	glm::mat4x4 B;
	glm::mat4x3 BDerivative;

	glm::vec3 position;
	std::vector<glm::vec3> pointsOnPath;

	Trajectory(std::string filePath) {
		//this->B = glm::mat4x4(-1, 3, -3, 1, 3, -6, 3, 0, -3, 0, 3, 0, 1, 4, 1, 0);
		this->B = glm::mat4x4(-1, 3, -3, 1, 3, -6, 0, 4, -3, 3, 3, 1, 1, 0, 0, 0);
		this->BDerivative = glm::mat4x3(-1, 2, -1, 3, -4, 0, -3, 2, 1, 1, 0, 0);
		std::ifstream ifs(filePath);
		std::string tmp;
		float x, y, z;
		std::vector<Vertex3D> vrhovi;
		while (std::getline(ifs, tmp))
		{
			sscanf_s(tmp.c_str(), "%f %f %f", &x, &y, &z);
			Vertex3D vrh = Vertex3D(x / 30.0f, y / 30.0f, z / 30.0f);
			vrhovi.push_back(vrh);
		}
		this->R = vrhovi;

		this->position = calculatePositon(0, 1);
		this->pointsOnPath = calculateAllPoints();
	}

	glm::vec3 calculatePositon(float t, int i) {
		glm::vec4 vect = glm::vec4(t * t * t, t * t, t, 1);
		glm::mat3x4 vecR = glm::mat3x4(R[i - 1].vertex.x, R[i].vertex.x, R[i + 1].vertex.x, R[i + 2].vertex.x,
			R[i - 1].vertex.y, R[i].vertex.y, R[i + 1].vertex.y, R[i + 2].vertex.y,
			R[i - 1].vertex.z, R[i].vertex.z, R[i + 1].vertex.z, R[i + 2].vertex.z);
		glm::vec3 vec = vect * 0.16666f * B * vecR;
		return vec;
	}

	glm::vec3 izracunajDeriviraniP(float t, int i)
	{
		glm::vec3 vecT = glm::vec3(t*t, t, 1);
		glm::mat4x4 vecR = glm::mat3x4(R[i - 1].vertex.x, R[i].vertex.x, R[i + 1].vertex.x, R[i + 2].vertex.x,
			R[i - 1].vertex.y, R[i].vertex.y, R[i + 1].vertex.y, R[i + 2].vertex.y,
			R[i - 1].vertex.z, R[i].vertex.z, R[i + 1].vertex.z, R[i + 2].vertex.z);

		return vecT * 0.5f * BDerivative * vecR;
	}
	glm::vec3 izracunajDerivirani2P(float t, int i)
	{
		glm::vec4 vecDerv = glm::vec4(1 - t, 3 * t - 2, 1 - 3 * t, t);
		glm::mat4x4 vecR = glm::mat3x4(R[i - 1].vertex.x, R[i].vertex.x, R[i + 1].vertex.x, R[i + 2].vertex.x,
			R[i - 1].vertex.y, R[i].vertex.y, R[i + 1].vertex.y, R[i + 2].vertex.y,
			R[i - 1].vertex.z, R[i].vertex.z, R[i + 1].vertex.z, R[i + 2].vertex.z);

		return vecDerv * vecR;
	}
	std::vector<glm::vec3> calculateAllPoints() {
		std::vector<glm::vec3> path;
		for (int i = 1; i < R.size() - 2; i++) {
			for (float t = 0.f; t < 1.f; t += 0.11f) {
				glm::vec3 temp = calculatePositon(t, i);
				path.push_back(temp);
			}
		}
		return path;
	}

	void renderPath()
	{
		glBegin(GL_POINTS);
		for (unsigned int i = 0; i < this->pointsOnPath.size(); i++)
		{
			glVertex3f(this->pointsOnPath[i].x, this->pointsOnPath[i].y, this->pointsOnPath[i].z);
		}
		glEnd();

	}
};