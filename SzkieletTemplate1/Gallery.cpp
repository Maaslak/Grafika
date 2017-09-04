#include "Gallery.h"



namespace Models {
	Gallery::Gallery(int id) :Model(id) {
		/*for (int i = 0; i < 20; i++) {
		shelf[i] = new Models::Bottle
		("Corona/eb_metal_shelf_02.obj", "Corona/White Wood.png");
		}*/
		shelf = new Models::Shelf(2);
	}
	Gallery::~Gallery() {
		for (int i = 0; i < 1; i++) {
			delete(shelf);
		}
	}
	void Gallery::draw(glm::mat4 V, glm::mat4 M) {
		this->drawSolid();

		/*for (int i = 0; i < 1; i++) {
		shelf[i]->draw(V, M);
		M = glm::translate(M, glm::vec3(120.0f, 0.0f, 0.0f));
		glLoadMatrixf(value_ptr(V*M));
		}*/
		shelf->draw(V, M);
	}
}