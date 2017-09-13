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

namespace Models {
	//vector <mod> Model::models;
	mod Model::models[20];
	void Model::drawWire(glm::mat4 V) {
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		
		drawSolid(V);
		
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	}

	void Model::drawSolid(glm::mat4 V) {
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

	Model::Model()
	{
		//models[id].isdynamic = false;
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
		this->id = id;
		this->M = M;
	}
}