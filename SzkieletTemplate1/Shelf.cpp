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
		//this->idbot = idbot;
		this->idbot = 2;
		//this->UpdateCollTable();

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
					bot[j + (i * 5)] = new Models::Bottle(this->idbot,M1);

				}
			}

		}
		else
			if (this->idbot == 3 || this->idbot == 20) { //Moet i Gout de Diamant 
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
						if (this->idbot == 6 || this->idbot == 21 || this->idbot == 22) { //heineken, BrewDog Atlantic IPA i Budweiser
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
							if (this->idbot == 7 || this->idbot == 8 || this->idbot == 14) { //Screaming Eagle, Les Hauts i Chateau Margaux
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






									else
										if (this->idbot == 11) { //Courvoisier 1
											M = glm::rotate(M, 4.71f, glm::vec3(1.0f, 0.0f, 0.0f));
											M = glm::translate(M, glm::vec3(-57.0f, -20.0f, 11.0f));
											M = glm::scale(M, glm::vec3(0.05f, 0.05f, 0.05f));

											glm::mat4 M1;
											for (int i = 0; i < 20 / (20 / 4); i++) {
												M1 = glm::translate(M, glm::vec3(0.0f, 0.0f, i * 715.0f + 0.0f));
												for (int j = 0; j < 20 / 4; j++) {
													M1 = glm::translate(M1, glm::vec3(390.0f, 0.0f, 0.0f));
													bot[j + (i * 5)] = new Models::Bottle(idbot, M1);
												}
											}
										}
										else
											if (this->idbot == 12) { //Courvoisier 2
												M = glm::rotate(M, 4.71f, glm::vec3(1.0f, 0.0f, 0.0f));
												M = glm::translate(M, glm::vec3(-57.0f, -20.0f, 11.0f));
												M = glm::scale(M, glm::vec3(0.05f, 0.05f, 0.05f));

												glm::mat4 M1;
												for (int i = 0; i < 20 / (20 / 4); i++) {
													M1 = glm::translate(M, glm::vec3(0.0f, 0.0f, i * 715.0f + 0.0f));
													for (int j = 0; j < 20 / 4; j++) {
														M1 = glm::translate(M1, glm::vec3(390.0f, 0.0f, 0.0f));
														bot[j + (i * 5)] = new Models::Bottle(idbot, M1);
													}
												}
											}
											else
												if (this->idbot == 13 || this->idbot == 15) { //Cheval Blanc i Moulin de Launay
													M = glm::rotate(M, 4.71f, glm::vec3(1.0f, 0.0f, 0.0f));
													M = glm::rotate(M, 3.14f, glm::vec3(0.0f, 0.0f, 1.0f));
													M = glm::translate(M, glm::vec3(-57.0f, 20.0f, 25.0f));
													M = glm::scale(M, glm::vec3(75.0f, 75.0f, 75.0f));

													glm::mat4 M1;
													for (int i = 0; i < 20 / (20 / 4); i++) {
														M1 = glm::translate(M, glm::vec3(0.0f, 0.0f, i * 0.476f + 0.0f));
														for (int j = 0; j < 20 / 4; j++) {
															M1 = glm::translate(M1, glm::vec3(0.26f, 0.0f, 0.0f));
															bot[j + (i * 5)] = new Models::Bottle(idbot, M1);
														}
													}
												}
												else
													if (this->idbot == 16) { //Brandy 1
														M = glm::rotate(M, 4.71f, glm::vec3(1.0f, 0.0f, 0.0f));
														M = glm::translate(M, glm::vec3(-57.0f, -20.0f, 11.0f));
														M = glm::scale(M, glm::vec3(2.5f, 2.5f, 2.5f));

														glm::mat4 M1;
														for (int i = 0; i < 20 / (20 / 4); i++) {
															M1 = glm::translate(M, glm::vec3(0.0f, 0.0f, i * 14.3f + 0.0f));
															for (int j = 0; j < 20 / 4; j++) {
																M1 = glm::translate(M1, glm::vec3(7.8f, 0.0f, 0.0f));
																bot[j + (i * 5)] = new Models::Bottle(idbot, M1);
															}
														}
													}
												else
													if (this->idbot == 17) { //Brandy 2
														//M = glm::rotate(M, 4.71f, glm::vec3(1.0f, 0.0f, 0.0f));
														M = glm::rotate(M, 1.57f, glm::vec3(0.0f, -1.0f, 0.0f));
														M = glm::translate(M, glm::vec3(20.0f, 11.0f, -57.0f));
														M = glm::scale(M, glm::vec3(2.5f, 2.5f, 2.5f));

														glm::mat4 M1;
														for (int i = 0; i < 20 / (20 / 4); i++) {
															M1 = glm::translate(M, glm::vec3(0.0f, i * 14.3f + 0.0f, 0.0f));
															for (int j = 0; j < 20 / 4; j++) {
																M1 = glm::translate(M1, glm::vec3(0.0f, 0.0f, 7.8f));
																bot[j + (i * 5)] = new Models::Bottle(idbot, M1);
															}
														}
													}
													else
														if (this->idbot == 18) { //Martini
															M = glm::rotate(M, 4.71f, glm::vec3(0.0f, 0.0f, -1.0f));
															//M = glm::rotate(M, 1.57f, glm::vec3(0.0f, 0.0f, 0.0f));
															M = glm::translate(M, glm::vec3(11.0f, -57.0f, 20.0f));
															M = glm::scale(M, glm::vec3(0.25f, 0.25f, 0.25f));

															glm::mat4 M1;
															for (int i = 0; i < 20 / (20 / 4); i++) {
																M1 = glm::translate(M, glm::vec3(i * 143.0f + 0.0f, 0.0f, 0.0f));
																for (int j = 0; j < 20 / 4; j++) {
																	M1 = glm::translate(M1, glm::vec3(0.0f, 78.0f, 0.0f));
																	bot[j + (i * 5)] = new Models::Bottle(idbot, M1);
																}
															}
														}
														else
															if (this->idbot == 19) { //Cointreau
																M = glm::rotate(M, 4.71f, glm::vec3(1.0f, 0.0f, 0.0f));
																M = glm::translate(M, glm::vec3(-57.0f, -20.0f, 11.0f));
																M = glm::scale(M, glm::vec3(2.5f, 2.5f, 2.5f));

																glm::mat4 M1;
																for (int i = 0; i < 20 / (20 / 4); i++) {
																	M1 = glm::translate(M, glm::vec3(0.0f, 0.0f, i * 14.3f + 0.0f));
																	for (int j = 0; j < 20 / 4; j++) {
																		M1 = glm::translate(M1, glm::vec3(7.8f, 0.0f, 0.0f));
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
			if(!bot[i]->drinked)
				bot[i]->draw(V);
		}
	}
}