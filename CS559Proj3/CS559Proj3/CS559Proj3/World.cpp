#include "World.h"
#include "Cube.h"
//ASSUMPTION: THE WORLD IS 5280 x 5280 UNITS
//NOTE: That's feet.  Box2D uses meters-kilograms-seconds.  
//NOTE: We let (x,y) in box2d translate to (x, 0.0, y) in 3d.


World::World(void)
{
	is_init = false;
	return;
}

World::~World(void)
{
	//Probably want some TakeDown methods here
	return;
}

void World::switchFloorShader(bool set)
{
	stadium.switchFloorShader(set);
}

void World::TakeDown(void)
{
	if (!is_init) return;
	for (sphereIt = spheres.begin(); sphereIt < spheres.end(); sphereIt++)
	{
		(*sphereIt)->TakeDown();
		delete *sphereIt;
	}
	stadium.TakeDown();
	skydome.TakeDown();
	world->~b2World(); //Box2D implements cleanup for physics
	return;
}

void World::switchCam(void)
{
	if (this->currCam == &this->birdsEye)
	{
		this->currCam = this->player.getCam();
	}
	else
	{
		this->currCam = &this->birdsEye;
	}
}

void World::initSkyboxes(void)
{
	for (int i = 0; i < NUM_TEXTS; i++)
	{
		switch(TEXTURE_TYPE(i))
		{
		case SKY:
			skyboxes[i].l.position = glm::vec4(300.0f, 600.0f, 0.0f, 1.0f);
			skyboxes[i].l.amb = glm::vec3(0.3f, 0.3f, 0.2f);
			skyboxes[i].l.diff = glm::vec3(0.8f, 0.8f, 0.8f);
			skyboxes[i].l.spec = glm::vec3(0.9f, 0.9f, 0.9f);
			skyboxes[i].tex = SKY;
			break;
		case NIGHT_SKY:
			skyboxes[i].l.position = glm::vec4(-300.0f, 600.0f, 0.0f, 1.0f);
			skyboxes[i].l.amb = glm::vec3(0.1f, 0.1f, 0.1f);
			skyboxes[i].l.diff = glm::vec3(0.5f, 0.5f, 0.5f);
			skyboxes[i].l.spec = glm::vec3(0.7f, 0.7f, 0.7f);
			skyboxes[i].tex = NIGHT_SKY;
			break;
		default:
			skyboxes[i].tex = TEX_ERR;
			break;
		}
	}
}

