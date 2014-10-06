#pragma once
#include <vector>
#include <random>
#include "PhysicsInclude.h"
#include "glutInclude.h"
#include "Stadium.h"
#include "DrawObject.h"
#include "Camera.h"
#include "Player.h"
#include "Sphere.h"
#include "MaterialInfo.h"
#include "ContactListener.h"
#include "Cursor.h"
#include "Cube.h"
#include "Skybox.h"
//#define BOX2D_DEBUG

class World
{
public:
	World(void);
	~World(void);
	bool init(int spheres); //Should we specify stacks/slices?
	void draw(bool do_physics); //Draw our world and possibly simulate physics
	void switchCam(void); //Switch from overhead view to first-person view
	inline Camera * getCurrentCam(void) { return this->currCam; }
	inline Player * getPlayer(void) { return &this->player; }
	void switchSkydome(void);
	void switchFloorShader(bool set);
	void TakeDown(void);

	int totalSpheres;

private:
	void initSkyboxes(void);
	vector<Sphere *> spheres; // Keeps track of all our spheres in the world
	std::vector<Sphere *>::iterator sphereIt; //Lets us move through the spheres and draw them

	Camera * currCam; // Points to the camera we're using
	Player player; // Our player object
	Camera birdsEye; // Camera situated above the world
	
	Cursor cursor; //Our cursor
	Cube cube; //Used in Box2D debugging
	
	Stadium stadium; // Our playing field
	glm::mat4 baseMv; // Base modelview for our world
	lightInfo l; //Light for our world
	materialInfo m; //Material for our world
	ContactListener contactListener; //Deals with collisions
	Skybox skydome; // Our skydome
	// The camera for the player is in the Player class

	//Our various skybox configs
	skyboxInfo skyboxes[NUM_TEXTS];
	int sky_index;
	
	Shader dummy_gooch_shader; //Used for Gooch outlines

	bool is_init; //Helps us in takedown

	//BOX2D INFO
	b2World * world; //Our world; have as pointer because there's no default constructor

};