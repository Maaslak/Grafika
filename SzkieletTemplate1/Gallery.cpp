#include "Gallery.h"



namespace Models {
	Gallery::Gallery(int id, glm::mat4 M) :Model(id, M) {
		
		initCollisionTable();
		UpdateCollTable();

		M = glm::scale(M, glm::vec3(0.05f, 0.05f, 0.05f));
		M = glm::rotate(M, 1.57f, glm::vec3(1.0f, 0.0f, 0.0f));
		M = glm::translate(M, glm::vec3(450.0f, 160.0f, -325.0f));
		

		for (int j = 0; j < 2; j++) {
			if (j == 1) {
				M = glm::rotate(M, 1.57f, glm::vec3(0.0f, -1.0f, 0.0f));
				M = glm::translate(M, glm::vec3(1710.0f, 0.0f, -520.0f));
			}
			for (int i = 0 + (j * 14); i < 4 + (j * 14); i++) {
				M = glm::translate(M, glm::vec3(-130.0f, 0.0f, 0.0f));
				shelf[i] = new Models::Shelf(1, //2, M);
												18, M);
			}

			M = glm::translate(M, glm::vec3(-130.0f, 0.0f, 0.0f));
			M = glm::rotate(M, 1.57f, glm::vec3(0.0f, 1.0f, 0.0f));
			M = glm::translate(M, glm::vec3(260.0f, 0.0f, 0.0f));
			for (int i = 4 + (j * 14); i < 6 + (j * 14); i++) {
				M = glm::translate(M, glm::vec3(-390.0f, 0.0f, 0.0f));
				shelf[i] = new Models::Shelf(1, //2, M);
												18, M);
			}

			M = glm::translate(M, glm::vec3(-120.0f, 0.0f, 0.0f));
			M = glm::rotate(M, 1.57f, glm::vec3(0.0f, 1.0f, 0.0f));
			for (int i = 6 + (j * 14); i < 10 + (j * 14); i++) {
				M = glm::translate(M, glm::vec3(-130.0f, 0.0f, 0.0f));
				shelf[i] = new Models::Shelf(1, //2, M);
												16, M);
			}

			M = glm::translate(M, glm::vec3(-120.0f, 0.0f, 0.0f));
			M = glm::rotate(M, 1.57f, glm::vec3(0.0f, 1.0f, 0.0f));
			for (int i = 10 + (j * 14); i < 14 + (j * 14); i++) {
				M = glm::translate(M, glm::vec3(-130.0f, 0.0f, 0.0f));
				shelf[i] = new Models::Shelf(1, //2, M);
												17, M);
			}
		}
		this->UpdateCollTable();
	}
	Gallery::~Gallery() {
		for (size_t i = 0; i < CollTabPrec; i++)
		{
			delete(this->coltab.tab[i]);
		}
		delete(this->coltab.tab);
		for (int i = 0; i < 28; i++) {
			delete(shelf[i]);
		}
	}
	void Gallery::draw(glm::mat4 V) {
		this->drawSolid(V);
		for (int i = 0; i < 28; i++) {
			shelf[i]->draw(V);
		}
	}
	void Gallery::initCollisionTable() {
		Model::coltab.tab = new bool*[CollTabPrec];
		for (size_t i = 0; i < CollTabPrec; i++)
		{
			this->coltab.tab[i] = new bool[CollTabPrec];
		}
		for (size_t i = 0; i < CollTabPrec; i++)
		{
			for (size_t j = 0; j < CollTabPrec; j++)
			{
				coltab.tab[i][j] = false;
			}
		}
		static float limit = 10000;
		glm::vec3 min, max;
		min = glm::vec3(limit, limit, limit);
		max = glm::vec3(-limit, -limit, -limit);
		this->myMinMax(min, max);
		//coltab.delta = max - min; //Nie dzia³a, jakiœ dziwny operator odejmowania
		coltab.delta.x = (max.x - min.x) / CollTabPrec;
		coltab.delta.y = (max.y - min.y) / CollTabPrec;
		coltab.delta.z = (max.z - min.z) / CollTabPrec;
		coltab.min = min;
		coltab.max = max;
	}
	bool Gallery::isCollision(glm::vec3 cameraPos) {
		glm::vec4 temp;
		temp = glm::vec4(cameraPos, 0.0f);
		int x, y, z;
		x = round((temp.x - Models::Model::coltab.min.x) / Models::Model::coltab.delta.x);
		//idy = round((temp.y - Models::Model::coltab.min.y) / Models::Model::coltab.delta.y);
		z = round((temp.z - Models::Model::coltab.min.z) / Models::Model::coltab.delta.z);
		const int radius = CollTabPrec / 50;
		for (int idx = x - radius; idx < x + radius; idx++) {
			for (int idz = z - radius; idz < z + radius; idz++) {
				if (idx >= CollTabPrec || idz >= CollTabPrec || idx < 0 || idz < 0) {
					cout << "Out of Range!!!\n";
					return true;
				}
				else {
					if (coltab.tab[idx][idz]) {
						cout << "Collision!!!!\n";
						return true;
					}
				}
			}
		}
		return false;
	}
}