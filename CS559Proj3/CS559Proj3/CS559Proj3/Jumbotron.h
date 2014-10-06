#pragma once
#include "Cube.h"
class Jumbotron
{
public:
	Jumbotron(void);
	~Jumbotron(void);
	void init(glm::vec3 pos, bool flipped); //"Flipped" bool renders it backwards
	bool draw(const glm::mat4 & proj, glm::mat4 mv, const glm::ivec2 & size, const float time, lightInfo * & l, materialInfo * & m);
	void TakeDown(void);
protected:
	Cube stand; //Support rod for screen; uses same shader as Spheres
	Cube screen; //The actual screen; uses an FBO
	glm::vec3 pos; //Overall position of object
	Shader * screenShader; //Shader for the screen
};

