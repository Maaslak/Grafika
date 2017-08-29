#pragma once
#include "model.h"

namespace Models {

	class Bottle : public Model {
		public:
			//virtual void drawSolid();
			Bottle(char* path, char* texpath):Model(path, texpath) {
			
		}
	};

}