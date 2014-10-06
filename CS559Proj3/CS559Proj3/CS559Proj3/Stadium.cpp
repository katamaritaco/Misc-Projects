#include "Stadium.h"

Stadium::Stadium(void)
{
}

#define FLOOR_DEPTH -(SPHERE_RADIUS)

void Stadium::TakeDown(void)
{
	//Need to specifically take care of the walls' shader because it's shared
	Shader * wall_shader = wall_one.getShader();
	wall_shader->TakeDown();
	if (wall_shader != NULL)
	{
		free(wall_shader);
	}
	wall_one.setShader(NULL);
	wall_two.setShader(NULL);
	wall_three.setShader(NULL);
	wall_four.setShader(NULL);

	wall_one.TakeDown();
	wall_two.TakeDown();
	wall_three.TakeDown();
	wall_four.TakeDown();
	floor.TakeDown();

	screen_one.TakeDown();
	screen_two.TakeDown();
	screen_three.TakeDown();
	screen_four.TakeDown();
}

void Stadium::switchFloorShader(bool set)
{
	floor.toggleShader(set);
}

void Stadium::init(void)
{
	if (GLReturnedError("Stadium init - on entry")) return;
	
	ShaderWithShadows * s = new ShaderWithShadows(); //Always use default for walls
	s->init(TEX_W_SHADOWS);
	wall_one.init(1.0f, WALL_HEIGHT, 2 * WALL_LENGTH);

	wall_one.setPos(glm::vec3(WALL_LENGTH, FLOOR_DEPTH, -WALL_LENGTH));
	wall_one.setShader(s);
	wall_one.toggleTiling(true);
	wall_two.init(1.0f, WALL_HEIGHT, 2 * WALL_LENGTH);
	wall_two.setPos(glm::vec3(-WALL_LENGTH, FLOOR_DEPTH, -WALL_LENGTH));
	wall_two.setShader(s);
	wall_two.toggleTiling(true);
	wall_three.init(2 * WALL_LENGTH, WALL_HEIGHT, 1.0f);
	wall_three.setPos(glm::vec3(-WALL_LENGTH, FLOOR_DEPTH, WALL_LENGTH));
	wall_three.setShader(s);
	wall_three.toggleTiling(true);
	wall_four.init(2 * WALL_LENGTH, WALL_HEIGHT, 1.0f);
	wall_four.setPos(glm::vec3(-WALL_LENGTH, FLOOR_DEPTH, -WALL_LENGTH));
	wall_four.setShader(s);
	wall_four.toggleTiling(true);
	floor.init(2 * WALL_LENGTH, 1.0f, 2 * WALL_LENGTH);
	floor.setPos(glm::vec3(-WALL_LENGTH, FLOOR_DEPTH, -WALL_LENGTH));
	floor.toggleTiling(true);

	FireShader * floor_s = new FireShader();
	floor_s->init(NOISE_NORMAL);
	floor.setShader(floor_s); 

	screen_one.init(glm::vec3(WALL_LENGTH + 1.1f, 0.0f, 1.0f), false);
	screen_two.init(glm::vec3(WALL_LENGTH + 1.1f, 0.0f, 1.0f), false);
	screen_three.init(glm::vec3(WALL_LENGTH + 1.1f, 0.0f, 1.0f), false);
	screen_four.init(glm::vec3(WALL_LENGTH + 1.1f, 0.0f, 1.0f), false);
	if (GLReturnedError("Stadium init - on exit")) return;
}

void Stadium::initPhysics(b2World * world) //Set up our Box2D object
{
	/*
	wall_one.initPhysics(2640.0f, glm::vec2(2640.0f, 0.0f), degToRad(90.0f), world);
	wall_two.initPhysics(2640.0f, glm::vec2(-2640.0f, 0.0f), degToRad(90.0f), world);
	wall_three.initPhysics(2640.0f, glm::vec2(0.0f, 2640.0f), 0.0f, world);
	wall_four.initPhysics(2640.0f, glm::vec2(0.0f, -2640.0f), 0.0f, world);
	*/

	//Let's try an edge chain instead.
	//FROM THE BOX2D PINBALL TEST
	
	/*
		Sphere bl;
	bl.initialize(50, 10, 10);
	bl.setPos(glm::vec3(-2640.0f, 0.0f, -2640.0f));
	bl.initPhysics(world); //Since this uses the inital position, must call after setPos
	spheres.push_back(bl);

	Sphere ul;
	ul.initialize(50, 10, 10);
	ul.setPos(glm::vec3(2640.0f, 0.0f, -2640.0f));
	ul.initPhysics(world); //Since this uses the inital position, must call after setPos
	spheres.push_back(ul);
	
	Sphere ur;
	ur.initialize(50, 10, 10);
	ur.setPos(glm::vec3(2640.0f, 0.0f, 2640.0f));
	ur.initPhysics(world); //Since this uses the inital position, must call after setPos
	spheres.push_back(ur);
	
	Sphere br;
	br.initialize(50, 10, 10);
	br.setPos(glm::vec3(-2640.0f, 0.0f, 2640.0f));
	br.initPhysics(world); //Since this uses the inital position, must call after setPos
	spheres.push_back(br);*/

	
	ground = NULL;
	{
		b2BodyDef bd;
		ground = world->CreateBody(&bd);

		b2Vec2 vs[4];
		vs[0].Set(-WALL_LENGTH, -WALL_LENGTH);
		vs[1].Set(-WALL_LENGTH, WALL_LENGTH);
		vs[2].Set(WALL_LENGTH, WALL_LENGTH);
		vs[3].Set(WALL_LENGTH, -WALL_LENGTH);

		b2ChainShape loop;
		loop.CreateLoop(vs, 4);
		b2FixtureDef fd;
		fd.shape = &loop;
		fd.density = 0.0f;
		ground->CreateFixture(&fd);
	}
	
}

Stadium::~Stadium(void)
{
}

bool Stadium::draw(const glm::mat4 & proj, glm::mat4 mv, const glm::ivec2 & size, const float time, lightInfo * & l, materialInfo * & m)
{
	if (GLReturnedError("Stadium draw - on entry")) return false;
	wall_one.draw(proj, mv, size, time, l, m);
	wall_two.draw(proj, mv, size, time, l, m);
	wall_three.draw(proj, mv, size, time, l, m);
	wall_four.draw(proj, mv, size, time, l, m);
	floor.draw(proj, mv, size, time, l, m);
	screen_one.draw(proj, mv, size, time, l, m);
	screen_two.draw(proj, glm::rotate(mv, 90.0f, glm::vec3(0.0, 1.0, 0.0)), size, time, l, m);
	screen_three.draw(proj, glm::rotate(mv, 180.0f, glm::vec3(0.0, 1.0, 0.0)), size, time, l, m);
	screen_four.draw(proj, glm::rotate(mv, 270.0f, glm::vec3(0.0, 1.0, 0.0)), size, time, l, m);
	if (GLReturnedError("Stadium draw - on exit")) return false;
	return true;
}