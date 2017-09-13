#include "Bottle.h"
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <GLFW/glfw3.h>
#include <stdlib.h>

namespace Models {
	Bottle::Bottle(int id, glm::mat4 M) :Model(id, M) {

	}
	void Bottle::draw(glm::mat4 V) {
		//glLoadMatrixf(value_ptr(V*M));
		this->drawSolid(V);
	}


}