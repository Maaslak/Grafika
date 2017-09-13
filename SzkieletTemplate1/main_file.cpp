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




float aspect = 1.0f; //Aktualny stosunek szeroko�ci do wysoko�ci okna
float speed_x = 0; //Szybko�� k�towa obrotu obiektu w radianach na sekund� wok� osi x

float speed_y = 0; //Szybko�� k�towa obrotu obiektu w radianach na sekund� wok� osi y
//const int ilosc = 100;

//std::vector <mod> models;


//mod temp;

char* ksztalty[] = { "Gallery/Gallery.obj","Shelf/shelf.obj" ,"Corona/corona.obj" ,"ButelkiNew/szampan/moet/SimpleMoet.obj" ,
	"ButelkiNew/absolut vodka/SimpleAbsolutTest.obj" ,"ButelkiNew/chivas regal (whisky)/Chivas.obj",  
	"ButelkiNew/beer/heineken/SimpleHeinekenTest.obj", "ButelkiNew/Screaming Eagle/SimpleScreamingEagle.obj",
	"ButelkiNew/les hauts de lynch/SimpleLesHauts.obj" ,"ButelkiNew/Turnbull's (whisky)/SimpleTurnbull's.obj", "ButelkiNew/napoleon/SimpleNapoleon.obj" };

char* tekstury[] = { "Gallery/cegla1.png","Shelf/polka.png" ,"Corona/corona.png" ,"ButelkiNew/szampan/moet/texture.png" ,
	"ButelkiNew/absolut vodka/texture.png" ,"ButelkiNew/chivas regal (whisky)/texture.png", 
	"ButelkiNew/beer/heineken/texture.png", "ButelkiNew/Screaming Eagle/texture.png",
	"ButelkiNew/les hauts de lynch/texture.png", "ButelkiNew/Turnbull's (whisky)/texture.png" ,"ButelkiNew/napoleon/texture.png" };

				   // camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 deltacameraPos = glm::vec3(0.0f, 0.0f, 0.0f);

int n = 0;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

Models::Gallery* gallery;
//Models::Shelf* shelf;
//Models::Bottle* bot;


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
	float cameraSpeed = 2.0f * glfwGetTime();

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

//Procedura inicjuj�ca
void initOpenGLProgram(GLFWwindow* window) {
	//************Tutaj umieszczaj kod, kt�ry nale�y wykona� raz, na pocz�tku programu************
	glfwSetFramebufferSizeCallback(window, windowResize); //Zarejestruj procedur� obs�ugi zmiany rozdzielczo�ci bufora ramki
	
	glfwSetKeyCallback(window, key_callback); //Zarejestruj procedur� obs�ugi klawiatury
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glClearColor(0, 0, 0, 1); //Ustaw kolor czyszczenia ekranu

							  //glEnable(GL_LIGHTING); //W��cz tryb cieniowania
	glEnable(GL_LIGHT0); //W��cz zerowe �r�d�o �wiat�a
	glEnable(GL_DEPTH_TEST); //W��cz u�ywanie budora g��boko�ci
	glEnable(GL_COLOR_MATERIAL); //W��cz �ledzenie kolor�w przez materia�
	glEnable(GL_TEXTURE_2D);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	//glFrontFace(GL_CCW);
	
	for (int id = 0; id < 11; id++) {

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
	}

	glm::mat4 M = glm::mat4(1.0f);
	M = glm::scale(M, glm::vec3(0.2f, 0.2f, 0.2f));
	//M = glm::scale(M, glm::vec3(0.02f, 0.02f, 0.02f));
	M = glm::rotate(M, 1.57f, glm::vec3(-1.0f, 0.0f, 0.0f));
	M = glm::rotate(M, 1.57f, glm::vec3(0.0f, 0.0f, -1.0f));
	gallery = new Models::Gallery(0,M);

	//shelf = new Models::Shelf(1,9);
	//bot = new Models::Bottle(5);

}




//Procedura rysuj�ca zawarto�� sceny
void drawScene(GLFWwindow* window, float angle_x, float angle_y) {
	//************Tutaj umieszczaj kod rysuj�cy obraz******************l

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wyczy�� bufor kolor�w (czyli przygotuj "p��tno" do rysowania)

														//***Przygotowanie do rysowania****
	glm::mat4 P = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 V = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	//Models::Model::V = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	/*lookAt( //Wylicz macierz widoku
		vec3(0.0f, 0.0f, -5.0f),
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f));*/
	glMatrixMode(GL_PROJECTION); //W��cz tryb modyfikacji macierzy rzutomainwania
	glLoadMatrixf(value_ptr(P)); //Za�aduj macierz rzutowania
	glMatrixMode(GL_MODELVIEW);  //W��cz tryb modyfikacji macierzy model-widok

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	gallery->draw(V);
	

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
		//angle_x += speed_x*glfwGetTime(); //Oblicz przyrost k�ta obrotu i zwi�ksz aktualny k�t
		//angle_y += speed_y*glfwGetTime(); //Oblicz przyrost k�ta obrotu i zwi�ksz aktualny k�t
		glfwSetTime(0); //Wyzeruj timer
		drawScene(window, angle_x, angle_y); //Wykonaj procedur� rysuj�c�
		glfwPollEvents(); //Wykonaj procedury callback w zalezno�ci od zdarze� jakie zasz�y.
		glfwSetCursorPosCallback(window, mouse_callback);
		cameraPos += deltacameraPos;

	}

	delete(gallery);
	//delete(shelf);
	//delete(bot);
	glfwDestroyWindow(window); //Usu� kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zaj�te przez GLFW
	exit(EXIT_SUCCESS);
}