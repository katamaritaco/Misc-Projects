//The base area for our game.
//COMPRISED OF:
//A floor
//Four walls
//Two pillars with screens

//The position of the stadium is fixed at 0,0.
//We translate our cubes, then scale them appopriately.
#include "glutInclude.h"
#include "Cube.h"
#include <vector>
#include "Sphere.h"
#include "Jumbotron.h"
#include "FireShader.h"

#pragma once
class Stadium
{
public:
	Stadium(void);
	~Stadium(void);
	void init();
	bool draw(const glm::mat4 & proj, glm::mat4 mv, const glm::ivec2 & size, const float time, lightInfo * & l, materialInfo * & m);
	void initPhysics(b2World * world); //Set up our Box2D objects
	void switchFloorShader(bool set); //Adjusts shader used for floor
	void TakeDown(void);
protected:
	Cube wall_one;
	Cube wall_two;
	Cube wall_three;
	Cube wall_four; //NOTE: These actually don't have Box2D equivalents; we define a single 'boundary'
	Cube floor;
	Jumbotron screen_one;
	Jumbotron screen_two;
	Jumbotron screen_three;
	Jumbotron screen_four;
	b2Body* ground; //Used to define boundary of stadium
};

