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
	//vector <mod> Model::models;
	mod Model::models[20];
	void Model::drawWire() {
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		
		drawSolid();
		
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	}

	void Model::drawSolid() {
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
	Model::Model(int id)
	{
		this->id = id;
		/*
		cout << "tworzenie";
		if(texpath != NULL)
			if(lodepng::decode(lode.data, lode.width, lode.height, texpath))
				cout<<"Unable to load texture from" << path;
		else {
			glGenTextures(1, &lode.tex);
			glBindTexture(GL_TEXTURE_2D, lode.tex);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, lode.width, lode.height, 0,
				GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)(lode.data.data()));
		}

		/* (texpath != NULL) {
			lodepng::decode(lode.data, lode.width, lode.height, texpath);
			glGenTextures(1, &lode.tex);
			glBindTexture(GL_TEXTURE_2D, lode.tex);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, lode.width, lode.height, 0,
				GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)(lode.data.data()));
		}*/

		/*
		obj_scene_data data;
		if (!parse_obj_scene(&data, path))	//loadOBJ "Corona/Corona.obj"
			throw EXCEPTION_BREAKPOINT;
		isdynamic = true;
		if (data.face_list[0]->vertex_count == 3) {
			vertexCount = 3 * data.face_count;
			vertices = new float[9 * data.face_count];
			texCoords = new float[9 * data.face_count];
			normals = new float[9 * data.face_count];
			for (unsigned int i = 0; i < data.face_count; i++)
			{
				for (unsigned int j = 0; j < 3; j++)
				{
					vertices[i * 9 + j * 3] = data.vertex_list[(data.face_list[i]->vertex_index)[j]]->e[0];
					vertices[i * 9 + j * 3 + 1] = data.vertex_list[(data.face_list[i]->vertex_index)[j]]->e[1];
					vertices[i * 9 + j * 3 + 2] = data.vertex_list[(data.face_list[i]->vertex_index)[j]]->e[2];

					if (data.vertex_texture_count != 0) {
						texCoords[i * 9 + j * 3] = data.vertex_texture_list[(data.face_list[i]->texture_index)[j]]->e[0];
						texCoords[i * 9 + j * 3 + 1] = 1.0f - data.vertex_texture_list[(data.face_list[i]->texture_index)[j]]->e[1];
						texCoords[i * 9 + j * 3 + 2] = data.vertex_texture_list[(data.face_list[i]->texture_index)[j]]->e[2];
					}
					if (data.vertex_normal_count != 0) {
						normals[i * 9 + j * 3] = data.vertex_normal_list[(data.face_list[i]->normal_index)[j]]->e[0];
						normals[i * 9 + j * 3 + 1] = -data.vertex_normal_list[(data.face_list[i]->normal_index)[j]]->e[1];
						normals[i * 9 + j * 3 + 2] = data.vertex_normal_list[(data.face_list[i]->normal_index)[j]]->e[2];
					}

				}
			}
		}
		if (data.face_list[0]->vertex_count == 4) {
			istriangle = false;
			vertexCount = data.face_count;
			vertices = new float[12 * data.face_count];
			texCoords = new float[12 * data.face_count];
			normals = new float[12 * data.face_count];
			for (unsigned int i = 0; i < data.face_count; i++)
			{
				for (unsigned int j = 0; j < 4; j++)
				{
					vertices[i*12 + j*3] = data.vertex_list[(data.face_list[i]->vertex_index)[j]]->e[0];
					vertices[i * 12 + j * 3 + 1] = data.vertex_list[(data.face_list[i]->vertex_index)[j]]->e[1];
					vertices[i * 12 + j * 3 + 2] = data.vertex_list[(data.face_list[i]->vertex_index)[j]]->e[2];

					if (data.vertex_texture_count != 0) {
						texCoords[i * 12 + j * 3] = data.vertex_texture_list[(data.face_list[i]->texture_index)[j]]->e[0];
						texCoords[i * 12 + j * 3 + 1] = 1.0f - data.vertex_texture_list[(data.face_list[i]->texture_index)[j]]->e[1];
						texCoords[i * 12 + j * 3 + 2] = data.vertex_texture_list[(data.face_list[i]->texture_index)[j]]->e[2];
					}
					if (data.vertex_normal_count != 0) {
						normals[i * 12 + j * 3] = data.vertex_normal_list[(data.face_list[i]->normal_index)[j]]->e[0];
						normals[i * 12 + j * 3 + 1] = -data.vertex_normal_list[(data.face_list[i]->normal_index)[j]]->e[1];
						normals[i * 12 + j * 3 + 2] = data.vertex_normal_list[(data.face_list[i]->normal_index)[j]]->e[2];
					}
				}
			}
		}*/
	}
}