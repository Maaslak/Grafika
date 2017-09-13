/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <structuredquery.h>
#include <fltUserStructures.h>
#include <StructuredQueryCondition.h>
#include <cstdlib>
#include "glm/glm.hpp"
//#include <GLFW/glfw3.h>
#include "GL/glew.h"
#include "GL/glut.h"
#include "constants.h"
#include <stdio.h>
#include "objTester\obj_parser.h"
#include "lodepng.h"
//#include "allmodels.h"
//#include "Bottle.h"
//#include "main_file.cpp"

using namespace std;

typedef struct tex_type {
	std::vector<unsigned char> data;
	unsigned width, height, depth;
	GLuint tex;
};

typedef struct mod {
	int vertexCount;
	float *vertices;
	float *normals;
	float *vertexNormals;
	float *texCoords;
	float *colors;

	tex_type lode;
	bool isdynamic = false;
	bool istriangle = true;
};


namespace Models {

	
	

	class Model {
		public:
			/*int vertexCount;
			float *vertices;
			float *normals;
			float *vertexNormals;
			float *texCoords;
			float *colors;

			tex_type lode;
			bool isdynamic = false;
			bool istriangle = true;*/

			//static vector<mod> models;
			static mod models[20];

			int id;
			glm::mat4 M;
			//static glm::mat4 V;
					
			virtual void drawSolid(glm::mat4);
			virtual void drawWire(glm::mat4);

			Model();
			~Model();
			Model(int,glm::mat4);

	};
}

#endif