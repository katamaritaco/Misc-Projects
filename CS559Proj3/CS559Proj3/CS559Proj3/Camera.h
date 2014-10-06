#include "glutInclude.h"
#pragma once

// A simple container class for our camera.

class Camera
{
public:
	Camera();
	~Camera();
	glm::mat4 proj; //Our projection matrix.
	glm::mat4 modelview; //Our modelview matrix.
	glm::vec3 loc; //Location of the cmaera
	glm::vec3 point; //Where we're looking at in our eyeLoc.
	float fov; //our FOV
};
