#pragma once
#include "model.h"

namespace Models {

	class Bottle : public Model {
	public:
		Bottle(int id, glm::mat4 M);
		void draw(glm::mat4);

	};

}

