#define GLM_FORCE_RADIANS

#include <stdio.h>
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include "lodepng.h"
//#include "constants.h"
//#include "allmodels.h"
//#include "model.h"
#include "Gallery.h"
//#include "myCube.h"

//#include <vector>




float aspect = 1.0f; //Aktualny stosunek szerokoœci do wysokoœci okna
float speed_x = 0; //Szybkoœæ k¹towa obrotu obiektu w radianach na sekundê wokó³ osi x

float speed_y = 0; //Szybkoœæ k¹towa obrotu obiektu w radianach na sekundê wokó³ osi y
//const int ilosc = 100;

//std::vector <mod> models;


//mod temp;

char* ksztalty[] = { "Gallery/galeria1.obj","Shelf/shelf.obj" ,"Corona/corona.obj"};

char* tekstury[] = { "Gallery/podloga.png","Shelf/oak.png","Corona/corona.png"};

				   // camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 deltacameraPos = glm::vec3(0.0f, 0.0f, 0.0f);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

//Models::Shelf* shelf[100];
//Models::Shelf* shelf;
//Models::Bottle* bot;
//Models::Bottle* bot[ilosc];
Models::Gallery* gallery;


void displayFrame() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}





void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

//Procedura ob³ugi zmiany rozmiaru bufora ramki
void windowResize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height); //Obraz ma byæ generowany w oknie o tej rozdzielczoœci
	aspect = (float)width / (float)height; //Stosunek szerokoœci do wysokoœci okna
}

//Procedura obs³ugi klawiatury
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT) speed_y = PI / 2;
		if (key == GLFW_KEY_RIGHT) speed_y = -PI / 2;
		if (key == GLFW_KEY_UP) speed_x = PI / 2;
		if (key == GLFW_KEY_DOWN) speed_x = -PI / 2;
	}

	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_LEFT) speed_y = 0;
		if (key == GLFW_KEY_RIGHT) speed_y = 0;
		if (key == GLFW_KEY_UP) speed_x = 0;
		if (key == GLFW_KEY_DOWN) speed_x = 0;
	}

	deltacameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	float cameraSpeed = 10.0f * glfwGetTime();

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 deltacameraPos+= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		deltacameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		deltacameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		deltacameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
  
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}  

