//Used to define structs for material and lighting information.
#pragma once
#include <glm/glm.hpp>

typedef struct _lightInfo {
	glm::vec4 position; 
	glm::vec3 color; //This is currently unused
	glm::vec3 amb; //Ambient component
	glm::vec3 diff; //Diffuse component
	glm::vec3 spec; //Specular component
} lightInfo;

typedef struct _materialInfo {
	glm::vec3 kA; //Ambient reflectivity
	glm::vec3 kD; //Diffuse reflectivity
	glm::vec3 kS; //Specular reflectivity
	float shininess; //Specular highlight exponent
} materialInfo;
