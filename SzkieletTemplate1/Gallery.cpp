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
		M = glm::scale(M, glm::vec3(0.05f, 0.05f, 0.05f));
		M = glm::rotate(M, 1.57f, glm::vec3(1.0f, 0.0f, 0.0f));
		//M = glm::rotate(M, 3.14f, glm::vec3(0.0f, 0.5f, 0.0f));
		M = glm::translate(M, glm::vec3(450.0f, 0.0f, -325.0f));
		//glLoadMatrixf(value_ptr(V*M));

		for (int j = 0; j < 2; j++) {
			if (j == 1) {
				M = glm::rotate(M, 1.57f, glm::vec3(0.0f, -1.0f, 0.0f));
				M = glm::translate(M, glm::vec3(1710.0f, 0.0f, -520.0f));
			}
			for (int i = 0; i < 4; i++) {
				M = glm::translate(M, glm::vec3(-130.0f, 0.0f, 0.0f));
				glLoadMatrixf(value_ptr(V*M));
				shelf[i]->draw(V, M);
			}
			
			M = glm::translate(M, glm::vec3(-130.0f, 0.0f, 0.0f));
			M = glm::rotate(M, 1.57f, glm::vec3(0.0f, 1.0f, 0.0f));
			M = glm::translate(M, glm::vec3(260.0f, 0.0f, 0.0f));
			for (int i = 0; i < 2; i++) {
				M = glm::translate(M, glm::vec3(-390.0f, 0.0f, 0.0f));
				glLoadMatrixf(value_ptr(V*M));
				shelf[i]->draw(V, M);
			}
			
			M = glm::translate(M, glm::vec3(-120.0f, 0.0f, 0.0f));
			M = glm::rotate(M, 1.57f, glm::vec3(0.0f, 1.0f, 0.0f));
			//M = glm::translate(M, glm::vec3(0.0f, 0.0f, 0.0f));
			for (int i = 0; i < 4; i++) {
				M = glm::translate(M, glm::vec3(-130.0f, 0.0f, 0.0f));
				glLoadMatrixf(value_ptr(V*M));
				shelf[i]->draw(V, M);
			}

			M = glm::translate(M, glm::vec3(-120.0f, 0.0f, 0.0f));
			M = glm::rotate(M, 1.57f, glm::vec3(0.0f, 1.0f, 0.0f));
			//M = glm::translate(M, glm::vec3(0.0f, 0.0f, 0.0f));
			for (int i = 0; i < 4; i++) {
				M = glm::translate(M, glm::vec3(-130.0f, 0.0f, 0.0f));
				glLoadMatrixf(value_ptr(V*M));
				shelf[i]->draw(V, M);
			}
		}
	}
}