//Procedura inicjuj¹ca
void initOpenGLProgram(GLFWwindow* window) {
	//************Tutaj umieszczaj kod, który nale¿y wykonaæ raz, na pocz¹tku programu************
	glfwSetFramebufferSizeCallback(window, windowResize); //Zarejestruj procedurê obs³ugi zmiany rozdzielczoœci bufora ramki
	
	glfwSetKeyCallback(window, key_callback); //Zarejestruj procedurê obs³ugi klawiatury
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glClearColor(0, 0, 0, 1); //Ustaw kolor czyszczenia ekranu

							  //glEnable(GL_LIGHTING); //W³¹cz tryb cieniowania
	glEnable(GL_LIGHT0); //W³¹cz zerowe Ÿród³o œwiat³a
	glEnable(GL_DEPTH_TEST); //W³¹cz u¿ywanie budora g³êbokoœci
	glEnable(GL_COLOR_MATERIAL); //W³¹cz œledzenie kolorów przez materia³
	glEnable(GL_TEXTURE_2D);

	
	//bot = new Models::Bottle
	//("room/OBJ/Room.obj", "Corona/Great Hall/3bbce3da.png");
	//("can/can.obj", "Corona/BotellaText.png");
	//("Corona/Corona.obj", "Corona/BotellaText.png");
	//("Corona/can/can_reducedfaces_repaired.obj", "Corona/BotellaText.png");
	//("eb_metal_shelf_01/eb_metal_shelf_02.obj", "Corona/Great Hall/3bbce3da.png");
	//("Corona/Great Hall/Great Hall Model.obj", "Corona/Great Hall/3bbce3da.png");
	
	/*for (int i = 0; i < 1; i++) {
		shelf[i] = new Models::Shelf
		("Corona/eb_metal_shelf_02.obj", "Corona/White Wood.png");
	}*/
	//shelf = new Models::Shelf
	//("Corona/eb_metal_shelf_02.obj", "Corona/White Wood.png");
	
	
	/*for (int i = 0; i < ilosc; i++) {
		bot[i] = new Models::Bottle("Corona/Corona.obj", "Corona/BotellaText.png");
	}*/

		//gallery = new Models::Gallery("Corona/galeria.obj", "Corona/BotellaText.png");
	for (int id = 0; id < 3; id++) {

		if (tekstury[id] != NULL)
			if (lodepng::decode(Models::Model::models[id].lode.data, Models::Model::models[id].lode.width, Models::Model::models[id].lode.height, tekstury[id]))
				cout << "Unable to load texture from" << ksztalty[id];
			else {
				glGenTextures(1, &Models::Model::models[id].lode.tex);
				glBindTexture(GL_TEXTURE_2D, Models::Model::models[id].lode.tex);
				glTexImage2D(GL_TEXTURE_2D, 0, 4, Models::Model::models[id].lode.width, Models::Model::models[id].lode.height, 0,
					GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)(Models::Model::models[id].lode.data.data()));
			}

			obj_scene_data data;
			if (!parse_obj_scene(&data, ksztalty[id]))	//loadOBJ "Corona/Corona.obj"
				throw EXCEPTION_BREAKPOINT;
			Models::Model::models[id].isdynamic = true;
			if (data.face_list[0]->vertex_count == 3) {
				Models::Model::models[id].vertexCount = 3 * data.face_count;
				Models::Model::models[id].vertices = new float[9 * data.face_count];
				Models::Model::models[id].texCoords = new float[9 * data.face_count];
				Models::Model::models[id].normals = new float[9 * data.face_count];
				for (unsigned int i = 0; i < data.face_count; i++)
				{
					for (unsigned int j = 0; j < 3; j++)
					{
						Models::Model::models[id].vertices[i * 9 + j * 3] = data.vertex_list[(data.face_list[i]->vertex_index)[j]]->e[0];
						Models::Model::models[id].vertices[i * 9 + j * 3 + 1] = data.vertex_list[(data.face_list[i]->vertex_index)[j]]->e[1];
						Models::Model::models[id].vertices[i * 9 + j * 3 + 2] = data.vertex_list[(data.face_list[i]->vertex_index)[j]]->e[2];

						if (data.vertex_texture_count != 0 && (data.face_list[i]->texture_index)[0] != -1) {
							Models::Model::models[id].texCoords[i * 9 + j * 3] = data.vertex_texture_list[(data.face_list[i]->texture_index)[j]]->e[0];
							Models::Model::models[id].texCoords[i * 9 + j * 3 + 1] = 1.0f - data.vertex_texture_list[(data.face_list[i]->texture_index)[j]]->e[1];
							Models::Model::models[id].texCoords[i * 9 + j * 3 + 2] = data.vertex_texture_list[(data.face_list[i]->texture_index)[j]]->e[2];
						}
						if (data.vertex_normal_count != 0) {
							Models::Model::models[id].normals[i * 9 + j * 3] = data.vertex_normal_list[(data.face_list[i]->normal_index)[j]]->e[0];
							Models::Model::models[id].normals[i * 9 + j * 3 + 1] = -data.vertex_normal_list[(data.face_list[i]->normal_index)[j]]->e[1];
							Models::Model::models[id].normals[i * 9 + j * 3 + 2] = data.vertex_normal_list[(data.face_list[i]->normal_index)[j]]->e[2];
						}

					}
				}
			}
			if (data.face_list[0]->vertex_count == 4) {
				Models::Model::models[id].istriangle = false;
				Models::Model::models[id].vertexCount = data.face_count;
				Models::Model::models[id].vertices = new float[12 * data.face_count];
				Models::Model::models[id].texCoords = new float[12 * data.face_count];
				Models::Model::models[id].normals = new float[12 * data.face_count];
				for (unsigned int i = 0; i < data.face_count; i++)
				{
					for (unsigned int j = 0; j < 4; j++)
					{
						Models::Model::models[id].vertices[i * 12 + j * 3] = data.vertex_list[(data.face_list[i]->vertex_index)[j]]->e[0];
						Models::Model::models[id].vertices[i * 12 + j * 3 + 1] = data.vertex_list[(data.face_list[i]->vertex_index)[j]]->e[1];
						Models::Model::models[id].vertices[i * 12 + j * 3 + 2] = data.vertex_list[(data.face_list[i]->vertex_index)[j]]->e[2];

						if (data.vertex_texture_count != 0 && (data.face_list[i]->texture_index)[0] != -1) {
							Models::Model::models[id].texCoords[i * 12 + j * 3] = data.vertex_texture_list[(data.face_list[i]->texture_index)[j]]->e[0];
							Models::Model::models[id].texCoords[i * 12 + j * 3 + 1] = 1.0f - data.vertex_texture_list[(data.face_list[i]->texture_index)[j]]->e[1];
							Models::Model::models[id].texCoords[i * 12 + j * 3 + 2] = data.vertex_texture_list[(data.face_list[i]->texture_index)[j]]->e[2];
						}
						if (data.vertex_normal_count != 0) {
							Models::Model::models[id].normals[i * 12 + j * 3] = data.vertex_normal_list[(data.face_list[i]->normal_index)[j]]->e[0];
							Models::Model::models[id].normals[i * 12 + j * 3 + 1] = -data.vertex_normal_list[(data.face_list[i]->normal_index)[j]]->e[1];
							Models::Model::models[id].normals[i * 12 + j * 3 + 2] = data.vertex_normal_list[(data.face_list[i]->normal_index)[j]]->e[2];
						}
					}
				}
			}
			//Models::Model::models.push_back(temp);
	}
	//Models::Model::models = models;
	gallery = new Models::Gallery(0);
	/*for (int i = 0; i < 100; i++) {
		shelf[i] = new Models::Shelf(1);
	}*/

}




