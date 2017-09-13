#pragma once
//#include "model.h"
#include "Shelf.h"

#include <stdio.h>
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <GLFW/glfw3.h>
#include <stdlib.h>

namespace Models {

	class Gallery : public Model{
	public:
		Shelf* shelf[28];
		Gallery(int,glm::mat4);
		~Gallery();
		void draw(glm::mat4);
	};

}
