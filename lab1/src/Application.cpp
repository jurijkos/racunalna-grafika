#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>

#include "Trajectory.h"
#include "ObjectModel.h"
#include "Face3D.h"
#include "Vertex3D.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 900;

glm::vec3 srediste;
Trajectory *putanja;
ObjectModel *objekt;

void render(void);
void setup();

int main(void)
{
	setup();
	GLFWwindow* window;
	std::cout << "jurij" << std::endl;
	
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "B Spline", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	
	glm::mat4 view = glm::lookAt(glm::vec3(0.5, 0.5, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	
	glMatrixMode(GL_MODELVIEW);
	glMultMatrixf(glm::value_ptr(view));
	glScalef(1.5f, 1.5f, 1.5f);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClearColor(0.12f, 0.6f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		// kod 
		render();
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate(); 
	return 0;
}




ObjectModel* readObj(std::string filePath, Trajectory put)
{
	glm::vec3 sumVector = glm::vec3(0, 0, 0);
	std::ifstream ifs(filePath);
	std::string tmp;
	std::vector<std::string> vrhoviStr;
	std::vector<std::string> poligoniStr;
	while (std::getline(ifs, tmp))
	{
		if (tmp[0] == 'f')
		{
			poligoniStr.push_back(tmp);
		}
		else if (tmp[0] == 'v')
		{
			vrhoviStr.push_back(tmp);
			float x, y, z;
			sscanf_s(tmp.c_str(), "v %f %f %f", &x, &y, &z);
			sumVector += glm::vec3(x, y, z);
		}
	}
	std::vector<Face3D> poligoni;
	int v1, v2, v3;
	float x, y, z;
	for (unsigned int i = 0; i < poligoniStr.size(); i++)
	{
		sscanf_s(poligoniStr[i].c_str(), "f %d %d %d", &v1, &v2, &v3);

		sscanf_s(vrhoviStr[v1 - 1].c_str(), "v %f %f %f", &x, &y, &z);
		Vertex3D* vrh1 = new Vertex3D(x, y, z);
		sscanf_s(vrhoviStr[v2 - 1].c_str(), "v %f %f %f", &x, &y, &z);
		Vertex3D* vrh2 = new Vertex3D(x, y, z);
		sscanf_s(vrhoviStr[v3 - 1].c_str(), "v %f %f %f", &x, &y, &z);
		Vertex3D* vrh3 = new Vertex3D(x, y, z);

		Face3D p = Face3D(vrh1, vrh2, vrh3);
		poligoni.push_back(p);
	}

	sumVector /= vrhoviStr.size();
	srediste = sumVector;
	ObjectModel* obj = new ObjectModel(glm::vec3(0, 0, 1), sumVector, poligoni);


	return obj;
}



float t = 0.0f;
int i = 1;


void setup()
{
	std::string filename2 = "putanja.txt";
	
	putanja = new Trajectory(filename2);

	std::string filename = "aircraft747.obj";
	objekt = readObj(filename, *putanja);


	// ugasi ako se koristi display()
	std::vector<Face3D> noviPoly;
	srediste = glm::vec3(0, 0, 0);
	for (unsigned int i = 0; i < objekt->faces.size(); i++)
	{
		glm::vec3 v1 = objekt->faces[i].vertex1->vertex;// *inverse(R);
		glm::vec3 v2 = objekt->faces[i].vertex2->vertex;// *inverse(R);
		glm::vec3 v3 = objekt->faces[i].vertex3->vertex;// * inverse(R);

		Vertex3D* vrh1 = new Vertex3D(v1.z, v1.y, v1.x);
		Vertex3D* vrh2 = new Vertex3D(v2.z, v2.y, v2.x);
		Vertex3D* vrh3 = new Vertex3D(v3.z, v3.y, v3.x);

		srediste += v1 + v2 + v3;

		Face3D p = Face3D(vrh1, vrh2, vrh3);
		noviPoly.push_back(p);
	}
	srediste /= float(3 * objekt->faces.size());
	objekt->setFaces(noviPoly);

}


void render(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	
	putanja->renderPath();

	
	glm::vec3 tangenta = normalize(putanja->izracunajDeriviraniP(t, i));
	glColor3f(0.0, 1.0, 0.0);
	glm::vec3 start = putanja->calculatePositon(t, i);
	glm::vec3 end = start + 10.0f * tangenta;
	glBegin(GL_LINES);
	glVertex3f(start.x, start.y, start.z);
	glVertex3f(end.x, end.y, end.z);
	glEnd();

	
	glm::vec3 normala = normalize(glm::cross(tangenta, putanja->izracunajDerivirani2P(t, i)));
	glColor3f(0.0, 0.0, 1.0);
	glm::vec3 startN = putanja->calculatePositon(t, i);
	glm::vec3 endN = start + 10.0f * normala;
	glBegin(GL_LINES);
	glVertex3f(startN.x, startN.y, startN.z);
	glVertex3f(endN.x, endN.y, endN.z);
	glEnd();

	
	glm::vec3 binormala = normalize(glm::cross(tangenta, normala));
	glColor3f(1.0, 0.0, 0.0);
	glm::vec3 startB = putanja->calculatePositon(t, i);
	glm::vec3 endB = start + 15.0f * binormala;
	glBegin(GL_LINES);
	glVertex3f(startB.x, startB.y, startB.z);
	glVertex3f(endB.x, endB.y, endB.z);
	glEnd();

	//rotacijska matrica R
	glm::mat3x3 R = glm::mat3x3(tangenta, normala, binormala);

	
	objekt->draw(R, srediste, putanja, t, i);
	

	t += 0.1;
	if (t >= 1.0f)
	{
		i++;
		t = 0.0f;
	}

	if (i >= putanja->R.size() - 2)
	{
		i = 1;
		t = 0.0f;
		
	}

	
}

