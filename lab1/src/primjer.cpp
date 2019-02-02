//#include <iostream>
//#include <vector>
//#include <GLFW/glfw3.h>
//#include <fstream>
//#include <sstream>
//
//std::vector<std::vector<std::string> > read_from_obj_file(std::string &s);
//std::vector<std::string> split(const std::string &s, char delim);
//std::vector<std::vector<double> > vrati_vrhove(std::vector<std::vector<std::string> > elementi);
//std::vector<std::vector<int> > vrati_trokute(std::vector<std::vector<std::string> > elementi);
//
//
//class Vertex3D {
//private:
//	double x;
//	double y;
//	double z;
//	Vertex3D(int x, int y, int z) {
//		this->x = x;
//		this->y = y;
//		this->z = z;
//	}
//public:
//	Vertex3D(std::vector<double> vrhovi) {
//		this->x = vrhovi[0];
//		this->y = vrhovi[1];
//		this->z = vrhovi[2];
//	}
//	double getX() {
//		return this->x;
//	}
//	double getY() {
//		return this->y;
//	}
//	double getZ() {
//		return this->z;
//	}
//	Vertex3D* copy() {
//		return new Vertex3D(x, y, z);
//	}
//	std::string toString() {
//		std::string s = std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z);
//		return s;
//	}
//	void setX(double x) {
//		this->x = x;
//	}
//	void setY(double y) {
//		this->y = y;
//	}
//	void setZ(double z) {
//		this->z = z;
//	}
//};
//
//class Face3D {
//private:
//	int indexes[3];
//	int a;
//	int b;
//	int c;
//	int d;
//
//	Face3D(int a, int b, int c) {
//		indexes[0] = a;
//		indexes[1] = b;
//		indexes[2] = c;
//	}
//	void koef_ravnine() {
//
//	}
//public:
//	Face3D(std::vector<int> trokuti) {
//		indexes[0] = trokuti[0] - 1;
//		indexes[1] = trokuti[1] - 1;
//		indexes[2] = trokuti[2] - 1;
//	}
//	int getIndexVrh1() {
//		return indexes[0];
//	}
//	int getIndexVrh2() {
//		return indexes[1];
//	}
//	int getIndexVrh3() {
//		return indexes[2];
//	}
//	double getA() {
//		return a;
//	}
//	double getB() {
//		return b;
//	}
//	double getC() {
//		return c;
//	}
//	double getD() {
//		return d;
//	}
//	void setA(double a) {
//		this->a = a;
//	}
//	void setB(double b) {
//		this->b = b;
//	}
//	void setC(double c) {
//		this->c = c;
//	}
//	void setD(double d) {
//		this->d = d;
//	}
//	Face3D* copy() {
//		return new Face3D(indexes[0], indexes[1], indexes[2]);
//	}
//	std::string toString() {
//		std::string s = std::to_string(indexes[0] + 1) + " " + std::to_string(indexes[1] + 1) + " " + std::to_string(indexes[2] + 1);
//		return s;
//	}
//	double polozajToc(double x, double y, double z) {
//		return a * x + b * y + c * z + d;
//	}
//
//};
//
//class ObjectModel {
//private:
//	std::vector<Vertex3D*> vrhovi;
//	std::vector<Face3D*> trokuti;
//	ObjectModel(std::vector<Vertex3D*> vrhovi, std::vector<Face3D*> trokuti) {
//		this->vrhovi = vrhovi;
//		this->trokuti = trokuti;
//	}
//	void dodajKoef() {
//		for (int i = 0; i < trokuti.size(); i++) {
//			int vrh1 = trokuti[i]->getIndexVrh1();
//			int vrh2 = trokuti[i]->getIndexVrh2();
//			int vrh3 = trokuti[i]->getIndexVrh3();
//			double v_a_x = vrhovi[vrh2]->getX() - vrhovi[vrh1]->getX();
//			double v_a_y = vrhovi[vrh2]->getY() - vrhovi[vrh1]->getY();
//			double v_a_z = vrhovi[vrh2]->getZ() - vrhovi[vrh1]->getZ();
//			double v_b_x = vrhovi[vrh3]->getX() - vrhovi[vrh1]->getX();
//			double v_b_y = vrhovi[vrh3]->getY() - vrhovi[vrh1]->getY();
//			double v_b_z = vrhovi[vrh3]->getZ() - vrhovi[vrh1]->getZ();
//			double n_x = v_a_y * v_b_z - v_a_z * v_b_y;
//			double n_y = -(v_a_x * v_b_z - v_a_z * v_b_x);
//			double n_z = v_a_x * v_b_y - v_a_y * v_b_x;
//			double d = -n_x * vrhovi[vrh1]->getX() - n_y * vrhovi[vrh1]->getY() - n_z * vrhovi[vrh1]->getZ();
//			trokuti[i]->setA(n_x);
//			trokuti[i]->setB(n_y);
//			trokuti[i]->setC(n_z);
//			trokuti[i]->setD(d);
//		}
//	}
//public:
//	ObjectModel(std::vector<std::vector<double> > vrhovi, std::vector<std::vector<int> > trokuti) {
//		for (int i = 0; i < vrhovi.size(); i++) {
//			Vertex3D *vrh = new Vertex3D(vrhovi[i]);
//			this->vrhovi.push_back(vrh);
//		}
//		for (int i = 0; i < trokuti.size(); i++) {
//			Face3D *trokut = new Face3D(trokuti[i]);
//			this->trokuti.push_back(trokut);
//		}
//		dodajKoef();
//
//	}
//	~ObjectModel() {
//		for (int i = 0; i < vrhovi.size(); i++) {
//			delete this->vrhovi[i];
//		}
//		for (int i = 0; i < trokuti.size(); i++) {
//			delete this->trokuti[i];
//		}
//	}
//	ObjectModel* copy() {
//		std::vector<Vertex3D*> vrhoviKopija;
//		std::vector<Face3D*> trokutiKopija;
//		for (int i = 0; i < this->vrhovi.size(); i++) {
//			Vertex3D *vrh = this->vrhovi[i]->copy();
//			vrhoviKopija.push_back(vrh);
//		}
//		for (int i = 0; i < this->trokuti.size(); i++) {
//			Face3D *trokut = this->trokuti[i]->copy();
//			trokutiKopija.push_back(trokut);
//		}
//		return new ObjectModel(vrhoviKopija, trokutiKopija);
//	}
//	std::string dumpToObj() {
//		std::string s;
//		for (int i = 0; i < vrhovi.size(); i++) {
//			s = s + vrhovi[i]->toString() + "\n";
//		}
//		for (int i = 0; i < trokuti.size(); i++) {
//			s = s + trokuti[i]->toString() + "\n";
//		}
//		return s;
//	}
//	void normalize() {
//		double xmin = 0, xmax = 0, ymin = 0, ymax = 0, zmin = 0, zmax = 0;
//		xmin = xmax = vrhovi[0]->getX();
//		ymin = ymax = vrhovi[0]->getY();
//		zmin = zmax = vrhovi[0]->getZ();
//		for (int i = 0; i < this->vrhovi.size(); i++) {
//			if (vrhovi[i]->getX() < xmin) {
//				xmin = vrhovi[i]->getX();
//			}
//			if (vrhovi[i]->getX() > xmax) {
//				xmax = vrhovi[i]->getX();
//			}
//			if (vrhovi[i]->getY() < ymin) {
//				ymin = vrhovi[i]->getY();
//			}
//			if (vrhovi[i]->getY() > ymax) {
//				ymax = vrhovi[i]->getY();
//			}
//			if (vrhovi[i]->getZ() < zmin) {
//				zmin = vrhovi[i]->getZ();
//			}
//			if (vrhovi[i]->getZ() > zmax) {
//				zmax = vrhovi[i]->getZ();
//			}
//		}
//		double xavg = (xmin + xmax) / 2.0;
//		double yavg = (ymin + ymax) / 2.0;
//		double zavg = (zmin + zmax) / 2.0;
//		// u M* drzim maksimalne raspon po nekoj osi.
//		double M = xmax - xmin;
//		if (ymax - ymin > M) M = ymax - ymin;
//		if (zmax - zmin > M) M = zmax - zmin;
//		for (int i = 0; i < vrhovi.size(); i++) {
//			vrhovi[i]->setX((vrhovi[i]->getX() - xavg) * 2 / M);
//			vrhovi[i]->setY((vrhovi[i]->getY() - yavg) * 2 / M);
//			vrhovi[i]->setZ((vrhovi[i]->getZ() - zavg) * 2 / M);
//		}
//
//	}
//	//0 ako je izvan tijela
//	//1 ako je unutar tijela 
//	//2 ako je na plohi
//	int polozajTocke(double x, double y, double z) {
//		int polozaj = 1;
//		for (int i = 0; i < trokuti.size(); i++) {
//			double val = trokuti[i]->polozajToc(x, y, z);
//			if (val > 0) {
//				polozaj = 0;
//				break;
//			}
//			else if (val == 0) {
//				polozaj = 2;
//				//std::cout<<"nula"<<std::endl;
//			}
//		}
//		return polozaj;
//	}
//};
//
//
//int main(void)
//{
//
//
//
//
//	std::string name = "kocka.obj";
//	std::vector<std::vector<std::string> > elementi = read_from_obj_file(name);
//	std::vector<std::vector<double> > vrhovi = vrati_vrhove(elementi);
//	std::vector<std::vector<int> > trokuti = vrati_trokute(elementi);
//	ObjectModel *kocka = new ObjectModel(vrhovi, trokuti);
//	std::string s = kocka->dumpToObj();
//	std::cout << s;
//	std::cout << "normaliziran" << std::endl;
//	kocka->normalize();
//	//std::string s2 = kocka->dumpToObj();
//	//std::cout << s2 << std::endl;
//
//
//
//
//
//	GLFWwindow* window;
//	std::cout << "jurij" << std::endl;
//
//	/* Initialize the library */
//	if (!glfwInit())
//		return -1;
//
//	/* Create a windowed mode window and its OpenGL context */
//	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//	if (!window)
//	{
//		glfwTerminate();
//		return -1;
//	}
//
//	/* Make the window's context current */
//	glfwMakeContextCurrent(window);
//
//	/* Loop until the user closes the window */
//	while (!glfwWindowShouldClose(window))
//	{
//		/* Render here */
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// kod 
//		glBegin(GL_TRIANGLES);
//		glVertex2f(-0.5f, -0.5f);
//		glVertex2f(0.0f, 0.5f);
//		glVertex2f(0.5f, -0.5f);
//		glEnd();
//		/* Swap front and back buffers */
//		glfwSwapBuffers(window);
//
//		/* Poll for and process events */
//		glfwPollEvents();
//	}
//
//	glfwTerminate();
//	return 0;
//}
//
//
//
//
//
//// ucitavanje iz obj file a
//std::vector<std::vector<std::string> > read_from_obj_file(std::string &s) {
//	std::ifstream input("kocka.obj");
//	std::string str;
//	std::vector<std::string> linije;
//
//	while (std::getline(input, str)) {
//		//std::cout<<str<<std::endl;
//		linije.push_back(str);
//	}
//	std::vector<std::vector<std::string> > elementi(linije.size());
//	for (int i = 0; i < linije.size(); i++) {
//		elementi[i] = split(linije[i], ' ');
//	}
//	return elementi;
//}
//
//std::vector<std::string> split(const std::string &s, char delim) {
//	std::stringstream ss(s);
//	std::string item;
//	std::vector<std::string> tokens;
//	while (std::getline(ss, item, delim)) {
//		tokens.push_back(item);
//	}
//	return tokens;
//}
//
//std::vector<std::vector<double> > vrati_vrhove(std::vector<std::vector<std::string> > elementi) {
//	std::vector<std::vector<double> > vrhovi;
//	int brVrh = 0;
//	for (int i = 0; i < elementi.size(); i++) {
//		if (elementi[i][0] == "v" || elementi[i][0] == "V") {
//			std::vector<double> vec;
//			vrhovi.push_back(vec);
//
//			for (int j = 1; j < elementi[i].size(); j++) {
//
//				double val = std::stod(elementi[i][j]);
//				vrhovi[brVrh].push_back(val);
//			}
//			brVrh++;
//		}
//	}
//	return vrhovi;
//}
//
//std::vector<std::vector<int> > vrati_trokute(std::vector<std::vector<std::string> > elementi) {
//	std::vector<std::vector<int> > trokuti;
//	int brTrokuta = 0;
//	for (int i = 0; i < elementi.size(); i++) {
//		if (elementi[i][0] == "f" || elementi[i][0] == "F") {
//			std::vector<int> vec;
//			trokuti.push_back(vec);
//
//			for (int j = 1; j < elementi[i].size(); j++) {
//
//				int val = std::stoi(elementi[i][j]);
//				trokuti[brTrokuta].push_back(val);
//			}
//			brTrokuta++;
//		}
//	}
//	return trokuti;
//}