//Procedura rysuj¹ca zawartoœæ sceny
void drawScene(GLFWwindow* window, float angle_x, float angle_y, glm::mat4 M) {
	//************Tutaj umieszczaj kod rysuj¹cy obraz******************l

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wyczyœæ bufor kolorów (czyli przygotuj "p³ótno" do rysowania)

														//***Przygotowanie do rysowania****
	glm::mat4 P = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 V = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	/*lookAt( //Wylicz macierz widoku
		vec3(0.0f, 0.0f, -5.0f),
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f));*/
	glMatrixMode(GL_PROJECTION); //W³¹cz tryb modyfikacji macierzy rzutomainwania
	glLoadMatrixf(value_ptr(P)); //Za³aduj macierz rzutowania
	glMatrixMode(GL_MODELVIEW);  //W³¹cz tryb modyfikacji macierzy model-widok


								 //Rysowanie kostki
								 //1. Wyliczenie i za³adowanie macierzy modelu
	//glm::mat4 M = glm::mat4(1.0f);
	//M = glm::rotate(M, 5.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	M = glm::rotate(M, angle_x, glm::vec3(1.0f, 0.0f, 0.0f));
	M = glm::rotate(M, angle_y, glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::scale(M, glm::vec3(0.2f, 0.2f, 0.2f));
	glLoadMatrixf(value_ptr(V*M));

	

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/*for (int i = 0; i < 100; i++) {
		shelf[i]->draw(V, M);
		M = glm::translate(M, glm::vec3(120.0f, 0.0f, 0.0f));
		glLoadMatrixf(value_ptr(V*M));
	}*/
	//shelf->draw(V, M);

	M = glm::translate(M, glm::vec3(0.0f, 80.0f, 0.0f));
	glLoadMatrixf(value_ptr(V*M));
	gallery->draw(V,M);
	//shelf->draw(V, M);

	//bot->drawSolid();
	
	//glm::mat4 M1;
	/*int sciana[3];
	sciana[1] = ilosc / 5 * 2;
	sciana[2] = ilosc / 5;
	sciana[3] = ilosc / 5 * 2;*/
	/*for (int i = 0; i < ilosc/(ilosc/4); i++) {
		M1 = glm::translate(M, glm::vec3(0.0f, 0.0f, i * (-50) + 0.0f));
		for (int j = 0; j < ilosc/4; j++) {
			M1 = glm::translate(M1, glm::vec3(0.0f, 20.0f, 0.0f));
			glLoadMatrixf(value_ptr(V*M1));
			bot[i]->drawSolid();
			
		}
	}*/

/*	for (int i = 0; i < sciana[2] / (sciana[2] / 4); i++) {
		M1 = glm::translate(M, glm::vec3(0.0f, sciana[1]*5+0.0f, i * (-50) + 0.0f));
		for (int j = 0; j < sciana[2] / 4; j++) {
			M1 = glm::translate(M1, glm::vec3(-20.0f, 0.0f, 0.0f));
			glLoadMatrixf(value_ptr(V*M1));
			bot[sciana[1]+i]->drawSolid();

		}
	}

	for (int i = 0; i < sciana[3] / (sciana[3] / 4); i++) {
		M1 = glm::translate(M, glm::vec3(sciana[2]*5+0.0f, sciana[1] * 5 + 0.0f, i * (-50) + 0.0f));
		for (int j = 0; j < sciana[3] / 4; j++) {
			M1 = glm::translate(M1, glm::vec3(0.0f, 0.0f, -20.0f));
			glLoadMatrixf(value_ptr(V*M1));
			bot[sciana[1]+sciana[2] + i]->drawSolid();

		}
	}
	*/

	glfwSwapBuffers(window); //Przerzuæ tylny bufor na przedni
}



int main(void)
 {
	GLFWwindow* window; //WskaŸnik na obiekt reprezentuj¹cy okno
	
	glfwSetErrorCallback(error_callback);//Zarejestruj procedurê obs³ugi b³êdów

	if (!glfwInit()) { //Zainicjuj bibliotekê GLFW
		fprintf(stderr, "Nie mo¿na zainicjowaæ GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Galeria alkoholi", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Je¿eli okna nie uda³o siê utworzyæ, to zamknij program
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje siê aktywny i polecenia OpenGL bêd¹ dotyczyæ w³aœnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	GLenum err;
	if ((err = glewInit()) != GLEW_OK) { //Zainicjuj bibliotekê GLEW
		fprintf(stderr, "Nie mo¿na zainicjowaæ GLEW: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjuj¹ce


	float angle_x = 0.0f; //Aktualny k¹t obrotu obiektu wokó³ osi x
	float angle_y = 0.0f; //Aktualny k¹t obrotu obiektu wokó³ osi y
	glfwSetTime(0); //Wyzeruj timer

	glm::mat4 M = glm::mat4(1.0f);
	//M = glm::rotate(M, 3.14f, glm::vec3(1.0f, 0.0f, 0.0f));
	M = glm::translate(M, glm::vec3(0.0f, -10.0f, -20.0f));
					//G³ówna pêtla
	while (!glfwWindowShouldClose(window)) //Tak d³ugo jak okno nie powinno zostaæ zamkniête
	{
		//angle_x += speed_x*glfwGetTime(); //Oblicz przyrost k¹ta obrotu i zwiêksz aktualny k¹t
		//angle_y += speed_y*glfwGetTime(); //Oblicz przyrost k¹ta obrotu i zwiêksz aktualny k¹t
		glfwSetTime(0); //Wyzeruj timer
		drawScene(window, angle_x, angle_y,M); //Wykonaj procedurê rysuj¹c¹
		glfwPollEvents(); //Wykonaj procedury callback w zaleznoœci od zdarzeñ jakie zasz³y.
		glfwSetCursorPosCallback(window, mouse_callback);
		cameraPos += deltacameraPos;

	}

	delete(gallery);
	glfwDestroyWindow(window); //Usuñ kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajête przez GLFW
	exit(EXIT_SUCCESS);
}




/*int main(int argc, char** argv) {
	initializeGLUT(&argc, argv);
	initializeGLEW();
	//Kod inicjuj¹cy tutaj
	glutMainLoop();
	//Kod zwalniaj¹cy zasoby tutaj
}*/
