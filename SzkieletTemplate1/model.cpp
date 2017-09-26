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

#include "model.h"

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <GLFW/glfw3.h>
#include <stdlib.h>

extern const int CollTabPrec;

namespace Models {
	//vector <mod> Model::models;
	mod Model::models[30];
	vector<Model*> Model::allobjects;
	unsigned int Model::count = -1;
	CollisionTables Model::coltab;

	void Model::drawWire(glm::mat4 V) {
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		
		drawSolid(V);
		
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	}

	void Model::myMinMax(glm::vec3& min, glm::vec3& max)
	{
		for (size_t i = 0; i < models[id].vertexCount; i++)
		{
			glm::vec4 temp;
			temp.x = models[id].vertices[3 * i];
			temp.y = models[id].vertices[3 * i + 1];
			temp.z = models[id].vertices[3 * i + 2];
			temp.w = 0.0f;
			temp = this -> M * temp ;
			if (temp.x > max.x)
				max.x = temp.x;
			if (temp.x < min.x)
				min.x = temp.x;
			if (temp.y > max.y)
				max.y = temp.y;
			if (temp.y < min.y)
				min.y = temp.y;
			if (temp.z > max.z)
				max.z = temp.z;
			if (temp.z < min.z)
				min.z = temp.z;
		}
	}

	void Model::drawSolid(glm::mat4 V) {
		//gluPerspective(10, 1, 1, 100);
		glStencilFunc(GL_ALWAYS, this->selid%255, -1);

		glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
		glLoadMatrixf(value_ptr(V*M));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, models[id].lode.tex); //Uaktywnij uchwyt
			
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, models[id].vertices); 
		glTexCoordPointer(3, GL_FLOAT, 0, models[id].texCoords);
		glNormalPointer(GL_FLOAT, sizeof(float) * 4, models[id].vertexNormals);

		if (models[id].istriangle)
			glDrawArrays(GL_TRIANGLES, 0, models[id].vertexCount); //Rysuj model
		else
			glDrawArrays(GL_QUADS, 0, models[id].vertexCount);//Posprzątaj po sobie
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		
	}

	void Model::UpdateCollTable() {
		for (size_t i = 0; i < models[id].vertexCount; i++)
		{
			glm::vec4 temp;
			temp.x = models[id].vertices[3 * i];
			temp.y = models[id].vertices[3 * i + 1];
			temp.z = models[id].vertices[3 * i + 2];
			temp.w = 0.0f;
			temp = this->M * temp;
			int idx, idz;
			idx = round((temp.x - coltab.min.x) / coltab.delta.x);
			idz = round((temp.z - coltab.min.z) / coltab.delta.z);
			if (idx == CollTabPrec)
				idx--;
			if (idz == CollTabPrec)
				idz--;
			coltab.tab[idx][idz] = true;
		}

	}

	Model::Model()
	{
		//models[id].isdynamic = false;
		this->count++;
	}
	Model::~Model()
	{
		/*glDeleteTextures(1, &models[i].lode.tex);
		if (models[i].isdynamic) {
			if (models[i].vertices != NULL)
				delete(models[i].vertices);
			if (models[i].normals != NULL)
				delete(models[i].normals);
			if (models[i].vertexNormals != NULL)
				delete(models[i].vertexNormals);
			if (models[i].texCoords != NULL)
				delete(models[i].texCoords);
			if (models[i].colors != NULL)
				delete(models[i].colors);
		}*/
	}


	Model::Model(int id,glm::mat4 M)
	{
		Model();
		this->selid = this->count;
		allobjects.push_back(this);
		this->id = id;
		this->M = M;


	}
}