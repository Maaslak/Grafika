#pragma once
#include "model.h"
#include "Bottle.h"
#include "Shelf.h"

namespace Models {

	class Gallery : public Model {
	public:
		char* path;
		char* texpath;
		Shelf* shelf;
		Gallery(char*, char*);
		~Gallery();
		void draw(glm::mat4, glm::mat4);
	};
}
