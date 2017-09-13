#pragma once
//#include "model.h"
#include "Bottle.h"

namespace Models {

	class Shelf : public Model {
	public:
		Bottle* bot[20];
		int idbot;
		Shelf(int,int,glm::mat4);
		~Shelf();
		void draw(glm::mat4);
	};
}
