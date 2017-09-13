#include "Shelf.h"
//#include "model.h"
#include <stdio.h>
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <GLFW/glfw3.h>
#include <stdlib.h>


namespace Models {
	Shelf::Shelf(int id,int idbot,glm::mat4 M):Model(id,M) {
		this->idbot = idbot;

		if (this->idbot == 2) { //Corona
			M = glm::rotate(M, 4.71f, glm::vec3(1.0f, 0.0f, 0.0f));
			M = glm::rotate(M, 1.57f, glm::vec3(0.0f, 0.0f, 1.0f));
			M = glm::translate(M, glm::vec3(-20.0f, -50.0f, 11.0f));
			M = glm::scale(M, glm::vec3(0.8f, 0.8f, 0.8f));

			glm::mat4 M1;
			for (int i = 0; i < 20 / (20 / 4); i++) {
				M1 = glm::translate(M, glm::vec3(0.0f, 0.0f, i * 45 + 0.0f));
				for (int j = 0; j < 20 / 4; j++) {
					M1 = glm::translate(M1, glm::vec3(0.0f, 20.0f, 0.0f));
					bot[j + (i * 5)] = new Models::Bottle(idbot,M1);

				}
			}

		}
		else
			if (this->idbot == 3) { //Moet
				M = glm::rotate(M, 4.71f, glm::vec3(1.0f, 0.0f, 0.0f));
				M = glm::translate(M, glm::vec3(-50.0f, -20.0f, 11.0f));
				M = glm::scale(M, glm::vec3(3.1f, 3.1f, 3.1f));

				glm::mat4 M1;
				for (int i = 0; i < 20 / (20 / 4); i++) {
					M1 = glm::translate(M, glm::vec3(0.0f, 0.0f, i * 11.6 + 0.0f));
					for (int j = 0; j < 20 / 4; j++) {
						M1 = glm::translate(M1, glm::vec3(5.0f, 0.0f, 0.0f));
						bot[j + (i * 5)] = new Models::Bottle(idbot, M1);

					}
				}
			}
			else
				if (this->idbot == 4) { //Absolut
					M = glm::rotate(M, 4.71f, glm::vec3(1.0f, 0.0f, 0.0f));
					M = glm::translate(M, glm::vec3(-57.0f, -20.0f, 11.0f));
					M = glm::scale(M, glm::vec3(0.025f, 0.025f, 0.025f));

					glm::mat4 M1;
					for (int i = 0; i < 20 / (20 / 4); i++) {
						M1 = glm::translate(M, glm::vec3(0.0f, 0.0f, i * 1440 + 0.0f));
						for (int j = 0; j < 20 / 4; j++) {
							M1 = glm::translate(M1, glm::vec3(750.0f, 0.0f, 0.0f));
							bot[j + (i * 5)] = new Models::Bottle(idbot, M1);

						}
					}
				}
				else
					if (this->idbot == 5) { //Chivas
						M = glm::rotate(M, 4.71f, glm::vec3(1.0f, 0.0f, 0.0f));
						M = glm::translate(M, glm::vec3(-57.0f, -20.0f, 11.0f));
						M = glm::scale(M, glm::vec3(2.5f, 2.5f, 2.5f));

						glm::mat4 M1;
						for (int i = 0; i < 20 / (20 / 4); i++) {
							M1 = glm::translate(M, glm::vec3(0.0f, 0.0f, i * 14.25f + 0.0f));
							for (int j = 0; j < 20 / 4; j++) {
								M1 = glm::translate(M1, glm::vec3(7.5f, 0.0f, 0.0f));
								bot[j + (i * 5)] = new Models::Bottle(idbot, M1);

							}
						}
					}
					else
						if (this->idbot == 6) { //heineken
							M = glm::rotate(M, 4.71f, glm::vec3(1.0f, 0.0f, 0.0f));
							M = glm::translate(M, glm::vec3(-57.0f, -20.0f, 11.0f));
							M = glm::scale(M, glm::vec3(3.0f, 3.0f, 3.0f));

							glm::mat4 M1;
							for (int i = 0; i < 20 / (20 / 4); i++) {
								M1 = glm::translate(M, glm::vec3(0.0f, 0.0f, i * 12.0f + 0.0f));
								for (int j = 0; j < 20 / 4; j++) {
									M1 = glm::translate(M1, glm::vec3(6.1f, 0.0f, 0.0f));
									bot[j + (i * 5)] = new Models::Bottle(idbot, M1);

								}
							}
						}
						else
							if (this->idbot == 7 || this->idbot == 8) { //Screaming Eagle i Les Hauts
								M = glm::rotate(M, 4.71f, glm::vec3(1.0f, 0.0f, 0.0f));
								M = glm::translate(M, glm::vec3(-50.0f, -20.0f, 27.2f));
								M = glm::scale(M, glm::vec3(0.11f, 0.11f, 0.11f));

								glm::mat4 M1;
								for (int i = 0; i < 20 / (20 / 4); i++) {
									M1 = glm::translate(M, glm::vec3(0.0f, 0.0f, i * 325.0f + 0.0f));
									for (int j = 0; j < 20 / 4; j++) {
										M1 = glm::translate(M1, glm::vec3(180.0f, 0.0f, 0.0f));
										bot[j + (i * 5)] = new Models::Bottle(idbot, M1);
									}
								}
							}
							else
								if (this->idbot == 9) { //TurnBull's
									M = glm::rotate(M, 4.71f, glm::vec3(1.0f, 0.0f, 0.0f));
									M = glm::translate(M, glm::vec3(-57.0f, -20.0f, 11.0f));
									M = glm::scale(M, glm::vec3(3.0f, 3.0f, 3.0f));

									glm::mat4 M1;
									for (int i = 0; i < 20 / (20 / 4); i++) {
										M1 = glm::translate(M, glm::vec3(0.0f, 0.0f, i * 12.0f + 0.0f));
										for (int j = 0; j < 20 / 4; j++) {
											M1 = glm::translate(M1, glm::vec3(6.2f, 0.0f, 0.0f));
											bot[j + (i * 5)] = new Models::Bottle(idbot, M1);
										}
									}
								}
								else
									if (this->idbot == 10) { //Napoleon
										M = glm::rotate(M, 4.71f, glm::vec3(1.0f, 0.0f, 0.0f));
										M = glm::translate(M, glm::vec3(-57.0f, -20.0f, 11.0f));
										M = glm::scale(M, glm::vec3(0.025f, 0.025f, 0.025f));

										glm::mat4 M1;
										for (int i = 0; i < 20 / (20 / 4); i++) {
											M1 = glm::translate(M, glm::vec3(0.0f, 0.0f, i * 1430.0f + 0.0f));
											for (int j = 0; j < 20 / 4; j++) {
												M1 = glm::translate(M1, glm::vec3(780.0f, 0.0f, 0.0f));
												bot[j + (i * 5)] = new Models::Bottle(idbot, M1);
											}
										}
									}
	}
	Shelf::~Shelf() {
		for (int i = 0; i < 20; i++) {
			delete(bot[i]);
		}
	}
	void Shelf::draw(glm::mat4 V) {
		this->drawSolid(V);
		for (int i = 0; i < 20; i++) {
			bot[i]->draw(V);
		}
	}
}