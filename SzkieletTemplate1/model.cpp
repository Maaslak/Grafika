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

namespace Models {
	
	void Model::drawWire() {
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		
		drawSolid();
		
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	}
	Model::Model()
	{
	}
	Model::~Model()
	{
		if (vertices != NULL)
			delete(vertices);
		if (normals != NULL)
				delete(normals);
		if (vertexNormals != NULL)
			delete(vertexNormals);
		if (texCoords != NULL)
			delete(texCoords);
		if (colors != NULL)
			delete(colors);
	}
	Model::Model(char* path)
	{
		obj_scene_data data;
		if (!parse_obj_scene(&data, path))	//loadOBJ "Corona/Corona.obj"
			throw EXCEPTION_BREAKPOINT;
		if (data.face_list[0]->vertex_count == 3) {
			vertexCount = data.face_count;
			vertices = new float[9 * data.face_count];
			for (unsigned int i = 0; i < data.face_count; i++)
			{
				for (unsigned int j = 0; j < 3; i++)
				{
					vertices[i*9 + j*3] = data.vertex_list[(data.face_list[i]->vertex_index)[j]]->e[0];
					vertices[i * 9 + j * 3 + 1] = data.vertex_list[(data.face_list[i]->vertex_index)[j]]->e[1];
					vertices[i * 9 + j * 3 + 2] = data.vertex_list[(data.face_list[i]->vertex_index)[j]]->e[2];
				}
			}
		}
		if (data.face_list[0]->vertex_count == 4) {
			vertexCount = data.face_count;
			vertices = new float[12 * data.face_count];
			for (unsigned int i = 0; i < data.face_count; i++)
			{
				for (unsigned int j = 0; j < 4; j++)
				{
					vertices[i*12 + j*3] = data.vertex_list[(data.face_list[i]->vertex_index)[j]]->e[0];
					vertices[i * 12 + j * 3 + 1] = data.vertex_list[(data.face_list[i]->vertex_index)[j]]->e[1];
					vertices[i * 12 + j * 3 + 2] = data.vertex_list[(data.face_list[i]->vertex_index)[j]]->e[2];

				}
			}
		}
	}
}