#pragma once
//#include "model.h"
#include "Bottle.h"

namespace Models {

	class Shelf : public Model {
	public:
		//char* path;
		//char* texpath;
		Bottle* bot[20];
		Shelf(int);
		~Shelf();
		void draw(glm::mat4, glm::mat4);
	};
}