bool World::init(int sphere_count)
{
	totalSpheres = sphere_count;
	if (GLReturnedError("World init - on entry")) return true;
	b2Vec2 gravity;
	gravity.Set(0.0f, 0.0f);
	bool doSleep = true;
	this->world = new b2World(gravity);
	world->SetAllowSleeping(doSleep);
	world->SetContactListener(&contactListener);
	//world->SetContinuousPhysics(true); //For testing only
	birdsEye.proj = glm::perspective(birdsEye.fov, window.aspect, 1.0f, 50000.0f); 
	birdsEye.modelview = glm::lookAt(glm::vec3(0.0f, 1000.0f, 0.0f), glm::vec3(-000.01f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	
	for (int i = 0; i < sphere_count; i++)
	{
#ifndef BOX2D_DEBUG
		Sphere * new_s = new Sphere();

		new_s->initialize(SPHERE_RADIUS, 10, 10);

		glm::vec3 spherePosForCube = glm::vec3(-WALL_LENGTH + rand() % (int) (2 * WALL_LENGTH), 0.0f, -WALL_LENGTH + rand() % (int) (2 * WALL_LENGTH));

		new_s->setPos(spherePosForCube);
		new_s->initPhysics(world); //Since this uses the inital position, must call after setPos
		
		cube.init(50.0f,50.0f,50.0f);
		cube.setPos(glm::vec3(spherePosForCube.x, 70.0f, spherePosForCube.z));		
		
		this->spheres.push_back(new_s);
#endif
	}

	skydome.initialize(5000, 50, 50);
	
	Shader * skyShader = new Shader();
	skyShader->init(TEX_NO_LIGHTING);
	skydome.setShader(skyShader);

	//DEBUG
	/*
	for (int j = -50; j < 50; j++)
	{
		Sphere new_s;
		new_s.initialize(50, 10, 10);
		new_s.setPos(glm::vec3(110.0f * j, 0.0f, 110.0f * j));
		new_s.initPhysics(world); //Since this uses the inital position, must call after setPos
		this->spheres.push_back(new_s);
//		this->spheres.push_back(new DrawObject()); //TODO: But for serious need to get a good distribution
	}*/
	this->currCam = &birdsEye;

	player.init(SPHERE_RADIUS, 10, 10, 0.0f, 0.0f);
	player.initPhysics(world);
	player.update();

	l.amb = glm::vec3(0.5, 0.5, 0.5);
	l.diff = glm::vec3(0.5, 0.5, 0.5);
	l.spec = glm::vec3(0.5, 0.5, 0.5);
	l.position = glm::vec4(200.0, 500.0, 000.0, 1.0);
	m.kA = glm::vec3(0.9f, 0.9f, 0.9f);
	m.kD = glm::vec3(0.5f, 0.5f, 0.5f);
	m.kS = glm::vec3(0.6f, 0.6f, 0.6f);
	m.shininess = 2.5f;
	
	cursor.init(glm::vec3(0.0f, 0.0f, 0.0f));

	stadium.init();
	stadium.initPhysics(world);

#ifdef BOX2D_DEBUG

	circleDef.type = b2_dynamicBody;
	circleDef.position.Set(50.0f, 50.0f);
	circleDef.bullet = true;
	circleBody = world->CreateBody(&circleDef);
	circleShape.m_p.Set(50.0f, 50.0f);
	circleShape.m_radius = 5.0f;
	circleFixtureDef.shape = &circleShape;
	circleFixtureDef.density = 1.0f;
	circleFixtureDef.friction = 0.1001f;

	circleDef2.type = b2_dynamicBody;
	circleDef2.position.Set(150.0f, 150.0f);
	circleDef2.bullet = true;
	circleBody2 = world->CreateBody(&circleDef);
	circleShape2.m_p.Set(50.0f, 50.0f);
	circleShape2.m_radius = 5.0f;
	circleFixtureDef2.shape = &circleShape;
	circleFixtureDef2.density = 1.0f;
	circleFixtureDef2.friction = 0.1001f;
	
	circleBody->CreateFixture(&circleFixtureDef);
	circleBody2->CreateFixture(&circleFixtureDef2);

#endif

	sky_index = 0;
	initSkyboxes();
	switchSkydome();
	
	dummy_gooch_shader.init(NONE);

	//We used to init common shader here - that's now done in main

	if (GLReturnedError("World init - on exit")) return false;
	is_init = true;
	return true;
}

int debug_counter = 0;

void World::switchSkydome(void)
{
	sky_index++;
	sky_index %= NUM_TEXTS;
	while (skyboxes[sky_index].tex == TEX_ERR && sky_index < NUM_TEXTS)
	{
		sky_index++;
		sky_index %= NUM_TEXTS;
	}
	if (skyboxes[sky_index].tex == TEX_ERR)
	{
		fprintf(stderr, "Warning: No good skybox texture found\n");
		return;
	}
	this->skydome.setTexture(skyboxes[sky_index].tex);
	this->l = skyboxes[sky_index].l;
}

void World::draw(bool do_physics)
{
	if (GLReturnedError("World draw - on entry")) return;
	lightInfo * new_l = &l;
	materialInfo * new_m = &m;
	Shader * common_shader_back; //Used for Gooch
	if (currCam == &birdsEye)
	{
		birdsEye.proj = glm::perspective(birdsEye.fov, window.aspect, 1.0f, 50000.0f); 
	}
	if (render_target == RENDER_FULL) 
	{
		world->Step(0.016667f, 10, 10); //TODO: Match this w/ draw rate
	}
	//Precompute some matrices for shadow maps on first pass
	if (useShadows && (render_target == RENDER_SFBO))
	{
		light_matrix = glm::lookAt(glm::vec3(l.position), glm::vec3(0.00001, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		bp_matrix = bias_matrix * currCam->proj;
	}
	if (render_target == RENDER_GOOCH)
	{
		common_shader_back = common_shader;
		common_shader = &dummy_gooch_shader;
	}

	for (sphereIt = spheres.begin(); sphereIt < spheres.end(); sphereIt++)
	{
		if (render_target == RENDER_FULL)
		{
			(*sphereIt)->updatePos(); //Update sphere's location with physics-based one
		}
		(*sphereIt)->draw(currCam->proj, currCam->modelview, glm::ivec2(1.0, 1.0), elapsed_time, new_l, new_m);
	}
	if (render_target == RENDER_FULL)
	{
		player.update();
	}
	
	cursor.draw(currCam->proj, currCam->modelview, glm::ivec2(1.0, 1.0), elapsed_time, new_l, new_m);

	
	stadium.draw(currCam->proj, currCam->modelview, glm::ivec2(1.0, 1.0), elapsed_time, new_l, new_m);


	skydome.draw(currCam->proj, currCam->modelview, glm::ivec2(1.0, 1.0), elapsed_time, new_l, new_m);

	player.draw(currCam->proj, currCam->modelview, glm::ivec2(1.0, 1.0), elapsed_time, new_l, new_m);
#ifdef BOX2D_DEBUG
		printf("x: %f, y: %f, q: %f\n", circleBody->GetPosition().x, circleBody->GetPosition().y, circleBody->GetAngle());
		printf("x: %f, y: %f, q: %f\n\n", circleBody2->GetPosition().x, circleBody2->GetPosition().y, circleBody->GetAngle());
#endif
	debug_counter++;
	if (debug_counter % 10000 == 0)
	{
		printf("Stop! 10000 passed.\n");
		world->Dump();
	}
	if (render_target == RENDER_GOOCH)
	{
		common_shader = common_shader_back;
	}
	if (GLReturnedError("World draw - on exit")) return;
}