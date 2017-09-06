#include "Gallery.h"



namespace Models {
	Gallery::Gallery(int id) :Model(id) {
		for (int i = 0; i < 28; i++) {
			shelf[i] = new Models::Shelf(1);
		}
		//shelf = new Models::Shelf(1);
	}
	Gallery::~Gallery() {
		for (int i = 0; i < 28; i++) {
			delete(shelf[i]);
		}
	}
	void Gallery::draw(glm::mat4 V, glm::mat4 M) {
		this->drawSolid();
		M = glm::scale(M, glm::vec3(0.15f, 0.15f, 0.15f));
		M = glm::rotate(M, 1.57f, glm::vec3(-1.0f, 0.0f, 0.0f));
		M = glm::rotate(M, 3.14f, glm::vec3(0.0f, 1.0f, 0.0f));
		M = glm::translate(M, glm::vec3(-1680.0f, -160.0f, -570.0f));
		//glLoadMatrixf(value_ptr(V*M));

		for (int j = 0; j < 2; j++) {
			if (j == 1) {
				M = glm::rotate(M, 1.57f, glm::vec3(0.0f, -1.0f, 0.0f));
				M = glm::translate(M, glm::vec3(-1570.0f, 0.0f, 450.0f));
			}
			for (int i = 0; i < 4; i++) {
				M = glm::translate(M, glm::vec3(130.0f, 0.0f, 0.0f));
				glLoadMatrixf(value_ptr(V*M));
				shelf[i]->draw(V, M);
			}

			M = glm::translate(M, glm::vec3(65.0f, 0.0f, 0.0f));
			M = glm::rotate(M, 1.57f, glm::vec3(0.0f, 1.0f, 0.0f));
			M = glm::translate(M, glm::vec3(-325.0f, 0.0f, 0.0f));
			for (int i = 0; i < 2; i++) {
				M = glm::translate(M, glm::vec3(390.0f, 0.0f, 0.0f));
				glLoadMatrixf(value_ptr(V*M));
				shelf[i]->draw(V, M);
			}

			M = glm::translate(M, glm::vec3(55.0f, 0.0f, 0.0f));
			M = glm::rotate(M, 1.57f, glm::vec3(0.0f, 1.0f, 0.0f));
			M = glm::translate(M, glm::vec3(-65.0f, 0.0f, 0.0f));
			for (int i = 0; i < 4; i++) {
				M = glm::translate(M, glm::vec3(130.0f, 0.0f, 0.0f));
				glLoadMatrixf(value_ptr(V*M));
				shelf[i]->draw(V, M);
			}

			M = glm::translate(M, glm::vec3(55.0f, 0.0f, 0.0f));
			M = glm::rotate(M, 1.57f, glm::vec3(0.0f, 1.0f, 0.0f));
			M = glm::translate(M, glm::vec3(-65.0f, 0.0f, 0.0f));
			for (int i = 0; i < 4; i++) {
				M = glm::translate(M, glm::vec3(130.0f, 0.0f, 0.0f));
				glLoadMatrixf(value_ptr(V*M));
				shelf[i]->draw(V, M);
			}
		}
	}
}