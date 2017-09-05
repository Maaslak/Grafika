#include "Gallery.h"



namespace Models {
	Gallery::Gallery(int id) :Model(id) {
		for (int i = 0; i < 20; i++) {
			shelf[i] = new Models::Shelf(1);
		}
		//shelf = new Models::Shelf(1);
	}
	Gallery::~Gallery() {
		for (int i = 0; i < 20; i++) {
			delete(shelf[i]);
		}
	}
	void Gallery::draw(glm::mat4 V, glm::mat4 M) {
		this->drawSolid();

		M = glm::translate(M, glm::vec3(0.0f, -80.0f, 0.0f));
		glLoadMatrixf(value_ptr(V*M));
		
		for (int i = 0; i < 20; i++) {
			shelf[i]->draw(V, M);
			M = glm::translate(M, glm::vec3(120.0f, 0.0f, 0.0f));
			glLoadMatrixf(value_ptr(V*M));
		}
		
	}
}