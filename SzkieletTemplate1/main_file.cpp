#define GLM_FORCE_RADIANS

#include <stdio.h>
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include "lodepng.h"
#include "constants.h"
#include "allmodels.h"
#include "myCube.h"




using namespace glm;

float aspect = 1.0f; //Aktualny stosunek szeroko�ci do wysoko�ci okna
float speed_x = 0; //Szybko�� k�towa obrotu obiektu w radianach na sekund� wok� osi x
float speed_y = 0; //Szybko�� k�towa obrotu obiektu w radianach na sekund� wok� osi y

				   // camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 deltacameraPos = glm::vec3(0.0f, 0.0f, 0.0f);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Models::Bottle* bot;


void displayFrame() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}





void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

//Procedura ob�ugi zmiany rozmiaru bufora ramki
void windowResize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height); //Obraz ma by� generowany w oknie o tej rozdzielczo�ci
	aspect = (float)width / (float)height; //Stosunek szeroko�ci do wysoko�ci okna
}

//Procedura obs�ugi klawiatury
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
	float cameraSpeed = 2.5 * glfwGetTime();

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 deltacameraPos+= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		deltacameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		deltacameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		deltacameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

//Procedura inicjuj�ca
void initOpenGLProgram(GLFWwindow* window) {
	//************Tutaj umieszczaj kod, kt�ry nale�y wykona� raz, na pocz�tku programu************
	glfwSetFramebufferSizeCallback(window, windowResize); //Zarejestruj procedur� obs�ugi zmiany rozdzielczo�ci bufora ramki
	glfwSetKeyCallback(window, key_callback); //Zarejestruj procedur� obs�ugi klawiatury

	glClearColor(0, 0, 0, 1); //Ustaw kolor czyszczenia ekranu

							  //glEnable(GL_LIGHTING); //W��cz tryb cieniowania
	glEnable(GL_LIGHT0); //W��cz zerowe �r�d�o �wiat�a
	glEnable(GL_DEPTH_TEST); //W��cz u�ywanie budora g��boko�ci
	glEnable(GL_COLOR_MATERIAL); //W��cz �ledzenie kolor�w przez materia�
	glEnable(GL_TEXTURE_2D);


	bot = new Models::Bottle("Corona/Corona.obj", "Corona/BotellaText.png");
}

//Procedura rysuj�ca zawarto�� sceny
void drawScene(GLFWwindow* window, float angle_x, float angle_y) {
	//************Tutaj umieszczaj kod rysuj�cy obraz******************l

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wyczy�� bufor kolor�w (czyli przygotuj "p��tno" do rysowania)

														//***Przygotowanie do rysowania****
	mat4 P = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	mat4 V = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp); 
	/*lookAt( //Wylicz macierz widoku
		vec3(0.0f, 0.0f, -5.0f),
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f));*/
	glMatrixMode(GL_PROJECTION); //W��cz tryb modyfikacji macierzy rzutomainwania
	glLoadMatrixf(value_ptr(P)); //Za�aduj macierz rzutowania
	glMatrixMode(GL_MODELVIEW);  //W��cz tryb modyfikacji macierzy model-widok


								 //Rysowanie kostki
								 //1. Wyliczenie i za�adowanie macierzy modelu
	mat4 M = mat4(1.0f);
	M = rotate(M, angle_x, vec3(1.0f, 0.0f, 0.0f));
	M = rotate(M, angle_y, vec3(0.0f, 1.0f, 0.0f));
	M = scale(M, vec3(0.1f, 0.1f, 0.1f));
	glLoadMatrixf(value_ptr(V*M));
	

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	bot->drawSolid();


	glfwSwapBuffers(window); //Przerzu� tylny bufor na przedni
}





int main(void)
 {
	GLFWwindow* window; //Wska�nik na obiekt reprezentuj�cy okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedur� obs�ugi b��d�w

	if (!glfwInit()) { //Zainicjuj bibliotek� GLFW
		fprintf(stderr, "Nie mo�na zainicjowa� GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Galeria alkoholi", NULL, NULL);  //Utw�rz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Je�eli okna nie uda�o si� utworzy�, to zamknij program
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje si� aktywny i polecenia OpenGL b�d� dotyczy� w�a�nie jego.
	glfwSwapInterval(1); //Czekaj na 1 powr�t plamki przed pokazaniem ukrytego bufora

	GLenum err;
	if ((err = glewInit()) != GLEW_OK) { //Zainicjuj bibliotek� GLEW
		fprintf(stderr, "Nie mo�na zainicjowa� GLEW: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjuj�ce


	float angle_x = 0.0f; //Aktualny k�t obrotu obiektu wok� osi x
	float angle_y = 0.0f; //Aktualny k�t obrotu obiektu wok� osi y
	glfwSetTime(0); //Wyzeruj timer

					//G��wna p�tla
	while (!glfwWindowShouldClose(window)) //Tak d�ugo jak okno nie powinno zosta� zamkni�te
	{
		angle_x += speed_x*glfwGetTime(); //Oblicz przyrost k�ta obrotu i zwi�ksz aktualny k�t
		angle_y += speed_y*glfwGetTime(); //Oblicz przyrost k�ta obrotu i zwi�ksz aktualny k�t
		glfwSetTime(0); //Wyzeruj timer
		drawScene(window, angle_x, angle_y); //Wykonaj procedur� rysuj�c�
		glfwPollEvents(); //Wykonaj procedury callback w zalezno�ci od zdarze� jakie zasz�y.
		cameraPos += deltacameraPos;
	}

	delete(bot);
	glfwDestroyWindow(window); //Usu� kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zaj�te przez GLFW
	exit(EXIT_SUCCESS);
}




/*int main(int argc, char** argv) {
	initializeGLUT(&argc, argv);
	initializeGLEW();
	//Kod inicjuj�cy tutaj
	glutMainLoop();
	//Kod zwalniaj�cy zasoby tutaj
}*/
