#include "Shelf.h"
#include "model.h"
#include <stdio.h>
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <GLFW/glfw3.h>
#include <stdlib.h>


namespace Models {
	Shelf::Shelf(int id):Model(id) {
		for (int i = 0; i < 20; i++) {
			bot[i] = new Models::Bottle(2);
		}
		//bot = new Models::Bottle
		//("Corona/Corona.obj", "Corona/BotellaText.png");
	}
	Shelf::~Shelf() {
		for (int i = 0; i < 20; i++) {
			delete(bot[i]);
		}
	}
	void Shelf::draw(glm::mat4 V, glm::mat4 M) {
		//TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		this->drawSolid();
		M = glm::rotate(M, 4.71f, glm::vec3(1.0f, 0.0f, 0.0f));
		M = glm::rotate(M, 1.57f, glm::vec3(0.0f, 0.0f, 1.0f));
		M = glm::translate(M, glm::vec3(-20.0f, -50.0f, 11.0f));
		M = glm::scale(M, glm::vec3(0.8f, 0.8f, 0.8f));
		glLoadMatrixf(value_ptr(V*M));
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glm::mat4 M1;
		for (int i = 0; i < 20 / (20 / 4); i++) {
			M1 = glm::translate(M, glm::vec3(0.0f, 0.0f, i * 45 + 0.0f));
			for (int j = 0; j < 20 / 4; j++) {
				M1 = glm::translate(M1, glm::vec3(0.0f, 20.0f, 0.0f));
				glLoadMatrixf(value_ptr(V*M1));
				bot[i]->drawSolid();

			}
		}
		//bot->drawSolid();
	}
}