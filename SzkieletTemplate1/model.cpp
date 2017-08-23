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
		glDeleteTextures(1, &lode.tex);
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
	Model::Model(char* path, char* texpath = NULL)
	{
		if(lodepng::decode(lode.data, lode.width, lode.height, texpath))
			cout<<"Unable to load texture from" << path;
		else {
			glGenTextures(1, &lode.tex);
			glBindTexture(GL_TEXTURE_2D, lode.tex);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, lode.width, lode.height, 0,
				GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)(lode.data.data()));
		}
		obj_scene_data data;
		if (!parse_obj_scene(&data, path))	//loadOBJ "Corona/Corona.obj"
			throw EXCEPTION_BREAKPOINT;
		if (data.face_list[0]->vertex_count == 3) {
			vertexCount = 3 * data.face_count;
			vertices = new float[9 * data.face_count];
			texCoords = new float[9 * data.face_count];
			//normals = new float[9 * data.face_count];
			for (unsigned int i = 0; i < data.face_count; i++)
			{
				for (unsigned int j = 0; j < 3; j++)
				{
					vertices[i * 9 + j * 3] = data.vertex_list[(data.face_list[i]->vertex_index)[j]]->e[0];
					vertices[i * 9 + j * 3 + 1] = -data.vertex_list[(data.face_list[i]->vertex_index)[j]]->e[1];
					vertices[i * 9 + j * 3 + 2] = data.vertex_list[(data.face_list[i]->vertex_index)[j]]->e[2];

					texCoords[i * 9 + j * 3] = data.vertex_texture_list[(data.face_list[i]->texture_index)[j]]->e[0];
					texCoords[i * 9 + j * 3 + 1] = -data.vertex_texture_list[(data.face_list[i]->texture_index)[j]]->e[1];
					texCoords[i * 9 + j * 3 + 2] = data.vertex_texture_list[(data.face_list[i]->texture_index)[j]]->e[2];

					//normals[i * 9 + j * 3] = data.vertex_normal_list[(data.face_list[i]->normal_index)[j]]->e[0];
					//normals[i * 9 + j * 3 + 1] = -data.vertex_normal_list[(data.face_list[i]->normal_index)[j]]->e[1];
					//normals[i * 9 + j * 3 + 2] = data.vertex_normal_list[(data.face_list[i]->normal_index)[j]]->e[2];

				}
			}
		}
		if (data.face_list[0]->vertex_count == 4) {
			vertexCount = data.face_count;
			vertices = new float[12 * data.face_count];
			texCoords = new float[12 * data.face_count];
			//normals = new float[12 * data.face_count];
			for (unsigned int i = 0; i < data.face_count; i++)
			{
				for (unsigned int j = 0; j < 4; j++)
				{
					vertices[i*12 + j*3] = data.vertex_list[(data.face_list[i]->vertex_index)[j]]->e[0];
					vertices[i * 12 + j * 3 + 1] = -data.vertex_list[(data.face_list[i]->vertex_index)[j]]->e[1];
					vertices[i * 12 + j * 3 + 2] = data.vertex_list[(data.face_list[i]->vertex_index)[j]]->e[2];

					texCoords[i * 12 + j * 3] = data.vertex_texture_list[(data.face_list[i]->texture_index)[j]]->e[0];
					texCoords[i * 12 + j * 3 + 1] = -data.vertex_texture_list[(data.face_list[i]->texture_index)[j]]->e[1];
					texCoords[i * 12 + j * 3 + 2] = data.vertex_texture_list[(data.face_list[i]->texture_index)[j]]->e[2];

					//normals[i * 12 + j * 3] = data.vertex_normal_list[(data.face_list[i]->normal_index)[j]]->e[0];
					//normals[i * 12 + j * 3 + 1] = -data.vertex_normal_list[(data.face_list[i]->normal_index)[j]]->e[1];
					//normals[i * 12 + j * 3 + 2] = data.vertex_normal_list[(data.face_list[i]->normal_index)[j]]->e[2];
				}
			}
		}
	}
}