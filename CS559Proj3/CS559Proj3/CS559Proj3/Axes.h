#pragma once
#include "DrawObject.h"

//A special DrawObject that draws the local axes.

class Axes :
	public DrawObject
{
public:
	Axes(void);
	~Axes(void);
	bool draw(const glm::mat4 & proj, glm::mat4 mv, const glm::ivec2 & size, const float time, lightInfo * & l); 
	bool init(void);
};

