#pragma once
#include "Cube.h"

//A class for drawing a basic cursor
class Cursor
{
public:
	Cursor(void);
	~Cursor(void);
void init(glm::vec3 pos); 
	bool draw(const glm::mat4 & proj, glm::mat4 mv, const glm::ivec2 & size, const float time, lightInfo * & l, materialInfo * & m);
	void TakeDown(void);
protected:
	Cube textureCursor;
	glm::vec3 pos;
};

