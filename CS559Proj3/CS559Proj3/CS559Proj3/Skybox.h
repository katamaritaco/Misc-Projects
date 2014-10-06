#pragma once
#include "DrawObject.h"
#include "glutInclude.h"

//The Skybox class is actually a bit of a misnomer;
//it's a skydome based off our sphere class.

typedef DrawObject super;

class Skybox :
	public DrawObject
{
public:
	Skybox(void);
	~Skybox(void);
	bool draw(const glm::mat4 & proj, glm::mat4 mv, const glm::ivec2 & size, const float time, lightInfo * & l, materialInfo * & m);
	bool initialize(float radius, int slices, int stacks);

	inline float getRadius() { return own_radius; }
	inline void setColor(glm::vec4 new_colors[2]) { colors[0] = new_colors[0]; colors[1] = new_colors[1]; custom_colors = true; }


private:
	
	float own_radius; //Allow this to be variable in case we want to adjust spheres
	glm::vec4 colors[2]; //Unused carryover from Sphere class
	bool solidColor; //Unused carryover from Sphere class
	void BuildNormalVisualizationGeometry();

	bool custom_colors; //Unused carryover from Sphere class

};

